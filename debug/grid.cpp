// 怖くなってきたな。
// まぁ。。。
// 本当なら、違ってほしかったよ。
// 俺はこれから、いったい何人の人間に嫌わていくんだろうな。。。
// はははは。。。
// ま、仕方ないね。
// 自業自得だ。
// だが、諦めぬ。

#include <raylib.h>
#include <print>
#include <vector>
#include <map>
#include <utility>
#include "utils.hpp"

Color GetRandomColor(void) {
    return {(unsigned char)GetRandomValue(0, 0xff), 
            (unsigned char)GetRandomValue(0, 0xff),
            (unsigned char)GetRandomValue(0, 0xff),
            (unsigned char)GetRandomValue(0, 0xff)};
}

inline int InitGame(int width, int height) {
//    SetTraceLogLevel(LOG_FATAL);
    InitWindow(width, height, "こんなこともできちゃう");
    InitAudioDevice();
    SetConfigFlags(FLAG_WINDOW_TRANSPARENT | FLAG_VSYNC_HINT);
    SetWindowState(FLAG_WINDOW_UNDECORATED | 
                   FLAG_WINDOW_RESIZABLE);
    SetTargetFPS(120);
    return 0;
}

inline bool InTextureV(Vector2 position, PositionedTexture2D positioned_texture) {
    Rectangle rectangle {positioned_texture.position.x, 
                         positioned_texture.position.y, 
                         positioned_texture.texture.width, 
                         positioned_texture.texture.height};
    return CheckCollisionPointRec(position, rectangle);
}

struct ColoredRectangle {
    Rectangle rectangle {};
    Color color {};
};

std::vector<ColoredRectangle> 
GenerateSquareGrid(int rows = 10, int columns = 10, int padding = 10, int square_length = 100, 
                   Vector2 position = {10, 50}) {
    std::vector<ColoredRectangle> grid {};
    grid.reserve(rows * columns);

    Vector2 initial_position {position};
    Vector2 current_position {initial_position};

    for (auto i {0}; i < rows; ++i) {
        for (auto j {0}; j < columns; ++j) {
            grid.push_back({Rectangle(current_position.x,
                                      current_position.y,
                                      square_length,
                                      square_length),
                                      GetRandomColor()});
            current_position.x += square_length + padding;
        }
        current_position.y += square_length + padding;
        current_position.x = initial_position.x;
    }

    return grid;
}

inline int ImageLoop(int width, int height) {
    using std::vector;
    auto image_width {50};
    auto image_height {50};

    vector<std::string> image_paths {
                        "../assets/neon_add_button.png",
                        "../assets/neon_remove_button.png",
                        "../assets/neon_view_button.png",
    };
    vector<Vector2> positions {
                        Vector2(width - image_width - 10, height - 3 * image_height - 30),
                        Vector2(width - image_width - 10, height - 2 * image_height - 20),
                        Vector2(width - image_width - 10, height - image_height - 10)
    };

    auto textures {Assets::LoadPositionedImages(image_paths, positions)};

    auto grid {GenerateSquareGrid()};
    int click_count {0};

    Camera2D camera {.offset = {0, 0}, .target = {0, 0}, .rotation = 0.0f, .zoom = 1.0f};

    while (!WindowShouldClose()) {
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            if (InTextureV(GetMousePosition(), textures[0])) {
                if (click_count < grid.size()) {
                    std::println("[DEBUG] Adding.");
                    ++click_count;
                }
            } else if (InTextureV(GetMousePosition(), textures[1])) {
                if (click_count > 0) {
                    std::println("[DEBUG] Removing.");
                    --click_count;
                }
            }
        }

        if (IsKeyDown(KEY_W)) {
            camera.target.y -= 5;
        } else if (IsKeyDown(KEY_A)) {
            camera.target.x -= 5;
        } else if (IsKeyDown(KEY_S)) {
            camera.target.y += 5;
        } else if (IsKeyDown(KEY_D)) {
            camera.target.x += 5;
        } else if (IsKeyPressed(KEY_MINUS)) {
            camera.zoom -= 0.1f;
        } else if (IsKeyPressed(KEY_EQUAL)) {
            camera.zoom += 0.1f;
        }

        camera.zoom += GetMouseWheelMove();

        BeginDrawing();

        ClearBackground(DARKBLUE);

        BeginMode2D(camera);
        DrawText("Move with the W, A, S and D keys, as usual.", 10, 10, 30, BLUE);
        for (auto i {0}; i < click_count; ++i) {
            DrawRectangleRec(grid[i].rectangle, grid[i].color);
        }
        EndMode2D();

        for (auto i {0}; i < textures.size(); ++i) {
            auto in_texture {InTextureV(GetMousePosition(), textures[i])};
            auto text {TextFormat("In Image %i: %s", i, in_texture ? "Yes" : "No")};
            if (in_texture) {
                DrawTextureV(textures[i].texture, textures[i].position, PURPLE);
            } else {
                DrawTextureV(textures[i].texture, textures[i].position, WHITE);
            }
        }

        EndDrawing();
    }

    for (auto i {0}; i < textures.size(); ++i) {
        UnloadTexture(textures[i].texture);
        std::println("[INFO] Unloading texture.");
    }

    CloseAudioDevice();
    CloseWindow();

    return 0;
}

int main(void) {
    InitGame(1280, 720);
    ImageLoop(1280, 720);
    return 0;
}
