#include <iostream>

#include "buildings/factory/factory.hpp"
#include "buildings/house/house.hpp"
#include "buildings/park/park.hpp"

auto main(int argc, char** argv) -> int {
    Factory myFactory;
    House myHouse;
    Park myPark;

    std::cout << "compiled :3";

    return 0;
}
