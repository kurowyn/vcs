#include <print>

int main(void) {
    int x {0};
    std::println("x {}", x);
    auto f {[&x]() {x = 100;}};
    f();
    std::println("x {}", x);
}
