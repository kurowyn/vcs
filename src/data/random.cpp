#include "random.hpp"

namespace Random {
    string GenerateRandomWord(int32_t length = 5, string vowels = "bcdfghjklmnpqrstvwxyz",
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
    i32 GenerateRandomInteger(i32 lower = 0, i32 upper = std::numeric_limits<i32>::max()) {
        static mersenne_twister generator {random_device{}()};

        uniform_int_distribution number {lower, upper};

        return number(generator);
    }
};
