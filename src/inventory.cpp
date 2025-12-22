#include <print>
#include <vector>
#include <string>

using i32 = std::int32_t;
using std::vector;
using std::string;

struct Resource {
    string m_type {};
    string m_unit {};
    i32 m_quantity {};
    Resource(string type, string unit, i32 quantity) {
        m_type = type;
        m_unit = unit;
        m_quantity = quantity;
    }
};

int main(void) {
    return 0;
}
