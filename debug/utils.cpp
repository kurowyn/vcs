#include <raylib.h>
#include <print>
#include "utils.hpp"

int main(void) {
    int width {1280};
    int height {720};
    int image_width {50};
    int image_height {50};
    std::initializer_list<std::string> image_paths {
                        "../assets/neon_add_button.png"
                        "../assets/neon_remove_button.png"
                        "../assets/neon_view_button.png"
    };
    auto positions = {
                        Vector2(width - image_width - 10, height - 3 * image_height - 30),
                        Vector2(width - image_width - 10, height - 2 * image_height - 20),
                        Vector2(width - image_width - 10, height - image_height - 10)
    };

    auto textures {Assets::LoadPositionedImages(image_paths, positions)};
}
