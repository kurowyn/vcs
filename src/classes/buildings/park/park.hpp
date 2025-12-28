#pragma once

#include "utils/utils.hpp"
#include "classes/buildings/base-building.hpp"

class Park : public Base_Building {
   private:
    const EBuildingClass buildingClass = EBuildingClass::PARK;

   public:
    Park(int id, string name, Vector2D position);
    ~Park();
};