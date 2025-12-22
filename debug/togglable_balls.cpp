#include <raylib.h>
#include <print>
#include <vector>

struct Circle {
    Vector2 position {};
    Color color {};
    int radius {};
};

Color GetRandomColor(void) {
    return {(float)GetRandomValue(0, 0xff), 
            (float)GetRandomValue(0, 0xff),
            (float)GetRandomValue(0, 0xff),
            (float)GetRandomValue(0, 0xff)};
}

inline int InitGame(void) {
//    SetTraceLogLevel(LOG_FATAL);
    auto width {600};
    auto height {800};
    InitWindow(width, height, "こんなこともできちゃう");
    InitAudioDevice();
    SetConfigFlags(FLAG_WINDOW_TRANSPARENT);
    SetWindowState(FLAG_WINDOW_UNDECORATED | 
                   FLAG_WINDOW_RESIZABLE);
    SetTargetFPS(120);
    return 0;
}

inline int GameLoop(void) {
    auto width {600};
    auto height {800};
    auto radius {100.0f};

    while (!WindowShouldClose()) {
        BeginDrawing();

        ClearBackground(RAYWHITE);
        DrawFPS(0, 0);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}

inline int ButtonLoop(void) {
    auto width {600};
    auto height {800};
    auto color {GetRandomColor()};
    const auto default_font {GetFontDefault()};
    auto rec_x {(width - 300) / 2.0f};
    auto rec_y {(height - 100) / 2.0f};
    auto rec_width {300};
    auto rec_height {100};
    auto in_rectangle {false};
    auto in_rectangle_counter {0};
    auto jumpscare_sound {LoadSound("../assets/amaterasu.mp3")};
    
    while (!WindowShouldClose()) {
        if (IsKeyPressed(KEY_P)) {
            if (IsSoundPlaying(jumpscare_sound)) {
                PauseSound(jumpscare_sound);
            }
        }

        auto mouse_position {GetMousePosition()};
        auto mouse_position_text 
                            {TextFormat("Mouse: %.0f, %.0f", mouse_position.x, mouse_position.y)};
        in_rectangle = rec_x <= mouse_position.x && 
                       mouse_position.x <= rec_x + rec_width && 
                       rec_y <= mouse_position.y &&
                       mouse_position.y <= rec_y + rec_height;

        auto in_rectangle_text {TextFormat("In Rectangle: %s", in_rectangle ? "Yes" : "No")};
        auto mouse_position_text_measurements 
                               {MeasureTextEx(default_font, mouse_position_text, 20.0f, 1.0f)};
        auto in_rectangle_text_measurements
                               {MeasureTextEx(default_font, in_rectangle_text, 20.0f, 1.0f)};

        BeginDrawing();

        ClearBackground(RAYWHITE);
        DrawFPS(0, 0);
        DrawText(mouse_position_text, 0, 10 + mouse_position_text_measurements.y, 30, color);
        DrawText(in_rectangle_text, 0, 40 + in_rectangle_text_measurements.y, 30, color);

        if (in_rectangle) {
            color = RED;
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) ++in_rectangle_counter;
        } else {
            color = GetRandomColor();
        } 
         
        DrawRectangle(rec_x, rec_y, 300, 100, color);

        if (in_rectangle_counter == 10) {
            in_rectangle_counter = 0;
            ClearBackground(BLACK);
            PlaySound(jumpscare_sound);
        }

        EndDrawing();
    }

    CloseWindow();
    return 0;
}

int main(void) {
    InitGame();
    ButtonLoop();
    return 0;
}
