#include <print>
#include <array>

void f(std::initializer_list<int> array) {
    for (const auto& element: array) {
        std::println("{}", element);
    }
}

int main(void) {
    f({1, 2, 3, 4, 5, 6});
}
