#ifndef COMMON_HPP
#define COMMON_HPP

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

#endif // COMMON_HPP
