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

#include <memory>
#include "player.h"
#include "gamestate.h"

Player::Player() {

}

Player::~Player() {

}

void Player::Reset() {
   this->WarpPlayer(0, 0);
}

int Player::GetPositionX() {
   return this->PositionX;
}

int Player::GetPositionY() {
   return this->PositionY;
}

void Player::WarpPlayer(int x, int y) {
   this->PositionX = x;
   this->PositionY = y;
}

void Player::WalkPlayer(eDirection direction) {
   auto currentLandmark = GameState::Get().GetCurrentLandmark();
   auto newX = 0, newY = 0;
   switch (direction) {
      case DirectionUp:
         if (this->PositionX == 0)
            return;
         newX = this->GetPositionX();
         newY = this->GetPositionY() - 1;
         break;

      case DirectionDown:
         if (this->PositionY == (currentLandmark->GetHeight() - 1))
            return;
         newX = this->GetPositionX();
         newY = this->GetPositionY() + 1;
         break;

      case DirectionLeft:
         if (this->PositionX == 0)
            return;
         newX = this->GetPositionX() - 1;
         newY = this->GetPositionY();
         break;

      case DirectionRight:
         if (this->PositionX == (currentLandmark->GetWidth() - 1))
            return;
         newX = this->GetPositionX() + 1;
         newY = this->GetPositionY();
         break;
   }

   if (!this->IsPassable(newX, newY)) {
      return;
   }

   this->WarpPlayer(newX, newY);
}

std::shared_ptr<ITool> Player::GetCurrentTool() {
return std::shared_ptr<ITool>(this->CurrentTool);
}

std::vector<std::shared_ptr<IProp>> Player::GetInventory() {
return this->Inventory;
}

void Player::SpawnIntoInventory(std::shared_ptr<IProp> prop) {
this->Inventory.push_back(std::shared_ptr<IProp>(prop));
}

void Player::PickUpItemFromGround() {
auto currentLandmark = GameState::Get().GetCurrentLandmark();
auto prop = currentLandmark->GetProp(this->GetPositionX(), this->GetPositionY());
if (prop == nullptr) {
GameState::Get().AddLogMessage("There is nothing on the ground to pick up.");
return;
}

currentLandmark->RemoveProp(this->GetPositionX(), this->GetPositionY());
this->SpawnIntoInventory(prop);
bool startsWithVowel = prop->GetName().find_first_of("aAeEiIoOuU") == 0;
GameState::Get().AddLogMessageFmt("You pick up %s %s.", startsWithVowel ? "an" : "a", prop->GetName().c_str());
}

void Player::EquipFromInventory(std::shared_ptr<ITool> tool) {
this->RemoveFromInventory(std::dynamic_pointer_cast<IProp>(tool));
this->CurrentTool = std::shared_ptr<ITool>(tool);
}

void Player::DropInventoryItemOnGround(std::shared_ptr<IProp> prop) {
auto currentLandmark = GameState::Get().GetCurrentLandmark();
this->RemoveFromInventory(prop);
currentLandmark->AddProp(this->GetPositionX(), this->GetPositionY(), prop);
}

void Player::RemoveFromInventory(std::shared_ptr<IProp> prop) {
auto i = 0;
for (auto invProp : this->Inventory) {
if (invProp != prop) {
i++;
continue;
}

this->Inventory.erase(this->Inventory.begin() + i);
break;
}
}

void Player::UseTool() {
if(this->CurrentTool == nullptr) {
GameState::Get().AddLogMessage("You do not currently have a tool equipped!");
return;
}
if (!this->CurrentTool->IsUsable()) {
auto prop = std::dynamic_pointer_cast<IProp>(this->CurrentTool);

GameState::Get().AddLogMessageFmt("The %s is not usable at this time.", prop->GetName().c_str());
}
this->CurrentTool->Use();
}

void Player::UnequipCurrentTool() {
if (this->CurrentTool == nullptr) {
GameState::Get().AddLogMessage("You do not currently have a tool equipped!");
return;
}
this->SpawnIntoInventory(std::dynamic_pointer_cast<IProp>(this->CurrentTool));
this->CurrentTool = nullptr;
}

bool Player::IsPassable(int x, int y) {
auto currentLandmark = GameState::Get().GetCurrentLandmark();
auto tile = currentLandmark->GetTile(x, y);
if (!TileHasSurfaceAttribute(tile, eSurfaceAttributeType::Walkable)) {
return false;
}
auto prop = currentLandmark->GetProp(x, y);
if (prop == nullptr) {
return true;
}
return prop->GetIsPassable();
}
