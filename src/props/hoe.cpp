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
#include "hoe.h"
#include "colors.h"
#include "gamestate.h"

Hoe::Hoe() {

}

std::string Hoe::GetName() {
   return "Hoe";
}

std::string Hoe::GetDescription() {
   return "A tool for tilling the ground.";
}

int Hoe::GetColorCode() {
   return CLR_YELLOW;
}

char Hoe::GetCharacterCode() {
   return '\\';
}

bool Hoe::IsUsable() {
   auto landmark = GameState::Get().GetCurrentLandmark();
   if (landmark == nullptr) {
      return false;
   }

   auto playerX = Player::Get().GetPositionX();
   auto playerY = Player::Get().GetPositionY();
   auto currentTile = landmark->GetTile(playerX, playerY);

   switch(currentTile.TileType) {
      case eTileType::TileTilled:
      case eTileType::TileGrassTuft:
         return true;
      default:
         return false;
   }
}

void Hoe::Use() {
   auto landmark = GameState::Get().GetCurrentLandmark();
   if (landmark == nullptr) {
      return;
   }

   auto playerX = Player::Get().GetPositionX();
   auto playerY = Player::Get().GetPositionY();
   auto currentTile = landmark->GetTile(playerX, playerY);
   switch(currentTile.TileType) {
      case eTileType::TileGrassTuft:
         landmark->SetTile(playerX, playerY, eTileType::TileGrass);
         break;
      case eTileType::TileTilled:
         landmark->SetTile(playerX, playerY, eTileType::TileTilled);
         break;
   }

}
