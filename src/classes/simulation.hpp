#pragma once
#include <iostream>
#include <vector>

#include "classes/city.hpp"

class Simulation {
   public:
    vector<City*> cities;

    City* runningCity = nullptr;

    Simulation();
    ~Simulation();

    void add_city(string name);

    void prompt_chose_city();
    City* get_running_city();

   private:
    void set_running_city(int index);
    void load_saved_cities();
};
