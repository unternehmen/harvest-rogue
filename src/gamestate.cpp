/*
    harvest-rogue is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    harvest-rogue is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with harvest-rogue.  If not, see <http://www.gnu.org/licenses/>.     */

#include "player.h"
#include "gamestate.h"
#include "textgenerator.h"
#include "landmarkgenerator.h"
#include "tickevents.h"
#include "itemloader.h"

GameState::GameState() {
   this->ItemDatabase = ItemLoader::LoadItemDatabase("media/definitionfiles.json");
   this->active = true;
   this->CurrentScene = nullptr;
   this->NextScene = nullptr;
}

GameState::~GameState() {

}

std::shared_ptr<IScene> GameState::GetCurrentScene() {
   return std::shared_ptr<IScene>(this->CurrentScene);
}

void GameState::SetCurrentScene(std::shared_ptr<IScene> newScene) {
   this->NextScene = std::shared_ptr<IScene>(newScene);
}

bool GameState::IsActive() {
   return this->active;
}

void GameState::Terminate() {
   this->active = false;
}


bool GameState::TransitionScene() {
   if (nullptr == this->NextScene) {
      return false;
   }

   this->CurrentScene = std::shared_ptr<IScene>(this->NextScene);
   this->NextScene = nullptr;

   return true;
}

void GameState::InitializeNewGame() {
   CurrentDay = 1;
   CurrentSeason = (eGameStateSeason) 0;
   CurrentYear = 1;
   CurrentHour = 6;
   CurrentMinute = 0;
   CurrentSecond = 0;

   this->DialogStack.clear();
   this->Landmarks.clear();

   
   this->CurrentLandmarkIndex = -1;

   Player::Get().Reset();

   int playerX, playerY;
   this->Landmarks.push_back(LandmarkGenerator::GeneratePlayerFarm(playerX, playerY));
   Player::Get().WarpPlayer(playerX, playerY);

   this->CurrentLandmarkIndex = (int)this->Landmarks.size() - 1;

   // Temporary debug stuff
   this->AddLogMessage("Welcome to Harvest-Rogue, Alpha 1!");
   this->AddLogMessage("This is a pre-alpha release. Got feedback? Open an issue on github!");
   this->AddLogMessage("https://github.com/essial/harvest-rogue");

}

void GameState::StepSimulation() {
   CurrentSecond += 20;

   CurrentMinute += CurrentSecond / 60;
   CurrentSecond %= 60;

   CurrentHour += CurrentMinute / 60;
   if (CurrentMinute >= 60) {
      this->ProcessHourlyTick();
   }
   CurrentMinute %= 60;

   CurrentDay += CurrentHour / 24;
   if (CurrentHour >= 24) {
      this->ProcessDailyTick();
   }
   CurrentHour %= 24;

   while (CurrentDay > 30) {
      CurrentDay -= 30;
      CurrentSeason = (eGameStateSeason) ((int) CurrentSeason + 1);
      if ((int) CurrentSeason > 3) {
         CurrentSeason = (eGameStateSeason) 0;
         CurrentYear++;
      }
      std::stringstream seasonNotice;
      seasonNotice << "It is now " << eGameStateSeasonDescs[CurrentSeason] << "!";
      this->AddLogMessage(seasonNotice.str());
   }
}

int GameState::GetCurrentDay() {
   return this->CurrentDay;
}

eGameStateSeason GameState::GetCurrentSeason() {
   return this->CurrentSeason;
}

int GameState::GetCurrentYear() {
   return this->CurrentYear;
}

int GameState::GetCurrentHour() {
   return this->CurrentHour;
}

int GameState::GetCurrentMinute() {
   return this->CurrentMinute;
}

int GameState::GetCurrentSecond() {
   return this->CurrentSecond;
}

void GameState::AddLogMessage(std::string Message) {
   this->Log.push_back(Message);
   while (this->Log.size() > 50) {
      this->Log.erase(this->Log.begin());
   }
}

