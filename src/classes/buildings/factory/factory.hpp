#pragma once

#include <string>

#include "classes/buildings/base-building.hpp"
#include "utils/utils.hpp"

using namespace std;

class Factory : public Base_Building {
   private:
   public:
    const EBuildingClass buildingClass = EBuildingClass::FACTORY;

    Factory(int id, string name, Vector2D position);
    ~Factory();
};