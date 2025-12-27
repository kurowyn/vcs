#include <raylib.h>
#include <vector>
#include "box.hpp"
#include <print>

#define ASSET_PATH "../assets/button_assets/"

int main(void) {
    InitWindow(800, 600, "Test");
    SetTargetFPS(60);

    std::array<Texture2D, 3> textures {LoadTexture(ASSET_PATH"neon_add_button.png"), 
                                       LoadTexture(ASSET_PATH"neon_remove_button.png"),
                                       LoadTexture(ASSET_PATH"neon_view_button.png")};

    std::vector<Box> boxes {{.m_texture = textures[0],
                             .m_rectangle = Rectangle(0, 0, textures[0].width, textures[0].height),
                             .m_is_hoverable = false,
                             .m_hovered_color = WHITE,
                             .m_unhovered_color = WHITE},
                            {.m_texture = textures[1],
                             .m_rectangle = Rectangle(textures[0].width, 
                                                      textures[0].height, 
                                                      textures[1].width, 
                                                      textures[1].height),
                             .m_is_hoverable = false,
                             .m_hovered_color = WHITE,
                             .m_unhovered_color = WHITE},
                            {.m_texture = textures[2],
                             .m_rectangle = Rectangle(textures[0].width + textures[1].width, 
                                                      textures[0].height + textures[1].height, 
                                                      textures[2].width, 
                                                      textures[2].height),
                             .m_is_hoverable = false,
                             .m_hovered_color = WHITE,
                             .m_unhovered_color = WHITE}};

    while (!WindowShouldClose()) {
        auto mouse_position {GetMousePosition()};
        static auto in_count {0};
        BeginDrawing();
        for (auto& box: boxes) {
            box.Draw();
            if (CheckCollisionPointRec(mouse_position, box.m_rectangle)) {
                box.m_texture = textures[in_count++ % 3];
            }
        }
        EndDrawing();
    }

    CloseWindow();
    
    return 0;
}
