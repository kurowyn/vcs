#include "building.hpp"

int main(void) {
    Resource r1 {ResourceType::WATER, Unit::LITER, 100};
    Resource r2 {ResourceType::WATER, Unit::LITER, 100};
    r1 += r2;
    std::println("{}, {}, {}", r1.m_type, r1.m_unit, r1.m_quantity);
}
