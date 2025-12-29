#include "classes/buildings/factory/factory.hpp"

Factory::Factory(int id, string name, Vector2D position) : Base_Building(id, name, position) {
    this->set_effect(EBuildingEffect::POLLUTION, 5);
    this->set_resource(EBuildingResource::POWER, 10);
    this->set_resource(EBuildingResource::WATER, 10);
}

Factory::~Factory() {}