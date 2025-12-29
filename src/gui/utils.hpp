#ifndef UTILS_H
#define UTILS_H

#define WITH_CONSTRUCTOR(struct_type, attribute_type, argument_name)      \
    struct_type& with_##argument_name(attribute_type argument_name) {     \
        m_##argument_name = argument_name;                                  \
        return *this;                                                     \
    }                                                                     

#endif // UTILS_H
