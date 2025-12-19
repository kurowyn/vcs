#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif

#include <iostream>

#include "./classes/simulation.hpp"

int tickSpeed = 1000;  // every tickSpeed milliseconds

void sleep_ms(int milliseconds) {
#ifdef _WIN32
    Sleep(milliseconds);
#else
    sleep(milliseconds * 1000);
#endif
}

auto main(int argc, char** argv) -> int {
    Simulation sim;
    sim.prompt_chose_city();

    int lastTickAt = GetTickCount();
    while (true) {
        City* runningCity = sim.get_running_city();

        if (runningCity == nullptr) {
            std::cerr << "No running city selected. Exiting." << std::endl;
            return 1;
        }

        int currentTime = GetTickCount();
        if (currentTime - lastTickAt < tickSpeed) continue;
        lastTickAt = currentTime;
        int dt = currentTime - lastTickAt;

        runningCity->tick(dt);

        sleep_ms(tickSpeed);
        std::cout << "Ticked city: " << runningCity->name << std::endl;
    }

    return 0;
}
