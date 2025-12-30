#include "building.hpp"

int main(void) {
    City city {};
    city.AddBuilding(Building(BuildingType::HOUSE));
    city.AddBuilding(Building(BuildingType::PARK));
    city.AddBuilding(Building(BuildingType::FACTORY));
    city.AddBuilding(Building(BuildingType::HOUSE));
    city.AddBuilding(Building(BuildingType::PARK));
    for (auto& building: city.m_buildings) {
        building.ShowBuildingDetails();
    }
    city.RemoveBuilding(1);
    city.RemoveBuilding(2);
    city.RemoveBuilding(10);
    for (auto& building: city.m_buildings) {
        building.ShowBuildingDetails();
    }
}
