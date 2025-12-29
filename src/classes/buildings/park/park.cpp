#include "classes/buildings/park/park.hpp"

Park::Park(int id, string name, Vector2D position)
    : Base_Building(id, name, position) {
    this->set_effect(EBuildingEffect::SATISFACTION, 5);
}

Park::~Park() {}
