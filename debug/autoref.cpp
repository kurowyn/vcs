#include <print>
#include <vector>

int main(void) {
    std::vector<int> list {10, 100, 1000, 2000, 4000};
    for (auto& x: list) {
        x += 10;
    }

    for (const auto& x: list) {
        std::println("{}", x);
    }
}
