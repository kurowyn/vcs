#include "utils.hpp"

namespace BuildingMetaDict {
BuildingMetaData* HOUSE =
    new BuildingMetaData(EBuildingClass::HOUSE, {1.0f, 1.0f});
BuildingMetaData* FACTORY =
    new BuildingMetaData(EBuildingClass::FACTORY, {2.0f, 2.0f});
BuildingMetaData* PARK =
    new BuildingMetaData(EBuildingClass::PARK, {1.5f, 1.5f});

BuildingMetaData getMetaFromEnum(EBuildingClass className) {
    switch (className) {
        case EBuildingClass::HOUSE:
            return *HOUSE;
        case EBuildingClass::FACTORY:
            return *FACTORY;
        case EBuildingClass::PARK:
            return *PARK;
        default:
            std::cerr << "Error: BuildingMetaDict::getMetaFromEnum - Unknown "
                         "building class enum."
                      << std::endl;
            exit(-1);
    }
}
}  // namespace BuildingMetaDict
