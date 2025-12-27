#include "building.hpp"

int main(void) {
    auto b {Building::CreateRandomBuilding()};
    b.ShowBuildingDetails();
}
