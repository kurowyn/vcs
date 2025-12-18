#pragma once
#include <string>

#include "../../../utils.hpp"
#include "../base-building.hpp"

using namespace std;

class House : public Base_Building {
   private:
   public:
    const BuildingClass buildingClass = BuildingClass::HOUSE;

    House(int id, string name);
    ~House();
};
