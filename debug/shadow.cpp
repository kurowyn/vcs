#include <print>

void f(int n = 3) {
    std::println("{}", n);
}

void f(void) {
    int n {3};
    std::println("{}", n);
}

int main(void) {
    f();
}
