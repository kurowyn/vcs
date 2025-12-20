#pragma once

#include <unordered_map>

#include "./buildings/base-building.hpp"

using namespace std;

class City {
   private:
    int buildingIdCount = 1;

    unordered_map<int, Base_Building*> buildings;
    int pollution = 0;
    int satisfaction = 0;
    int waterSupply = 100;
    int powerSupply = 100;

   public:
    string name;

    City(string name);

    ~City();

    void add_building(string name, BuildingClass building);
    void remove_building(int id);
    void tick(int deltaTime);

    int get_pollution() const { return pollution; }
    int get_satisfaction() const { return satisfaction; }
    int get_water_supply() const { return waterSupply; }
    int get_power_supply() const { return powerSupply; }
};
