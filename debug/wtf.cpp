#include <print>
#include <algorithm>

#define BAD_BLOCK 

struct Block {
    int size;
    int height;
    int width;
    int breadth;
};

static Block bad_block {-1, -1, -1, -1};

Block operator&&(const Block& block, bool boolean) {
    if (boolean) {
        return block;
    } else {
        return ::bad_block;
    }
}

bool operator==(const Block& block_1, const Block& block_2) {
    return block_1.size == block_2.size &&
           block_1.height == block_2.height &&
           block_1.width == block_2.width &&
           block_1.breadth == block_2.breadth;
}

template<class InputIt, class T>
bool find(InputIt first, InputIt last, const T& value) {
    if (auto result {std::find(first, last, value)
}

int main(void) {
    auto list = {1, 2, 3, 4, 5};
    std::println("{}",
                 *std::find(list.begin(), 
                            list.end(), 
                            100));
}
