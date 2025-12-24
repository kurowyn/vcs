#include <print>
#include <vector>
#include <tuple>

int main(void) {
    std::vector<std::tuple<int, std::string>> a {{10, "Hello"}, {20, "Pointer"}};
    std::get<int>(a[0]) = 300;
    std::println("{}", std::get<int>(a[0]));
}
