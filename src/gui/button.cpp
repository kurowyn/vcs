// As it stands, this code uses an insane amount of GPU.
// This is probably because Box.IsHovered() and Box.IsClicked() are being called
// at every single draw call. Any suggestions are welcome.
#include <raylib.h>
#include <functional>
#include <print>
#include <array>

// This entire thing is horrible. Do not use it in production.
// This is only for a small college project.
struct Box {
    Texture2D& m_texture;
    Rectangle m_rectangle {};
    Color m_hover_color {};
    std::function<void(void)> m_call_back {};

    inline bool IsClicked(Vector2 mouse_position, MouseButton mouse_button) {
        return this->IsHovered(mouse_position) && IsMouseButtonPressed(mouse_button);
    }

    inline bool IsHovered(Vector2 mouse_position) {
        return CheckCollisionPointRec(mouse_position, m_rectangle);
    }

    inline void Draw(Vector2 mouse_position) {
        Color tint {IsHovered(mouse_position) ?  m_hover_color : BLANK};
        switch (m_texture.id) {
            case 0:
                DrawRectangleRec(m_rectangle, tint);
                break;
            default:
                DrawTextureV(m_texture, Vector2(m_rectangle.x, m_rectangle.y), tint);
                break;
        }
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

    SetTargetFPS(120);
    while (!WindowShouldClose()) {
        auto mouse_position {GetMousePosition()};
        BeginDrawing();
        ClearBackground(background_color);
        for (auto& box: boxes) {
            box.Draw(mouse_position);
            if (box.IsClicked(mouse_position, MOUSE_LEFT_BUTTON)) {
                box.m_call_back();
            } else if (box.IsClicked(mouse_position, MOUSE_RIGHT_BUTTON)) {
                std::println("[INFO] You right clicked!");
            }
        }

        EndDrawing();
    }

    CloseWindow();
}
