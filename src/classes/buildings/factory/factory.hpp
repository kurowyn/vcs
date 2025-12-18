#pragma once

#include <string>

#include "../../../utils.hpp"
#include "../base-building.hpp"

using namespace std;

class Factory : public Base_Building {
   private:
   public:
    const BuildingClass buildingClass = BuildingClass::FACTORY;

    Factory(int id, string name);
    ~Factory();
};