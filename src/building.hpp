#ifndef BUILDING_H
#define BUILDING_H

class Building {
    protected:
        std::int64_t m_id;
        std::string m_name;
        std::string m_type;
        std::float64_t m_water_consumption;
        std::float64_t m_electricity_consumption;
        std::float64_t satisfaction_rate; 
    public:
        void show_information(void) const;
        std::float64_t calculate_resource_impact(void) const;
};

class House:private Building

#endif

