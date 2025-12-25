#include <raylib.h>
#include <functional>
#include <print>
#include <array>

struct Box {
    // This entire thing is horrible. Do not use it in production.
    // This is only for a small college project.
    Texture2D& m_texture;
    Rectangle m_rectangle {};
    Color m_hover_color {};
    std::function<void(void)> m_call_back {};

    inline void operator()(Vector2 mouse_position, MouseButton mouse_button) {
        if (this->IsClicked(mouse_position, mouse_button)) {
            m_call_back();
        }
    }

    inline bool IsClicked(MouseButton mouse_button = MOUSE_LEFT_BUTTON) {
        return this->IsHovered(GetMousePosition()) && IsMouseButtonPressed(mouse_button);
    }

    inline bool IsClicked(Vector2 mouse_position, MouseButton mouse_button) {
        return this->IsHovered(mouse_position) && IsMouseButtonPressed(mouse_button);
    }

    inline bool IsHovered(void) {
        return CheckCollisionPointRec(GetMousePosition(), m_rectangle);
    }

    inline bool IsHovered(Vector2 mouse_position) {
        return CheckCollisionPointRec(mouse_position, m_rectangle);
    }
};

int main(void) {
    const unsigned int EMPTY_TEXTURE_ID {0};
    Texture2D EMPTY_TEXTURE {};
    Color background_color {GRAY};
    InitWindow(800, 600, "Box Demo");


    std::array boxes {Box(EMPTY_TEXTURE,
                          Rectangle(10, 10, 100, 100),
                          YELLOW,
                          [&background_color]() {background_color = WHITE;}),
                      Box(EMPTY_TEXTURE,
                          Rectangle(120, 10, 100, 100),
                          YELLOW,
                          [&background_color]() {background_color = PURPLE;}),
                      Box(EMPTY_TEXTURE,
                          Rectangle(230, 10, 100, 100),
                          YELLOW,
                          [&background_color]() {background_color = BLUE;})};

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(background_color);
        for (auto& box: boxes) {
            auto delta {GetMouseDelta()};
            std::println("[DEBUG] delta {}, {}", delta.x, delta.y);
            if (delta.x == 0.0f && delta.y == 0.0f) {
                DrawRectangleRec(box.m_rectangle, BLACK);
            } else {
                DrawRectangleRec(box.m_rectangle, box.IsHovered() ? box.m_hover_color : BLACK);
                box(GetMousePosition(), MOUSE_BUTTON_LEFT);
            }
        }

        EndDrawing();
    }

    CloseWindow();
}
