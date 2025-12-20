#pragma once
#include <iostream>
#include <string>

#include "../../city.hpp"
#include "../../utils.hpp"

using namespace std;

class Base_Building {
   private:
    int id;
    string name;

    // impact value per second
    int satisfactionEffect = 0;
    int waterConsumption = 0;
    int powerConsumption = 0;

   public:
    const BuildingClass buildingClass = BuildingClass::UNKNOWN;

    Base_Building(int id, string name);

    ~Base_Building();

    // afficherDetails
    void display_info() {
        cout << "Building ID: " << id << ", Name: " << name
             << ", Class: " << buildingClass << endl;
    }

   protected:
    virtual void impact_city(City* city) {
        // Placeholder for impacting city stats
        cout << "Impacting city with building ID: " << id << endl;
    }
};
