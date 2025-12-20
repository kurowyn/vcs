#pragma once

#include "../../../utils.hpp"
#include "../base-building.hpp"

class Park : public Base_Building {
   private:
    const BuildingClass buildingClass = BuildingClass::PARK;

    int satisfactionEffect = 5;

   public:
    Park(int id, string name);
    ~Park();

    void upgrade_satisfaction() {};
};