void GameState::AddLogMessageFmt(const std::string format, ...) {
   unsigned long size = 4096;
   std::string str;
   va_list ap;
   while (1) {     // Maximum two passes on a POSIX system...
      str.resize(size);
      va_start(ap, format);
      int n = vsnprintf((char *) str.data(), size, format.c_str(), ap);
      va_end(ap);
      if (n > -1 && n < (int)size) {  // Everything worked
         str.resize(n);
         this->AddLogMessage(str);
         return;
      }
      if (n > -1)  // Needed size returned
         size = (unsigned long)n + 1;   // For null char
      else
         size *= 2;      // Guess at a larger size (OS specific)
   }
}

std::vector<std::string> GameState::GetLogMessages() {
   return this->Log;
}

std::shared_ptr<Landmark> GameState::GetCurrentLandmark() {
   if (this->CurrentLandmarkIndex < 0) {
      return nullptr;
   }

   if (this->CurrentLandmarkIndex > this->Landmarks.size()) {
      return nullptr;
   }

   return std::shared_ptr<Landmark>(this->Landmarks[this->CurrentLandmarkIndex]);


}

std::vector<std::shared_ptr<Landmark>> GameState::GetAllLandmarks()
{
   return this->Landmarks;
}

std::shared_ptr<IDialog> GameState::GetCurrentDialog() {
   if (this->DialogStack.empty()) {
      return nullptr;
   }
   return this->DialogStack.back();
}

void GameState::PushDialog(std::shared_ptr<IDialog> dialog) {
   this->DialogStack.push_back(std::shared_ptr<IDialog>(dialog));
}

void GameState::PopDialog() {
   if (this->DialogStack.empty()) {
      return;
   }
   this->DialogStack.pop_back();
}

void GameState::ClearAllDialogs() {
   this->DialogStack.clear();
}

void GameState::SleepUntilNextMorning(int hour, int minute, int second) {
   Player::Get().SetIsSleeping(true);
   auto currentHour = this->GetCurrentHour();
   int totalHoursSlept = 0;
   while((this->GetCurrentHour() != hour) || (this->GetCurrentMinute() != minute)
         || (this->GetCurrentSecond() != second)) {
      this->StepSimulation();

      if (currentHour != this->GetCurrentHour()) {
         currentHour = this->GetCurrentHour();
         totalHoursSlept++;
      }

      // If the player wakes up, stop running the sleep simulation.
      if (!Player::Get().GetIsSleeping()) {
         GameState::Get().AddLogMessage("Your sleep has been interupted!");
         break;
      }
   }
   GameState::Get().AddLogMessageFmt("You slept for %i hours!", totalHoursSlept);
   Player::Get().SetIsSleeping(false);
}

std::map<std::string, Item> GameState::GetItemDatabase()
{
   return this->ItemDatabase;
}

ItemPtr GameState::GetItemFromItemDatabase(std::string itemName)
{
   return std::make_shared<Item>(Item::Clone(this->ItemDatabase[itemName]));
}

void GameState::ProcessDailyTick() {

}

void GameState::ProcessHourlyTick() {
   // Sleeping causes energy gain for the player every hour slept.
   if (Player::Get().GetIsSleeping()) {
      Player::Get().AdjustEnergy(10);
   };

   for (auto landmark : GameState::Landmarks) {
      auto landmarkItems = landmark->GetAllLandmarkItems();
      for (auto landmarkItem : landmarkItems) {
         if (landmarkItem.second == nullptr) {
            continue;
         }
         std::shared_ptr<IHourlyTickEvent> hourlyTickEvent;

         for (auto i : landmarkItem.second->ItemTarget->GetInterfaces()) {
            hourlyTickEvent = std::dynamic_pointer_cast<IHourlyTickEvent>(i.second);
            if (hourlyTickEvent != nullptr) {
               break;
            }
         }

         if (hourlyTickEvent == nullptr) {
            continue;
         }

         hourlyTickEvent->OnHourlyTick(landmarkItem.second->ItemTarget);
      }
   }
}
