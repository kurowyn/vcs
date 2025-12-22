#include <chrono>
#include <thread>
#include <print>

int main(void) {
    using namespace std::chrono_literals;
    using namespace std::chrono;
    using std::this_thread::sleep_for;
    auto t1 {steady_clock::now()};
    sleep_for(5s);
    auto t2 {steady_clock::now()};
    std::println("{}", duration_cast<seconds>(t2 - t1).count());
    return 0;
}
