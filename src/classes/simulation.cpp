#include "./simulation.hpp"

Simulation::Simulation() {}

Simulation::~Simulation() {}

void Simulation::add_city(string name) {
    City* newCity = new City(name);

    this->cities.push_back(newCity);
}

City* Simulation::get_running_city() { return this->runningCity; }

void Simulation::set_running_city(int index) {
    if (index < 0 || index >= this->cities.size()) {
        std::cerr << "Index out of bounds when setting running city!"
                  << std::endl;
        return;
    }

    this->runningCity = this->cities[index];
}

/**
 * Prompts the user to choose a city from the list of available cities.
 * If no cities are available, prompts the user to create a new city.
 * If the user chooses to create a new city, it asks for the city name
 * and adds it to the simulation.
 */
void Simulation::prompt_chose_city() {
    if (this->cities.empty()) {
        char choice;
        std::cout << "No cities.create one?  " << std::endl;
        std::cin >> choice;

        if (!(choice == 'y' || choice == 'Y')) exit(0);

        std::string cityName;
        std::cout << "Enter city name: ";
        std::cin >> cityName;
        this->add_city(cityName);
        this->set_running_city(0);

        return;
    }

    std::cout << "Choose a city by its index:" << std::endl;

    for (size_t i = 0; i < this->cities.size(); ++i)
        std::cout << i << ": " << this->cities[i]->name << std::endl;

    int choice = -1;
    std::cin >> choice;

    while (choice < 0 || choice >= this->cities.size()) {
        std::cerr << "Invalid choice. Please choose a valid city index: "
                  << std::endl;
        std::cin >> choice;
    }

    this->set_running_city(choice);
}

void Simulation::load_saved_cities() {
    // Placeholder for future implementation
}