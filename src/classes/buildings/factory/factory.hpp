#pragma once

#include <string>

#include "../../../utils.hpp"
#include "../base-building.hpp"

using namespace std;

class Factory : public Base_Building {
   private:
    // productionRessources et pollution.
    int waterProduction = 10;
    int powerProduction = 10;

    int pollution = 5;

   public:
    const BuildingClass buildingClass = BuildingClass::FACTORY;

    Factory(int id, string name);
    ~Factory();

    void impact_city(City* city) override {
        // produireRessources() et calculerPollution().
        cout << "producing " << pollution << "generating " << waterProduction
             << " water and " << powerProduction << " power" << endl;
    }
};