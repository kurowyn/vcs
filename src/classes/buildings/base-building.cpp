#include "classes/buildings/base-building.hpp"

#include <string>

using namespace std;

Base_Building::Base_Building(int id, string name, Vector2D position)
    : position(position), id(id), name(name) {}

Base_Building::~Base_Building() {}

void Base_Building::set_effect(EBuildingEffect effect, int value) {
    if (value == 0) {
        effects.erase(effect);
        return;
    }

     effects[effect] = value;
}

void Base_Building::set_resource(EBuildingResource resource, int value) {
    if (value < 0) {
        std::cerr << "Resource value cannot less than zero." << std::endl;
        return;
    }

    if (value == 0) {
        resources.erase(resource);
        return;
    }

    resources[resource] = value;
}

int Base_Building::get_effect(EBuildingEffect effect) {
    if (effects.find(effect) != effects.end()) {
        return effects[effect];
    }
    return 0;
}

int Base_Building::get_resource(EBuildingResource resource) {
    if (resources.find(resource) != resources.end()) {
        return resources[resource];
    }
    return 0;
}