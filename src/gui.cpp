// Well, let's keep working on this.
#include <raylib.h>
#include <vector>
#include <print>

Color GetRandomColor(void) {
    return {(unsigned char)GetRandomValue(0, 0xff), 
            (unsigned char)GetRandomValue(0, 0xff),
            (unsigned char)GetRandomValue(0, 0xff),
            (unsigned char)GetRandomValue(0, 0xff)};
}

Color GetRandomSolidColor(void) {
    return {(unsigned char)GetRandomValue(1, 0xff), 
            (unsigned char)GetRandomValue(1, 0xff),
            (unsigned char)GetRandomValue(1, 0xff),
            (unsigned char)0xff};
}


namespace Asset {
    #define ASSET_PATH "../assets/"
    Texture2D CITY_FIELD;
    Texture2D ADD_BUTTON;
    Texture2D REMOVE_BUTTON;
    Texture2D VIEW_BUTTON;
    Texture2D EMPTY_TEXTURE;
    int EMPTY_TEXTURE_ID;
    float BOX_PADDING;
    float BOX_WIDTH;
    float BUTTON_WIDTH;
    float BUTTON_HEIGHT;
    float BUTTON_COUNT;
    float BOX_HEIGHT;
    float CITY_FIELD_WIDTH;
    float CITY_FIELD_HEIGHT;
    int COLUMN_COUNT = 10;
    int ROW_COUNT = 10;

    int LoadAssets(void) {
        Asset::ADD_BUTTON = LoadTexture(ASSET_PATH"button_assets/neon_add_button.png");
        Asset::REMOVE_BUTTON = LoadTexture(ASSET_PATH"button_assets/neon_remove_button.png");
        Asset::VIEW_BUTTON = LoadTexture(ASSET_PATH"button_assets/neon_view_button.png");
        Asset::CITY_FIELD = LoadTexture(ASSET_PATH"city_assets/city_texture.png");
        Asset::EMPTY_TEXTURE = Texture2D();
        Asset::EMPTY_TEXTURE_ID = 0;
        Asset::BOX_PADDING = 3.0f;
        Asset::BOX_WIDTH = 294.0f;
        Asset::BUTTON_WIDTH = 50.0f;
        Asset::BUTTON_HEIGHT = 50.0f;
        Asset::BUTTON_COUNT = 3.0f;
        Asset::BOX_HEIGHT = 294.0f;
        Asset::CITY_FIELD_WIDTH = Asset::CITY_FIELD.width;
        Asset::CITY_FIELD_HEIGHT = Asset::CITY_FIELD.height;
        return 0;
    }
};

class Game {
    public:
        constexpr static auto GAME_TITLE {"vcs - a minimal city simulator"};
        constexpr static auto DEFAULT_FPS {120};
        constexpr static Color DEFAULT_COLOR {17, 63, 42, 255};
        std::vector<std::tuple<Rectangle, Texture2D&>> m_building_boxes {};
        std::vector<std::tuple<Rectangle, Texture2D&>> m_buttons {};
        std::vector<std::tuple<Rectangle, Texture2D&>> m_map {};
        Vector2 m_lower_bound {};
        Vector2 m_upper_bound {};
        Camera2D m_camera {};
        float m_camera_move_speed {};
        float m_width {};
        float m_height {};

        Game(float width, float height) {
            m_width = width; 
            m_height = height;
            m_camera_move_speed = 5.0f;
            m_camera = {Vector2(0, 0), Vector2(0, 0), 0.0f, 1.0f};
            m_lower_bound = Vector2(0.0f, 0.0f);
        }

        Game(int width, int height): Game((float)width, (float)height) {}

        Game(void): Game(GetScreenWidth(), GetScreenHeight()) {}

