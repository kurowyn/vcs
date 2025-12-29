#include "classes/city.hpp"

#include <iostream>

#include "classes/buildings/factory/factory.hpp"
#include "classes/buildings/house/house.hpp"
#include "classes/buildings/park/park.hpp"

City::City(string name) : name(name) {}

City::~City() {}

void City::tick(int deltaTime) {
    // Placeholder for future implementation
}

bool City::is_area_free(Vector2D position, EBuildingClass buildingType) {
    Vector2D size = BuildingMetaDict::getMetaFromEnum(buildingType).size;

    for (const auto& pair : this->buildings) {
        Base_Building* building = pair.second;
        Vector2D otherSize =
            BuildingMetaDict::getMetaFromEnum(building->buildingClass).size;

        if (areColliding(position, size, building->position, otherSize)) {
            return false;
        }
    }

    return true;
}

void City::add_building(string name, EBuildingClass buildingType,
                        Vector2D position) {
    if (!this->is_area_free(position, buildingType)) {
        std::cerr << "Cannot place building here, area is occupied!"
                  << std::endl;
        return;
    }

    int id = this->_buildingIdGen++;
    switch (buildingType) {
        case EBuildingClass::HOUSE:
            this->buildings[id] = new House(id, name, position);
            break;
        case EBuildingClass::FACTORY:
            this->buildings[id] = new Factory(id, name, position);
            break;
        case EBuildingClass::PARK:
            this->buildings[id] = new Park(id, name, position);
            break;
        default:
            std::cerr << "Unknown building type!" << std::endl;
            break;
    }
}

void City::remove_building(int id) {
    auto it = this->buildings.find(id);
    if (it != this->buildings.end()) {
        delete it->second;
        this->buildings.erase(it);
    } else
        std::cerr << "Building with ID " << id << " not found!" << std::endl;
}

int City::get_needed_resources(EBuildingResource resource) {
    int total = 0;

    for (const auto& pair : buildings)
        total += pair.second->get_resource(resource);

    return total;
}

int City::get_effect_count(EBuildingEffect effect) {
    int total = 0;

    for (const auto& [id, building] : buildings) {
        total += building->get_effect(effect);
    }

    return total;
}