#pragma once
#include <string>

#include "../../utils.hpp"

using namespace std;

class Base_Building {
   private:
    int id;
    string name;

   public:
    const BuildingClass buildingClass = BuildingClass::UNKNOWN;

    Base_Building(int id, string name);

    ~Base_Building();
};
