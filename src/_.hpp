#ifndef BUILDING_H
#define BUILDING_H

#include <stdfloat>
#include <string>
#include <vector>

using i32 = int;
using f32 = float;

class Building {
   protected:
    i32 m_id{};  // but this may not necessarily be an i32.
    std::string m_name{};
    std::string m_type{};  // but this could be better: enum.

    f32 m_water_consumption{};
    f32 m_power_consumption{};
    f32 m_satisfaction_effect{};  // whatever this means.
   public:
    void show_information(void) const;
    f32 get_resource_consumption(void) const;
};

class House : private Building {
   private:
    i32 m_capacity;
    i32 m_current_resident_count;

   public:
    void add_resident(i32 count);
    void remove_resident(i32 count);
};

class Factory : private Building {
   private:
    // But this might be something else, other than a simple string vector.
    std::vector<std::string> m_produced_resources{};
    f32 m_pollution_rate;

   public:
    void produce_resources(void);
    f32 calculate_pollution(void) const;
};

class Park : private Building {
   private:
    std::pair<f32, f32> m_area{};
    // But this might be better expressed using something other than a float.
    f32 m_wellbeing_effect{};

   public:
    void improve_wellbeing(void);  // not sure how to implement this. RNG?
};

class Resource {
   private:
    std::string m_name{};

   public:
    void show(void) const;
};

class City {
   private:
    std::vector<Building> m_building_list{};
    std::vector<std::string> m_resource_list{};  // this could be better.
    std::string m_name;
    f32 m_budget;
    i32 m_population;
    // But this might be better expressed using something other than a float,
    // too.
    f32 m_satisfaction_level;

   public:
    void add_building(Building b);
    void remove_building(i32 id);
    f32 calculate_total_consumption(void) const;
    f32 calculate_satisfaction_level(void) const;
};

class Event {
    // whatever this may be.
    // it seems that we can interpret it this way, though:
    // an event can be either:
    // - negative (it benefits the inhabitants of the city, increasing the
    // overall satisfaction level)
    // - positive (the opposite of the above). sometimes, the positive is used
    // to mitigate the effects of a negative event that has already occurred.
    // perhaps in the future, we may even allow the creation of custom events.
};

class Simulation {
   private:
    // a cycle "ID", I guess. Could be better, again.
    i32 m_current_cycle{};
    Event m_event{};
    City m_city{};

   public:
    void begin();
    void end();
    void start_event(Event e);
};

#endif
