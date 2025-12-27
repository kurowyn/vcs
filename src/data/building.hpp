#ifndef BUILDING_HPP
#define BUILDING_HPP

#include <iostream>
#include <vector>
#include <stdfloat>
#include <print>
#include <map>
#include <random>

using i32 = std::int32_t;
using f32 = std::float32_t;
using mersenne_twister = std::mt19937;
using std::uniform_int_distribution;
using std::random_device;
using std::string;
using std::string_view;
using std::vector;
using std::initializer_list;
using std::print;
using std::println;
using std::map;
using std::optional;

extern i32 g_building_id;

struct Resource {
    string m_type {};
    string m_unit {};
    i32 m_quantity {};
    Resource(string type, string unit, i32 quantity);
    static Resource CreateRandomResource(void);
    static vector<Resource> CreateRandomResourceList(i32 count = 3);
};

class Building {
    public:
        i32 m_id {};
        i32 m_satisfaction_effect {};
        i32 m_pollution_effect {};
        string m_name {};
        string m_type {};
        vector<Resource> m_consumed_resources {};

        explicit Building(void) {}

        static Building CreateEmptyBuilding(string name = "Building Name");
        static Building CreateBuilding(i32 id = 0, string name = "Building Name", 
                                       string type = "Building Type", 
                                       const vector<Resource>& consumed_resources = {},
                                       i32 satifaction_effect = 0, i32 pollution_effect = 0);
        static Building CreateBuilding(string name = "Building Name", 
                                       string type = "Building Type", 
                                       const vector<Resource>& consumed_resources = {},
                                       i32 satifaction_effect = 0, i32 pollution_effect = 0);
        static Building CreateBuilding(string name = "Building Name", 
                                       string type = "Building Type");
        static Building CreateRandomBuilding(void);
        static vector<Resource> ResolveConsumedResources(string building_type);
        static i32 ResolveSatisfactionEffect(string building_type);
        static i32 ResolvePollutionEffect(string building_type);
        void ShowBuildingDetails(void);
};

#endif // BUILDING_HPP
