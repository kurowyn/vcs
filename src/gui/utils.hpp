#ifndef UTILS_H
#define UTILS_H

#define WITH_CONSTRUCTOR(struct_type, attribute_type, argument_name)  \
    struct_type& with_##argument_name(attribute_type argument_name) { \
        m_##argument_name = argument_name;                            \
        return *this;                                                 \
    }

#include <raylib.h>

#include <print>
#include <string>
#include <vector>

#endif  // UTILS_H
