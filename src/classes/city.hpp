#pragma once

#include <unordered_map>

#include "./buildings/base-building.hpp"

using namespace std;

class City {
   private:
    int idCount = 1;
    unordered_map<int, Base_Building*> buildings;

   public:
    City();
    ~City();

    void add_building(string name, BuildingClass building);
    void remove_building();
};