        inline void PositionAssets(void) {
            m_upper_bound = {Asset::CITY_FIELD.width - m_width, 
                             Asset::CITY_FIELD.height - m_height};
            m_building_boxes.reserve(Asset::ROW_COUNT * Asset::COLUMN_COUNT);
            m_buttons.reserve(Asset::BUTTON_COUNT);
            m_map.emplace_back(Rectangle(0, 0, Asset::CITY_FIELD_WIDTH, Asset::CITY_FIELD_HEIGHT),
                               Asset::CITY_FIELD);
            for (auto row{0}; row < Asset::ROW_COUNT; ++row) {
                for (auto column{0}; column < Asset::COLUMN_COUNT; ++column) {
                    Rectangle box {.x = Asset::BOX_PADDING + column * 
                                        (Asset::BOX_WIDTH + Asset::BOX_PADDING),
                                   .y = Asset::BOX_PADDING + row * 
                                        (Asset::BOX_HEIGHT + Asset::BOX_PADDING),
                                   .width = Asset::BOX_WIDTH,
                                   .height = Asset::BOX_HEIGHT};
                    m_building_boxes.emplace_back(box, Asset::EMPTY_TEXTURE);
                }
            }
            m_buttons.emplace_back(Rectangle(m_width - Asset::BUTTON_WIDTH - 10,
                                             m_height - 3 * Asset::BUTTON_HEIGHT - 30, 
                                             Asset::BUTTON_WIDTH,
                                             Asset::BUTTON_HEIGHT),
                                   Asset::ADD_BUTTON);
            m_buttons.emplace_back(Rectangle(m_width - Asset::BUTTON_WIDTH - 10,
                                             m_height - 2 * Asset::BUTTON_HEIGHT - 20, 
                                             Asset::BUTTON_WIDTH,
                                             Asset::BUTTON_HEIGHT),
                                   Asset::REMOVE_BUTTON);
            m_buttons.emplace_back(Rectangle(m_width - Asset::BUTTON_WIDTH - 10,
                                             m_height - Asset::BUTTON_HEIGHT - 10, 
                                             Asset::BUTTON_WIDTH,
                                             Asset::BUTTON_HEIGHT),
                                   Asset::VIEW_BUTTON);
        }

        inline int InitGame(void) {
            InitWindow(m_width, m_height, Game::GAME_TITLE);
            SetExitKey(KEY_NULL);
            SetConfigFlags(FLAG_VSYNC_HINT);
            //SetWindowState(FLAG_FULLSCREEN_MODE);
            SetTargetFPS(Game::DEFAULT_FPS);
            Asset::LoadAssets();
            PositionAssets();
            return 0;
        }

