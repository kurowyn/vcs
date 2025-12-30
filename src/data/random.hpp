#ifndef RANDOM_HPP
#define RANDOM_HPP

#include "common.hpp"

namespace Random {
string GenerateRandomWord(int32_t length, string vowels, string consonants);
i32 GenerateRandomInteger(i32 lower, i32 upper);
};  // namespace Random

#endif  // RANDOM_HPP
