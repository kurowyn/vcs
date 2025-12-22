#include <raylib.h>
#include <vector>
#include <print>

namespace Default {
    const auto GAME_TITLE {"vcs - a minimal city simulator"};
    const auto DEFAULT_FPS {120};
    const Color DEFAULT_COLOR {17, 63, 42, 255};
};


Color GetRandomColor(void) {
    return {(unsigned char)GetRandomValue(0, 0xff), 
            (unsigned char)GetRandomValue(0, 0xff),
            (unsigned char)GetRandomValue(0, 0xff),
            (unsigned char)GetRandomValue(0, 0xff)};
}

inline void RegulateCamera(Camera2D* camera, Vector2 lower_bound, Vector2 upper_bound) {
    if (camera->target.x >= upper_bound.x) {
        camera->target.x = upper_bound.x;
    }

    if (camera->target.y >= upper_bound.y) {
        camera->target.y = upper_bound.y;
    }

    if (camera->target.x <= lower_bound.x) {
        camera->target.x = lower_bound.x;
    }

    if (camera->target.y <= lower_bound.y) {
        camera->target.y = lower_bound.y;
    }
}

inline void MoveCamera(Camera2D* camera, float move_speed) {
    if (IsKeyDown(KEY_W)) {
        camera->target.y -= move_speed;
    } else if (IsKeyDown(KEY_A)) {
        camera->target.x -= move_speed;
    } else if (IsKeyDown(KEY_S)) {
        camera->target.y += move_speed;
    } else if (IsKeyDown(KEY_D)) {
        camera->target.x += move_speed;
    }
}

inline void InitGame(int width, int height) {
    InitWindow(width, height, Default::GAME_TITLE);
    SetConfigFlags(FLAG_VSYNC_HINT);
    //SetWindowState(FLAG_WINDOW_UNDECORATED | FLAG_WINDOW_RESIZABLE);
    SetWindowState(FLAG_WINDOW_RESIZABLE);
    SetTargetFPS(Default::DEFAULT_FPS);
}

inline void GameLoop(int width, int height) {
    auto city_field {LoadTexture("../assets/city_texture.png")};
    auto add_button {LoadTexture("../assets/neon_add_button.png")};
    auto remove_button {LoadTexture("../assets/neon_remove_button.png")};
    auto view_button {LoadTexture("../assets/neon_view_button.png")};
    auto button_width {add_button.width};
    auto button_height {add_button.height};

    std::vector<Rectangle> building_boxes {};
    // So, there's gonna be a bunch of rectangles lined up next to each other...

    std::vector<std::tuple<Vector2, Texture2D>> map {{Vector2(0, 0),
                                                      LoadTexture("../assets/city_texture.png")}};

    auto move_speed {5.0f};
    Camera2D camera {Vector2(0, 0), Vector2(0, 0), 0.0f, 1.0f};
    while (!WindowShouldClose()) {
        if (IsKeyDown(KEY_LEFT_CONTROL) && IsKeyPressed(KEY_A)) {
            Vector2 previous_position {std::get<Vector2>(map.back())};
            Texture2D previous_texture {std::get<Texture2D>(map.back())};
            Vector2 new_position {previous_position.x + previous_texture.width,
                                   previous_position.y};
            map.push_back({new_position, LoadTexture("../assets/city_texture.png")});
        }

        if (IsKeyPressed(KEY_K)) {
            ++move_speed;
        } else if (IsKeyPressed(KEY_J)) {
            move_speed = move_speed > 0 ? --move_speed : move_speed;
        }

        if (IsKeyPressed(KEY_MINUS)) {
            camera.zoom -= 0.1f;
        } else if (IsKeyPressed(KEY_EQUAL)) {
            camera.zoom += 0.1f;
        }
        if (camera.zoom < 0) {
            camera.zoom = 0.0f;
        }

        MoveCamera(&camera, move_speed);
//        RegulateCamera(&camera, Vector2(0, 0), 
//                Vector2(city_field.width - 1280, city_field.height - 720));

        BeginDrawing();
        ClearBackground(Default::DEFAULT_COLOR);
        DrawFPS(0, 0);

        BeginMode2D(camera);
        for (const auto& [position, texture]: map) {
            DrawTextureV(texture, position, WHITE);
        }

        EndMode2D();

        DrawTexture(add_button, 
                    width - button_width - 10,
                    height - 3 * button_height - 30, 
                    WHITE);
        DrawTexture(remove_button, 
                    width - button_width - 10,
                    height - 2 * button_height - 20, 
                    WHITE);
        DrawTexture(view_button, 
                    width - button_width - 10,
                    height - button_height - 10, 
                    WHITE);
        EndDrawing();
    }
    CloseWindow();
}

int main(void) {
    auto width {1280};
    auto height {720};
    InitGame(width, height);
    GameLoop(width, height);
    return 0;
}
