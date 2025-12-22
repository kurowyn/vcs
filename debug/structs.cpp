#include <print>

struct S {
    int x {};
    int y {};
};

int main(void) {
    std::array<S, 4> l {{{10, 10}, {20, 20}, {30, 40}}};
}
