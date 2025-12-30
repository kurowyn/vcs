#include "building.hpp"

i32 Building::g_building_id {1};

Resource::Resource(string type, string unit, i32 quantity) {
    m_type = type;
    m_unit = unit;
    m_quantity = quantity;
}

Building::Building(string name, string type, i32 id) {
    m_id = id;
    m_name = name;
    m_type = type;
    m_satisfaction_effect = Random::GenerateRandomInteger(-100, 1000);
    m_pollution_effect = Random::GenerateRandomInteger(10, 1000);
    m_consumed_water = Resource(ResourceType::WATER, 
                                Unit::LITER,
                                Random::GenerateRandomInteger(10, 1000));
    m_consumed_electricity = Resource(ResourceType::ELECTRICITY, 
                                      Unit::WATT,
                                      Random::GenerateRandomInteger(10, 1000));
    m_produced_water = Resource(ResourceType::WATER, Unit::LITER, 0);
    m_produced_electricity = Resource(ResourceType::ELECTRICITY, Unit::WATT, 0);
    m_inhabitant_count = 0;
    m_inhabitant_capacity = 0;
    if (type == BuildingType::HOUSE) {
        m_inhabitant_count = Random::GenerateRandomInteger(10, 30);
        m_inhabitant_capacity = Random::GenerateRandomInteger(30, 40);
    } else if (type == BuildingType::FACTORY) {
        m_produced_water = Resource(ResourceType::WATER, 
                                    Unit::LITER,
                                    Random::GenerateRandomInteger(100, 1000));
        m_produced_electricity = Resource(ResourceType::ELECTRICITY, 
                                          Unit::WATT,
                                          Random::GenerateRandomInteger(100, 1000));
    }
}

Building::Building(string name, string type): Building(name, type, Building::g_building_id++) {}

Building::Building(string type): Building(Building::GenerateBuildingName(type), 
                                          type, 
                                          Building::g_building_id++) {}

std::string Building::GenerateBuildingName(std::string type) {
    static std::array random_adjectives {"Beautiful", "Amazing", "Great", "Wonderful", "Ordinary"};
    return std::format("{} {}", 
                random_adjectives[Random::GenerateRandomInteger(0, random_adjectives.size() - 1)],
                type);
}


void Building::ShowBuildingDetails(void) {
    std::println("ID: {}\n"
                 "Name: {}\n"
                 "Type: {}\n"
                 "Inhabitant Count: {}\n"
                 "Inhabitant Capacity: {}\n"
                 "Consumed Electricity: {}\n"
                 "Consumed Water: {}\n"
                 "Produced Water: {}\n"
                 "Produced Electricity: {}\n"
                 "Satisfaction Effect: {}\n"
                 "Pollution Effect: {}\n",
                 m_id, m_name, m_type, m_inhabitant_count, m_inhabitant_capacity,
                 m_consumed_electricity.m_quantity, m_consumed_water.m_quantity,
                 m_produced_water.m_quantity, m_produced_electricity.m_quantity,
                 m_satisfaction_effect, m_pollution_effect);
}

void Building::AddInhabitants(i32 count) {
    if (m_type == BuildingType::HOUSE && count > 0) {
        m_inhabitant_count = m_inhabitant_count + count > m_inhabitant_capacity ? 
                             m_inhabitant_count : m_inhabitant_count + count;
    }
}

void Building::RemoveInhabitants(i32 count) {
    if (m_type == BuildingType::HOUSE && count > 0) {
        m_inhabitant_count = m_inhabitant_count + count > m_inhabitant_capacity ? 
                             m_inhabitant_count : m_inhabitant_count + count;
    }
}

void Building::ProduceResources(void) {
    if (m_type == BuildingType::FACTORY) {
        m_pollution_effect += Random::GenerateRandomInteger(-100, 100);
        m_satisfaction_effect += Random::GenerateRandomInteger(-100, 100);
        m_produced_water.m_quantity += Random::GenerateRandomInteger(100, 1000);
        m_produced_electricity.m_quantity += Random::GenerateRandomInteger(100, 1000);
    }
}

void Building::IncreaseSatisfactionEffect(void) {
    m_satisfaction_effect += Random::GenerateRandomInteger(100, 1000);
}

City::City(string name) {
    m_name = name;
}

City::City(void) {
    static std::array random_adjectives {"Beautiful", "Amazing", "Great", "Wonderful", "Ordinary"};
    m_name = std::format("{} City", 
                random_adjectives[Random::GenerateRandomInteger(0, random_adjectives.size() - 1)]);
    m_total_water_consumption = Resource(ResourceType::WATER, Unit::LITER, 0);
    m_total_electricity_consumption = Resource(ResourceType::ELECTRICITY, Unit::WATT, 0);
    m_total_water_quantity = Resource(ResourceType::WATER, Unit::LITER, 0);
    m_total_electricity_quantity = Resource(ResourceType::ELECTRICITY, Unit::WATT, 0);
}

void City::AddBuilding(Building building) {
    m_buildings.push_back(building);
}

void City::RemoveBuilding(i32 id) {
    for (auto it {m_buildings.begin()}; it != m_buildings.end(); ++it) {
        if (it->m_id == id) {
            m_buildings.erase(it);
            break;
        }
    }
}

void City::CalculateSatisfactionRate(void) {
    auto total {0};
    for (auto it {m_buildings.begin()}; it != m_buildings.end(); ++it) {
        total += it->m_satisfaction_effect;
    }
    m_total_satisfaction_rate = total;
}

void City::CalculateTotalWaterConsumption(void) {
    auto total {0};
    for (auto it {m_buildings.begin()}; it != m_buildings.end(); ++it) {
        total += it->m_consumed_water.m_quantity;
    }
    m_total_water_consumption.m_quantity = total;
}

void City::CalculateTotalElectricityConsumption(void) {
    auto total {0};
    for (auto it {m_buildings.begin()}; it != m_buildings.end(); ++it) {
        total += it->m_consumed_electricity.m_quantity;
    }
    m_total_electricity_consumption.m_quantity = total;
}

void City::CalculateTotalWater(void) {
    auto total {0};
    for (auto it {m_buildings.begin()}; it != m_buildings.end(); ++it) {
        total += it->m_produced_water.m_quantity;
    }
    m_total_water_quantity.m_quantity = total;
}

void City::CalculateTotalElectricity(void) {
    auto total {0};
    for (auto it {m_buildings.begin()}; it != m_buildings.end(); ++it) {
        total += it->m_produced_electricity.m_quantity;
    }
    m_total_electricity_quantity.m_quantity = total;
}