        inline void HandleInput(void) {
            if (IsKeyPressed(KEY_F11)) {
                ToggleFullscreen();
                return;
            }

            if (IsKeyDown(KEY_LEFT_SHIFT) && IsKeyDown(KEY_W)) {
                m_camera.target.y -= (m_camera_move_speed * 2);
                return;
            } 
            if (IsKeyDown(KEY_W)) {
                m_camera.target.y -= m_camera_move_speed;
                return;
            } 

            if (IsKeyDown(KEY_LEFT_SHIFT) && IsKeyDown(KEY_A)) {
                m_camera.target.x -= (m_camera_move_speed * 2);
                return;
            } 
            if (IsKeyDown(KEY_A)) {
                m_camera.target.x -= m_camera_move_speed;
                return;
            } 

            if (IsKeyDown(KEY_LEFT_SHIFT) && IsKeyDown(KEY_S)) {
                m_camera.target.y += (m_camera_move_speed * 2);
                return;
            } 
            if (IsKeyDown(KEY_S)) {
                m_camera.target.y += m_camera_move_speed;
                return;
            }

            if (IsKeyDown(KEY_LEFT_SHIFT) && IsKeyDown(KEY_D)) {
                m_camera.target.x += (m_camera_move_speed * 2);
                return;
            } 
            if (IsKeyDown(KEY_D)) {
                m_camera.target.x += m_camera_move_speed;
                return;
            }

            if (IsKeyDown(KEY_LEFT_CONTROL) && IsKeyPressed(KEY_B)) {
                std::println("[DEBUG] Added.");
                auto last_texture {std::get<Rectangle>(m_map.back())};
                Vector2 previous_position {last_texture.x, last_texture.y};
                m_map.emplace_back(Rectangle(previous_position.x + Asset::CITY_FIELD_WIDTH, 
                                             previous_position.y,
                                             Asset::CITY_FIELD_WIDTH,
                                             Asset::CITY_FIELD_HEIGHT),
                                   Asset::CITY_FIELD);
                Vector2 m_old_upper_bound = {m_upper_bound.x, m_upper_bound.y};
                m_upper_bound = {m_old_upper_bound.x + Asset::CITY_FIELD_WIDTH, 
                                 m_old_upper_bound.y};
                return;
            }

            if (IsKeyPressed(KEY_K)) {
                ++m_camera_move_speed;
                return;
            } else if (IsKeyPressed(KEY_J)) {
                m_camera_move_speed = m_camera_move_speed > 0 ? --m_camera_move_speed 
                                      : m_camera_move_speed;
                return;
            }

            if (m_camera.zoom > 0) {
                auto old_camera_zoom = m_camera.zoom;
                if (IsKeyPressed(KEY_MINUS)) {
                    m_camera.zoom = m_camera.zoom > 0 ? m_camera.zoom - 0.1f : m_camera.zoom;
                } else if (IsKeyPressed(KEY_EQUAL)) {
                    m_camera.zoom += 0.1f;
                }

                m_camera.zoom += (GetMouseWheelMove() * 0.1f);

                if (m_camera.zoom < 0) {
                    m_camera.zoom = old_camera_zoom;
                }
                return;
            } else {
                return;
            } 
        }

        inline void RegulateCamera(Vector2 lower_bound, Vector2 upper_bound) {
            if (m_camera.target.x >= upper_bound.x) {
                m_camera.target.x = upper_bound.x;
            }

            if (m_camera.target.y >= upper_bound.y) {
                m_camera.target.y = upper_bound.y;
            }

            if (m_camera.target.x <= lower_bound.x) {
                m_camera.target.x = lower_bound.x;
            }

            if (m_camera.target.y <= lower_bound.y) {
                m_camera.target.y = lower_bound.y;
            }
        }

        inline void DrawCall(void) {
            RegulateCamera(m_lower_bound, m_upper_bound);
            BeginDrawing();

            DrawFPS(0, 0);

            BeginMode2D(m_camera);
            ClearBackground(DEFAULT_COLOR);
            for (const auto& [rectangle, texture]: m_map) {
                DrawTexture(texture, rectangle.x, rectangle.y, Color(255, 255, 255, 200));
            }
            for (const auto& [rectangle, texture]: m_building_boxes) {
                auto relative_mouse_position {GetScreenToWorld2D(GetMousePosition(), m_camera)};
                if (texture.id == Asset::EMPTY_TEXTURE_ID) {
                    DrawRectangleRec(rectangle, 
                                     CheckCollisionPointRec(relative_mouse_position, rectangle) ?
                                     Fade(WHITE, 0.25f) : BLANK);
                } else {
                    DrawTexture(texture, rectangle.x, rectangle.y, WHITE);
                }
            }
            EndMode2D();

            for (const auto& [rectangle, texture]: m_buttons) {
                DrawTexture(texture, rectangle.x, rectangle.y, WHITE);
            }

            EndDrawing();
        }

        inline void GameLoop(void) {
            while (!WindowShouldClose()) {
                HandleInput();
                DrawCall();
            }
            CloseWindow();
        }

        inline int StartGame(void) {
            InitGame();
            GameLoop();
            return 0;
        }
};

int main(void) {
    Game(1280, 720).StartGame();
    return 0;
}
