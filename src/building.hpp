#include "common.hpp"

i32 g_building_id {0};


struct Resource {
    string m_type {};
    string m_unit {};
    i32 m_quantity {};

    Resource(string type, string unit, i32 quantity) {
        m_type = type;
        m_unit = unit;
        m_quantity = quantity;
    }

    static Resource CreateRandomResource(void) {
        return Resource(
                Common::random_word_generator(), 
                Common::random_word_generator(),
                Common::random_i32_generator()
        );
    }

    static vector<Resource> CreateRandomResourceList(i32 count = 3) {
        auto resource_list {vector<Resource>{}};
        resource_list.reserve(count);
        while (count-- != 0) {
            resource_list.push_back(Resource::CreateRandomResource());
        }
        return resource_list;
    }
};

class Building {
    public:
        i32 m_id {};
        i32 m_satisfaction_effect {};
        i32 m_pollution_effect {};
        string m_name {};
        string m_type {};
        vector<Resource> m_consumed_resources {};
        vector<Resource> m_required_resources {};

        explicit Building(void) {}

        static Building CreateBuilding(i32 id = 0, string name = "Building Name", 
                string type = "Building Type", const vector<Resource>& consumed_resources = {},
                const vector<Resource>& required_resources = {}, i32 satifaction_effect = 0, 
                i32 pollution_effect = 0) {
            Building b {};
            b.m_id = id;
            b.m_name = name;
            b.m_type = type;
            b.m_consumed_resources = consumed_resources;
            b.m_required_resources = required_resources;
            b.m_satisfaction_effect = satifaction_effect;
            b.m_pollution_effect = pollution_effect;
            return b;
        }

        static Building CreateRandomBuilding(void) {
            return Building::CreateBuilding(
                    Common::random_i32_generator(),
                    Common::random_word_generator(),
                    Common::random_word_generator(), 
                    Resource::CreateRandomResourceList(),
                    Resource::CreateRandomResourceList(),
                    Common::random_i32_generator(),
                    Common::random_i32_generator()
            );
        }

        static Building CreateBuilding(string name = "Building Name", string type = "Building Type", 
                const vector<Resource>& consumed_resources = {},
                const vector<Resource>& required_resources = {}, i32 satifaction_effect = 0, 
                i32 pollution_effect = 0) {
            return Building::CreateBuilding(
                    ::g_building_id++,
                    name,
                    type,
                    consumed_resources,
                    required_resources,
                    satifaction_effect,
                    pollution_effect
            );
        }

        static Building CreateBuilding(string name = "Building Name", 
                string type = "Building Type") {
            return Building::CreateBuilding(
                    name, 
                    type, 
                    Building::ResolveConsumedResources(type),
                    Building::ResolveRequiredResources(type), 
                    Building::ResolveSatisfactionEffect(type), 
                    Building::ResolvePollutionEffect(type)
            );
        }

        // These 4 statics will probably use a std::map.
        static vector<Resource> ResolveRequiredResources(string building_type) {
            // TODO: based on the building_type given, return the right required resources.
            return {};
        }

        static vector<Resource> ResolveConsumedResources(string building_type) {
            // TODO: based on the building_type given, return the right consumed resources.
            return {};
        }

        static i32 ResolveSatisfactionEffect(string building_type) {
            // TODO: based on the building_type given, return the right satisfaction effect.
            return 0;
        }

        static i32 ResolvePollutionEffect(string building_type) {
            // TODO: based on the building_type given, return the right pollution effect.
            return 0;
        }

        void ShowBuildingDetails(void) {
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
            print("Built using these resources: ");
            if (!m_required_resources.empty()) {
                print("\n");
                for (const auto& resource: m_required_resources) {
                    print("{}, {} {}(s)\n", resource.m_type,
                            resource.m_quantity,
                            resource.m_unit);
                }
            } else {
                println("None");
            }
        }

        Building& WithName(string name = "Building Name") {
            this->m_name = name;
            return *this;
        }

        Building& WithType(string type = "Building Type") {
            this->m_type = type;
            return *this;
        }

        Building& WithConsumedResources(const vector<Resource>& consumed_resources = {}) {
            this->m_consumed_resources = consumed_resources;
            return *this;
        }

        Building& WithRequiredResources(const vector<Resource>& required_resources = {}) {
            this->m_required_resources = required_resources;
            return *this;
        }

        Building& WithSatisfactionEffect(i32 satifaction_effect) {
            this->m_satisfaction_effect = satifaction_effect;
            return *this;
        }

        Building& WithPollutionEffect(i32 pollution_effect) {
            this->m_pollution_effect = pollution_effect;
            return *this;
        }
};
