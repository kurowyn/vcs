#pragma once
#include <string>

#include "../../../utils.hpp"
#include "../base-building.hpp"

using namespace std;

class House : public Base_Building {
   private:
    // capaciteHabitants et habitantsActuels
    int maxOccupants = 4;
    int currentOccupants = 0;

   public:
    const BuildingClass buildingClass = BuildingClass::HOUSE;

    House(int id, string name);
    ~House();

    // ajouterHabitants(nb) et retirerHabitants(nb).
    bool add_occupants(int nb) {
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
