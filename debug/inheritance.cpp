#include <print>

class A {
    public:
        A(void) {
            std::println("[INFO] A() Called.");
        }
        int x {}, y {};
        int f(void) {
            std::println("[INFO] A.f() Called.");
            auto count {x * y};
            for (auto i = 0; i < count; ++i) {
                std::print("A");
            }
            return count;
        }
};

class B:public A {
    public:
        B(void) { 
            std::println("[INFO] B() Called.");
        }
        B(int z, int w) { 
            std::println("[INFO] B(int, int) Called.");
            this->z = z;
            this->w = w;
        }
        int z {}, w {};
        int f(void) {
            std::println("[INFO] B.f() Called.");
            auto count {z * w};
            for (auto i = 0; i < count; ++i) {
                std::print("B");
            }
            return count;
        }
};

int main(void) {
    B b {10, 10};
    B& rb = b;
    A& a {rb};
    a.f();
}
