#ifndef BUILDING_HPP
#define BUILDING_HPP

#include "random.hpp"
#include "common.hpp"

struct Resource {
    string m_type {};
    string m_unit {};
    i32 m_quantity {};
    Resource(void) = default;
    Resource(string type, string unit, i32 quantity);
};

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
        i32 m_id {};
        i32 m_satisfaction_effect {};
        i32 m_pollution_effect {};
        string m_name {};
        string m_type {};
        i32 m_inhabitant_count {};
        i32 m_inhabitant_capacity {};
        Resource m_consumed_water {};
        Resource m_consumed_electricity {};
        Resource m_produced_water {};
        Resource m_produced_electricity {};

        Building(string name, string type, i32 id);
        Building(string name, string type);
        Building(string type);
        Building(void) = default;

        static i32 g_building_id;
        static std::string GenerateBuildingName(std::string type);

        void ShowBuildingDetails(void);
        void AddInhabitants(i32 count);
        void RemoveInhabitants(i32 count);
        void ProduceResources(void);
        void IncreaseSatisfactionEffect(void);
};

class City {
    public:
        std::string m_name {};
        std::vector<Building> m_buildings {};
        i32 m_population {};
        i32 m_total_satisfaction_rate {};
        i32 m_total_pollution_rate {};
        Resource m_total_water_consumption;
        Resource m_total_electricity_consumption;
        Resource m_total_water_quantity;
        Resource m_total_electricity_quantity;

        City(std::string name);
        City(void);
        void AddBuilding(Building building);
        void RemoveBuilding(i32 id);
        void CalculateSatisfactionRate(void);
        void CalculateTotalWaterConsumption(void);
        void CalculateTotalElectricityConsumption(void);
        void CalculateTotalWater(void);
        void CalculateTotalElectricity(void);
        void ShowCityInformation(void);
};

#endif // BUILDING_HPP
