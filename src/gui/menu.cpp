#include "box.hpp"
#include <raylib.h>
#include <array>

int main(void) {
    InitWindow(1280, 720, "Menu");

    SetTargetFPS(60);

    auto t1 {LoadTexture("../assets/house_assets/house_1.png")};
    auto t2 {LoadTexture("../assets/factory_assets/factory_1.png")};
    auto t3 {LoadTexture("../assets/park_assets/park_1.png")};

    std::array<Box, 3> choices {Box{.m_texture = t1,
                                    .m_rectangle = Rectangle(0, 
                                                             0, 
                                                             t1.width, 
                                                             t1.height),
                                    .m_is_hoverable = true,
                                    .m_hovered_color = Fade(BLACK, 0.95f),
                                    .m_unhovered_color = WHITE},
                                Box{.m_texture = t2,
                                    .m_rectangle = Rectangle(t1.width + 10, 
                                                             0, 
                                                             t2.width, 
                                                             t2.height),
                                    .m_is_hoverable = true,
                                    .m_hovered_color = Fade(BLACK, 0.95f),
                                    .m_unhovered_color = WHITE},
                                Box{.m_texture = t3,
                                    .m_rectangle = Rectangle(2 * t2.width + 20, 
                                                             0, 
                                                             t3.width, 
                                                             t3.height),
                                    .m_is_hoverable = true,
                                    .m_hovered_color = Fade(BLACK, 0.95f),
                                    .m_unhovered_color = WHITE}};

    unsigned int choice {0};
    while (!WindowShouldClose()) {
        auto mouse_position {GetMousePosition()};

        BeginDrawing();

        ClearBackground(WHITE);

        DrawText("Choose A Building To Place!", 
                 300,
                 100,
                 30,
                 PURPLE);

        DrawText(TextFormat("Choice: %i", choice),
                 300,
                 150,
                 30,
                 PURPLE);

        for (auto& box: choices) {
            box.Draw(mouse_position, MOUSE_BUTTON_LEFT);
            if (box.IsClicked(mouse_position, MOUSE_BUTTON_LEFT)) {
                choice = box.m_texture.id;
            }
        }

        EndDrawing();
    }

    CloseWindow();

    return 0;
}
