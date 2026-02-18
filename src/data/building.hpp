#ifndef BUILDING_HPP
#define BUILDING_HPP

#include "common.hpp"
#include "random.hpp"

struct Resource {
    string m_type{};
    string m_unit{};
    i32 m_quantity{};
    Resource(void) = default;
    Resource(string type, string unit, i32 quantity);
};

Resource operator+(Resource r1, Resource r2);
Resource operator-(Resource r1, Resource r2);
Resource operator+=(Resource& r1, Resource r2);
Resource operator-=(Resource& r1, Resource r2);

namespace BuildingType {
    constexpr string HOUSE = "House";
    constexpr string FACTORY = "Factory";
    constexpr string PARK = "Park";
    constexpr string NONE = "NONE";
};  

namespace ResourceType {
    constexpr string WATER = "Water";
    constexpr string ELECTRICITY = "Electricity";
    constexpr string NONE = "NONE";
};  

namespace Unit {
    constexpr string LITER = "Liter";
    constexpr string WATT = "Watt";
    constexpr string NONE = "NONE";
};  

class Building {
   public:
    i32 m_id{};
    i32 m_satisfaction_effect{};
    i32 m_pollution_effect{};
    string m_name{};
    string m_type{};
    i32 m_inhabitant_count{};
    i32 m_inhabitant_capacity{};
    Resource m_consumed_water{};
    Resource m_consumed_electricity{};
    Resource m_produced_water{};
    Resource m_produced_electricity{};

    Building(string name, string type, i32 id);
    Building(string name, string type);
    Building(string type);
    Building(void) = default;

    static i32 g_building_id;
    static std::string GenerateBuildingName(std::string type);

    void ShowBuildingDetails(void);
};

class City {
   public:
    std::string m_name{};
    std::vector<Building> m_buildings{};
    i32 m_population{};
    i32 m_satisfaction_level{};
    i32 m_pollution_level{};
    Resource m_consumed_water;
    Resource m_consumed_electricity;
    Resource m_produced_water;
    Resource m_produced_electricity;

    City(std::string name);
    City(void);
    void AddBuilding(Building building);
    void ModifyBuilding(i32 id, Building building);
    void RemoveBuilding(i32 id);
    Building SearchBuilding(i32 id);

    void ModifyPopulation(i32 population);
    void ModifyPollutionLevel(i32 pollution);
    void ModifySatisfactionLevel(i32 satisfaction);

    void ProduceResources(void);
    void ConsumeResources(void);

    void ShowCityInformation(void);
};

#endif  // BUILDING_HPP
