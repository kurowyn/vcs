#pragma once
#include <string>

#include "utils/utils.hpp"
#include "classes/buildings/base-building.hpp"

using namespace std;

class House : public Base_Building {
   private:
    // capaciteHabitants et habitantsActuels
    int maxOccupants = 4;
    int currentOccupants = 0;

   public:
    const EBuildingClass buildingClass = EBuildingClass::HOUSE;

    House(int id, string name, Vector2D position);
    ~House();

    // ajouterHabitants(nb) et retirerHabitants(nb).
    bool add_occupants_if_possible(int nb) {
        if (currentOccupants + nb > maxOccupants) return false;

        currentOccupants += nb;
        return true;
    }
    void remove_occupants(int nb) {
        if (currentOccupants - nb >= 0)
            currentOccupants -= nb;
        else
            currentOccupants = 0;
    }
};
