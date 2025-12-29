#pragma once
#include <iostream>
#include <string>
#include <unordered_map>

#include "utils/utils.hpp"

using namespace std;

class Base_Building {
   private:
    int id;
    string name;

   protected:
    unordered_map<EBuildingEffect, int> effects;
    unordered_map<EBuildingResource, int> resources;

   public:
    const EBuildingClass buildingClass = EBuildingClass::UNKNOWN;
    const Vector2D position;

    Base_Building(int id, string name, Vector2D position);

    ~Base_Building();

    // afficherDetails
    void display_info() {
        cout << "Building ID: " << id << ", Name: " << name
             << ", Class: " << buildingClass << endl;
    }

   protected:
    void set_effect(EBuildingEffect effect, int value);

    void set_resource(EBuildingResource resource, int value);

   public:
    int get_effect(EBuildingEffect effect);
    int get_resource(EBuildingResource resource);
};
