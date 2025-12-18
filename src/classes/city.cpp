#include "./city.hpp"

#include <iostream>

#include "./buildings/factory/factory.hpp"
#include "./buildings/house/house.hpp"
#include "./buildings/park/park.hpp"

City::City() {}

City::~City() {}

void City::add_building(string name, BuildingClass buildingType) {
    int id = this->idCount++;
    switch (buildingType) {
        case BuildingClass::HOUSE:
            this->buildings[id] = new House(id, name);
            break;
        case BuildingClass::FACTORY:
            this->buildings[id] = new Factory(id, name);
            break;
        case BuildingClass::PARK:
            this->buildings[id] = new Park(id, name);
            break;
        default:
            std::cerr << "Unknown building type!" << std::endl;
            break;
    }
}