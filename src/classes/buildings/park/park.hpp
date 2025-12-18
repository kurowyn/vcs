#pragma once

#include "../../../utils.hpp"
#include "../base-building.hpp"

class Park : public Base_Building {
   private:
    const BuildingClass buildingClass = BuildingClass::PARK;

   public:
    Park(int id, string name);
    ~Park();
};