#include "building.hpp"

namespace BuildingType {
    constexpr string HOUSE = "House";
    constexpr string FACTORY = "Factory";
    constexpr string SERVICE = "Service";
    constexpr string PARK = "Other";
    constexpr string OTHER = "Custom";
    constexpr string UNKNOWN = "Unknown";
};

namespace ResourceType {
    constexpr string WATER = "Water";
    constexpr string ELECTRICITY = "Electricity";
    constexpr string WOOD = "Wood";
    constexpr string IRON = "Wood";
    constexpr string GLASS = "GLASS";
    constexpr string UNKNOWN = "Unknown";
};

namespace Unit {
    constexpr string LITER = "Liter";
    constexpr string KILOGRAM = "Kilogram";
    constexpr string PIECE = "Piece";
    constexpr string WATT = "Watt";
    constexpr string UNKNOWN = "Unknown";
};

namespace Common {
    string random_word_generator(int32_t length = 5, 
                                 string vowels = "bcdfghjklmnpqrstvwxyz",
                                 string consonants = "aieuo") {
        static mersenne_twister generator {random_device{}()};

        uniform_int_distribution vowel_id {0, static_cast<int>(vowels.size()) - 1};
        uniform_int_distribution consonant_id {0, static_cast<int>(consonants.size()) - 1};
        uniform_int_distribution vowel_or_consonant {1, 2};

        string random_string {};
        random_string.reserve(length);

        for (auto i {0}; i < length; ++i) {
            random_string += i % 2 == 0 ?
                             vowels[vowel_id(generator)] :
                             consonants[consonant_id(generator)];
        }

        random_string[0] = std::toupper(random_string[0]);

        return random_string;
    }

    i32 random_i32_generator(i32 lower = 0, i32 upper = std::numeric_limits<i32>::max()) {
        static mersenne_twister generator {random_device{}()};

        uniform_int_distribution number {lower, upper};

        return number(generator);
    }
};

i32 g_building_id {1};

Resource::Resource(string type, string unit, i32 quantity) {
    m_type = type;
    m_unit = unit;
    m_quantity = quantity;
}

Resource Resource::CreateRandomResource(void) {
    return Resource(Common::random_word_generator(), 
            Common::random_word_generator(),
            Common::random_i32_generator());
}

vector<Resource> Resource::CreateRandomResourceList(i32 count) {
    auto resource_list {vector<Resource>{}};
    resource_list.reserve(count);
    while (count-- != 0) {
        resource_list.push_back(Resource::CreateRandomResource());
    }
    return resource_list;
}

Building Building::CreateEmptyBuilding(string name) {
    return Building::CreateBuilding(0,
                                    name,
                                    BuildingType::UNKNOWN,
                                    {},
                                    0,
                                    0);
}

Building Building::CreateBuilding(i32 id, string name, string type, 
                                  const vector<Resource>& consumed_resources,
                                  i32 satifaction_effect, i32 pollution_effect) {
    Building b {};
    b.m_id = id;
    b.m_name = name;
    b.m_type = type;
    b.m_consumed_resources = consumed_resources;
    b.m_satisfaction_effect = satifaction_effect;
    b.m_pollution_effect = pollution_effect;
    return b;
}

Building Building::CreateRandomBuilding(void) {
    return Building::CreateBuilding(Common::random_i32_generator(),
                                    Common::random_word_generator(),
                                    Common::random_word_generator(), 
                                    Resource::CreateRandomResourceList(),
                                    Common::random_i32_generator(),
                                    Common::random_i32_generator());
}

Building Building::CreateBuilding(string name, string type, 
                                  const vector<Resource>& consumed_resources,
                                  i32 satifaction_effect, i32 pollution_effect) {
    return Building::CreateBuilding(::g_building_id++,
                                    name,
                                    type,
                                    consumed_resources,
                                    satifaction_effect,
                                    pollution_effect);
}

Building Building::CreateBuilding(string name, string type) {
    return Building::CreateBuilding(name, 
                                    type, 
                                    Building::ResolveConsumedResources(type),
                                    Building::ResolveSatisfactionEffect(type), 
                                    Building::ResolvePollutionEffect(type));
}

vector<Resource> Building::ResolveConsumedResources(string building_type) {
    // TODO: based on the building_type given, return the right consumed resources.
    return {};
}

i32 Building::ResolveSatisfactionEffect(string building_type) {
    // TODO: based on the building_type given, return the right satisfaction effect.
    return 0;
}

i32 Building::ResolvePollutionEffect(string building_type) {
    // TODO: based on the building_type given, return the right pollution effect.
    return 0;
}

void Building::ShowBuildingDetails(void) {
    print("ID: {}\n"
            "Name: {}\n"
            "Type: {}\n"
            "Satisfaction Effect: {}\n"
            "Pollution Effect: {}\n"
            "Consumed Resources: \n",
            m_id, m_name, m_type, m_satisfaction_effect, 
            m_pollution_effect);
    // DRY: Do Repeat Yourself.
    if (!m_consumed_resources.empty()) {
        for (const auto& resource: m_consumed_resources) {
            print("{}, {} {}(s)\n", resource.m_type,
                    resource.m_quantity,
                    resource.m_unit);
        }
    } else {
        println("None");
    }
}
