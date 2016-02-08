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

#ifndef HARVEST_ROGUE_PROP_H
#define HARVEST_ROGUE_PROP_H

#include <string>
#include <memory>
#include "tiles.h"

class IProp {
public:
   virtual ~IProp() { }
   virtual std::string GetName() = 0;
   virtual std::string GetDescription() = 0;
   virtual TileType::TileType GetTileType() = 0;
};

#endif //HARVEST_ROGUE_PROP_H
