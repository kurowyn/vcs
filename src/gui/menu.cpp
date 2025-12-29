#include "box.hpp"
#include <map>
#include <utility>
#include <print>
#include <array>
#include <raylib.h>

enum class Mode {
    SELECT_BUILDING_TO_ADD = 1,
    SELECT_SQUARE_TO_ADD_TO,
    SELECT_SQUARE_TO_REMOVE_FROM,
    SELECT_SQUARE_TO_VIEW,
};


int main(void) {
    const auto WIDTH {1366};
    const auto HEIGHT {768};
    const auto PADDING {10};

    auto mode {Mode::SELECT_SQUARE_TO_VIEW};
    char* building_selected {"None"};

    InitWindow(WIDTH, HEIGHT, "Demo");

    SetTargetFPS(120);

    std::array images {LoadImage("../assets/button_assets/neon_view_button.png"),
                       LoadImage("../assets/button_assets/neon_remove_button.png"),
                       LoadImage("../assets/button_assets/neon_add_button.png"),
                       LoadImage("../assets/house_assets/house_1.png"),
                       LoadImage("../assets/factory_assets/factory_1.png"),
                       LoadImage("../assets/park_assets/park_1.png")};

    const std::array<const char*, 6> BUTTON_NAMES {"View", "Remove", "Add", "House", "Factory", "Park"};

    std::map<const char*, Box> boxes {};

    for (auto& image: images) {
        ImageAlphaCrop(&image, 0.0f);
        ImageResizeNN(&image, 50, image.height * 50 / image.width);
    }

    for (auto row {0}; row < 6; ++row) {
        static Vector2 position {WIDTH - images[row].width - PADDING, HEIGHT};
        position.y -= PADDING + images[row].height;
        boxes[BUTTON_NAMES[row]] = Box()
                                   .with_texture(LoadTextureFromImage(images[row]))
                                   .with_rectangle(Rectangle(position.x
                                                             position.y,
                                                             images[row].width,
                                                             images[row].height))
                                   .with_is_hoverable(true)
                                   .with_hovered_color(SKYBLUE)
                                   .with_unhovered_color(WHITE);
    }

    boxes["House"].m_unhovered_color = boxes["Factory"].m_unhovered_color = boxes["Park"].m_unhovered_color = BLANK;
    boxes["House"].m_hovered_color = boxes["Factory"].m_hovered_color = boxes["Park"].m_hovered_color = BLANK;

    while (!WindowShouldClose()) {
        auto mouse_position {GetMousePosition()};
        auto mouse_wheel {GetMouseWheelMove()};

        if (boxes["Add"].IsClicked(mouse_position, MOUSE_LEFT_BUTTON)) {
            if (mode != Mode::SELECT_SQUARE_TO_ADD_TO) {
                boxes["House"].m_unhovered_color = 
                boxes["Factory"].m_unhovered_color =
                boxes["Park"].m_unhovered_color = Fade(WHITE, 0.25f);

                boxes["House"].m_hovered_color =
                boxes["Factory"].m_hovered_color =
                boxes["Park"].m_hovered_color = WHITE;

                mode = Mode::SELECT_BUILDING_TO_ADD;
            }
        } else if (boxes["Remove"].IsClicked(mouse_position, MOUSE_LEFT_BUTTON)) {
            boxes["House"].m_unhovered_color = boxes["Factory"].m_unhovered_color = boxes["Park"].m_unhovered_color = BLANK;
            boxes["House"].m_hovered_color = boxes["Factory"].m_hovered_color = boxes["Park"].m_hovered_color = BLANK;
            mode = Mode::SELECT_SQUARE_TO_REMOVE_FROM;
        } else if (boxes["View"].IsClicked(mouse_position, MOUSE_LEFT_BUTTON)) {
            boxes["House"].m_unhovered_color = boxes["Factory"].m_unhovered_color = boxes["Park"].m_unhovered_color = BLANK;
            boxes["House"].m_hovered_color = boxes["Factory"].m_hovered_color = boxes["Park"].m_hovered_color = BLANK;
            mode = Mode::SELECT_SQUARE_TO_VIEW;
        } 

        for (auto& [role, box]: boxes) {
            if (role == "House" || role == "Factory" || role == "Park") {
                if (box.IsClicked(mouse_position, MOUSE_LEFT_BUTTON)) {
                    mode = Mode::SELECT_SQUARE_TO_ADD_TO;

                    boxes["House"].m_unhovered_color = Fade(WHITE, 0.25f);
                    boxes["Factory"].m_unhovered_color = Fade(WHITE, 0.25f);
                    boxes["Park"].m_unhovered_color = Fade(WHITE, 0.25f);
                    box.m_unhovered_color = WHITE;

                    building_selected = const_cast<char*>(role);
                }
            }
        }

        BeginDrawing();

        ClearBackground(DARKBROWN);
        for (auto& [role, box]: boxes) {
            box.Draw(mouse_position);
        }

        switch (mode) {
            case Mode::SELECT_BUILDING_TO_ADD:
                DrawText("SELECT A BUILDING TO ADD!", 0, 0, 30, WHITE);
                break;
            case Mode::SELECT_SQUARE_TO_ADD_TO:
                DrawText(TextFormat("YOU SELECTED: %s", building_selected), 0, 0, 30, WHITE);
                DrawText("SELECT A SQUARE TO PLACE THE BUILDING ON!", 0, 50, 30, WHITE);
                break;
            case Mode::SELECT_SQUARE_TO_REMOVE_FROM:
                DrawText("SELECT A BUILDING TO REMOVE!", 0, 0, 30, WHITE);
                break;
            case Mode::SELECT_SQUARE_TO_VIEW:
                DrawText("SELECT A BUILDING TO VIEW!", 0, 0, 30, WHITE);
                break;
        }

        EndDrawing();
    }

    CloseWindow();

    return 0;
}
