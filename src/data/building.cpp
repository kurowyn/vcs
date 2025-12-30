#include "building.hpp"

i32 Building::g_building_id{1};

Resource::Resource(string type, string unit, i32 quantity) {
    m_type = type;
    m_unit = unit;
    m_quantity = quantity;
}

Resource operator+(Resource r1, Resource r2) {
    if (r1.m_type == r2.m_type && r1.m_unit == r2.m_unit) {
        return Resource(r1.m_type, r1.m_unit, r1.m_quantity + r2.m_quantity);
    }
}

Resource operator-(Resource r1, Resource r2) {
    if (r1.m_type == r2.m_type && r1.m_unit == r2.m_unit) {
        return Resource(r1.m_type, r1.m_unit,
                        r1.m_quantity - r2.m_quantity >= 0
                            ? r1.m_quantity - r2.m_quantity
                            : 0);
    }
}

Resource operator+=(Resource& r1, Resource r2) {
    if (r1.m_type == r2.m_type && r1.m_unit == r2.m_unit) {
        r1.m_quantity = r1.m_quantity + r2.m_quantity;
        return Resource(r1.m_type, r1.m_unit, r1.m_quantity + r2.m_quantity);
    }
}

Resource operator-=(Resource& r1, Resource r2) {
    if (r1.m_type == r2.m_type && r1.m_unit == r2.m_unit) {
        r2.m_quantity = r1.m_quantity - r2.m_quantity >= 0
                            ? r1.m_quantity - r2.m_quantity
                            : 0;
        return Resource(r1.m_type, r1.m_unit,
                        r1.m_quantity - r2.m_quantity >= 0
                            ? r1.m_quantity - r2.m_quantity
                            : 0);
    }
}

Building::Building(string name, string type, i32 id) {
    m_id = id;
    m_name = name;
    m_type = type;
    m_satisfaction_effect = Random::GenerateRandomInteger(10, 1000);
    m_pollution_effect = Random::GenerateRandomInteger(10, 1000);
    m_consumed_water = Resource(ResourceType::WATER, Unit::LITER,
                                Random::GenerateRandomInteger(10, 1000));
    m_consumed_electricity = Resource(ResourceType::ELECTRICITY, Unit::WATT,
                                      Random::GenerateRandomInteger(10, 1000));
    m_produced_water = Resource(ResourceType::WATER, Unit::LITER, 0);
    m_produced_electricity = Resource(ResourceType::ELECTRICITY, Unit::WATT, 0);
    m_inhabitant_count = 0;
    m_inhabitant_capacity = 0;
    if (type == BuildingType::HOUSE) {
        m_inhabitant_count = Random::GenerateRandomInteger(10, 30);
        m_inhabitant_capacity = Random::GenerateRandomInteger(30, 40);
    } else if (type == BuildingType::FACTORY) {
        m_produced_water = Resource(ResourceType::WATER, Unit::LITER,
                                    Random::GenerateRandomInteger(100, 1000));
        m_produced_electricity =
            Resource(ResourceType::ELECTRICITY, Unit::WATT,
                     Random::GenerateRandomInteger(100, 1000));
    }
}

Building::Building(string name, string type)
    : Building(name, type, Building::g_building_id++) {}

Building::Building(string type)
    : Building(Building::GenerateBuildingName(type), type,
               Building::g_building_id++) {}

std::string Building::GenerateBuildingName(std::string type) {
    static std::array random_adjectives{"Beautiful", "Amazing", "Great",
                                        "Wonderful", "Ordinary"};

    return std::format("{} {}",
                       random_adjectives[Random::GenerateRandomInteger(
                           0, random_adjectives.size() - 1)],
                       type);
}

void Building::ShowBuildingDetails(void) {
    std::println(
        "ID: {}\n"
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

void City::ModifyPollutionLevel(i32 pollution_level) {
    m_pollution_level += pollution_level;
    if (m_pollution_level < 0) {
        m_pollution_level = 0;
    }
}

void City::ModifyPopulation(i32 population) {
    m_population += population;
    if (m_population < 0) {
        m_population = 0;
    }
}

void City::ModifySatisfactionLevel(i32 satisfaction_level) {
    m_satisfaction_level += satisfaction_level;
    if (m_satisfaction_level < 0) {
        m_satisfaction_level = 0;
    }
}

City::City(string name) { m_name = name; }

City::City(void) {
    static std::array random_adjectives{"Beautiful", "Amazing", "Great",
                                        "Wonderful", "Ordinary"};
    m_name =
        std::format("{} City", random_adjectives[Random::GenerateRandomInteger(
                                   0, random_adjectives.size() - 1)]);
    m_consumed_water = Resource(ResourceType::WATER, Unit::LITER, 0);
    m_consumed_electricity = Resource(ResourceType::ELECTRICITY, Unit::WATT, 0);
    m_produced_water = Resource(ResourceType::WATER, Unit::LITER, 0);
    m_produced_electricity = Resource(ResourceType::ELECTRICITY, Unit::WATT, 0);
}

void City::AddBuilding(Building building) {
    m_buildings.push_back(building);
    ModifyPollutionLevel(building.m_pollution_effect);
    ModifySatisfactionLevel(building.m_satisfaction_effect);
    ModifyPopulation(building.m_inhabitant_count);
    m_consumed_water += building.m_consumed_water;
    m_consumed_electricity += building.m_consumed_electricity;
    m_produced_water += building.m_produced_water;
    m_produced_electricity += building.m_produced_electricity;
}

void City::ModifyBuilding(i32 id, Building new_building) {
    for (auto& building : m_buildings) {
        if (building.m_id == id) {
            building = new_building;
            building.m_id = id;
            // for good measure.
        }
    }
}

void City::RemoveBuilding(i32 id) {
    for (auto it{m_buildings.begin()}; it != m_buildings.end(); ++it) {
        if (it->m_id != id) continue;

        ModifyPollutionLevel(-it->m_pollution_effect);
        ModifySatisfactionLevel(-it->m_satisfaction_effect);
        ModifyPopulation(-it->m_inhabitant_count);
        m_consumed_water -= it->m_consumed_water;
        m_consumed_electricity -= it->m_consumed_electricity;
        m_produced_water -= it->m_produced_water;
        m_produced_electricity -= it->m_produced_electricity;
        m_buildings.erase(it);
        break;
    }
}

Building City::SearchBuilding(i32 id) {
    for (auto& building : m_buildings) {
        if (building.m_id == id) {
            return building;
        }
    }
    return Building(BuildingType::NONE, BuildingType::NONE, 0);
}

void City::ProduceResources(void) {
    for (auto& building : m_buildings) {
        m_produced_water += building.m_produced_water;
        m_produced_electricity += building.m_produced_water;
    }
}

void City::ConsumeResources(void) {
    for (auto& building : m_buildings) {
        m_consumed_water += building.m_consumed_water;
        m_consumed_electricity += building.m_consumed_electricity;
        m_produced_water -= building.m_consumed_water;
        m_produced_electricity -= building.m_consumed_electricity;
    }
}
