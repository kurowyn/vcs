#pragma once

#include <unordered_map>

#include "./buildings/base-building.hpp"

using namespace std;

class City {
   private:
    int buildingIdCount = 1;
    unordered_map<int, Base_Building*> buildings;

   public:
    string name;
    City(string name);

    ~City();

    void add_building(string name, BuildingClass building);
    void tick(int deltaTime);
};
