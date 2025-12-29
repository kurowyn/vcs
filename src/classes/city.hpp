#pragma once

#include <unordered_map>

#include "classes/buildings/base-building.hpp"

using namespace std;

class City {
   private:
    int _buildingIdGen = 1;

    std::unordered_map<int, Base_Building*> buildings;

    bool is_area_free(Vector2D position, EBuildingClass buildingType);

   public:
    string name;

    City(string name);
    ~City();

    void add_building(string name, EBuildingClass building, Vector2D position);
    void remove_building(int id);
    void tick(int deltaTime);

    int get_effect_count(EBuildingEffect effect);

    int get_needed_resources(EBuildingResource resource);
};
