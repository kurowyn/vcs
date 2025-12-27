#include <print>

int main(void) {
    int x {100}, y {200};
    auto capture {[&x, &y]() {++x; ++y;}};
    capture();
    std::println("{}, {}", x, y);
}
