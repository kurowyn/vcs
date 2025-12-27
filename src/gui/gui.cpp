#include "gui.hpp"

namespace Asset {
    Texture2D CITY_FIELD;
    Texture2D ADD_BUTTON;
    Texture2D REMOVE_BUTTON;
    Texture2D VIEW_BUTTON;
    Texture2D PLUS_SIGN;
    Texture2D HOUSE;
    Texture2D PARK;
    Texture2D FACTORY;
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
    int COLUMN_COUNT;
    int ROW_COUNT;

    int LoadAssets(void) {
        Asset::CITY_FIELD = LoadTexture(ASSET_PATH"city_assets/city_texture.png");
        Asset::ADD_BUTTON = LoadTexture(ASSET_PATH"button_assets/neon_add_button.png");
        Asset::REMOVE_BUTTON = LoadTexture(ASSET_PATH"button_assets/neon_remove_button.png");
        Asset::VIEW_BUTTON = LoadTexture(ASSET_PATH"button_assets/neon_view_button.png");
        Asset::PLUS_SIGN = LoadTexture(ASSET_PATH"city_assets/add_sign.png");
        Asset::HOUSE = LoadTexture(ASSET_PATH"house_assets/house_1.png");
        Asset::PARK = LoadTexture(ASSET_PATH"park_assets/park_1.png");
        Asset::FACTORY = LoadTexture(ASSET_PATH"factory_assets/factory_1.png");
        Asset::EMPTY_TEXTURE = Texture2D();
        Asset::EMPTY_TEXTURE_ID = 0;
        Asset::BOX_PADDING = 3.0f;
        Asset::BOX_WIDTH = 294.0f;
        Asset::BUTTON_WIDTH = 50.0f;
        Asset::BUTTON_HEIGHT = 50.0f;
        Asset::BUTTON_COUNT = 3.0f;
        Asset::BOX_HEIGHT = 294.0f;
        Asset::COLUMN_COUNT = 10;
        Asset::ROW_COUNT = 10;
        Asset::CITY_FIELD_WIDTH = Asset::CITY_FIELD.width;
        Asset::CITY_FIELD_HEIGHT = Asset::CITY_FIELD.height;
        return 0;
    }
};

std::string Game::GAME_TITLE {"vcs - a minimal city simulator"};
int Game::DEFAULT_FPS {120};
Color Game::DEFAULT_COLOR {17, 63, 42, 255};

const char* Game::ResolveMode(Mode mode) {
    switch (mode) {
        case Mode::ADD:
            return "Add";
        case Mode::REMOVE:
            return "Remove";
        case Mode::VIEW:
            return "View";
        default:
            return "Unknown";
    }
}

Game::Game(float width, float height) {
    m_width = width; 
    m_height = height;
    m_camera_move_speed = 5.0f;
    m_camera = {Vector2(0, 0), Vector2(0, 0), 0.0f, 1.0f};
    m_lower_bound = Vector2(0.0f, 0.0f);
    m_mode = Mode::VIEW;
}

Game::Game(int width, int height): Game((float)width, (float)height) {}

Game::Game(void): Game(GetScreenWidth(), GetScreenHeight()) {}

void Game::AddBuilding(void) {
    std::println("[DEBUG] AddBuilding(): Not Yet Implemented.");
}

void Game::RemoveBuilding(void) {
    std::println("[DEBUG] RemoveBuilding(): Not Yet Implemented.");
}

void Game::ViewBuilding(void) {
    std::println("[DEBUG] ViewBuilding(): Not Yet Implemented.");
}

int Game::InitGame(void) {
    InitWindow(m_width, m_height, Game::GAME_TITLE.c_str());
    SetExitKey(KEY_NULL);
    SetConfigFlags(FLAG_VSYNC_HINT);
//    SetWindowState(FLAG_FULLSCREEN_MODE);
    SetTargetFPS(Game::DEFAULT_FPS);
    PositionAssets();
    return 0;
}

void Game::PositionAssets(void) {
    Asset::LoadAssets();

    m_upper_bound = {Asset::CITY_FIELD.width - m_width, 
                     Asset::CITY_FIELD.height - m_height};
    m_building_boxes.reserve(Asset::ROW_COUNT * Asset::COLUMN_COUNT);
    m_buttons.reserve(Asset::BUTTON_COUNT);
    m_map.reserve(3);
    m_map.emplace_back(Box{.m_texture = Asset::CITY_FIELD, 
                           .m_rectangle = Rectangle{.x = 0,
                                                    .y = 0, 
                                                    .width = Asset::CITY_FIELD_WIDTH,
                                                    .height = Asset::CITY_FIELD_HEIGHT},
                           .m_is_hoverable = false,
                           .m_hovered_color = BLANK,
                           .m_unhovered_color = WHITE});

    for (auto row{0}; row < Asset::ROW_COUNT; ++row) {
        for (auto column{0}; column < Asset::COLUMN_COUNT; ++column) {
            Rectangle rectangle {.x = Asset::BOX_PADDING + column * 
                                 (Asset::BOX_WIDTH + Asset::BOX_PADDING),
                                 .y = Asset::BOX_PADDING + row * 
                                 (Asset::BOX_HEIGHT + Asset::BOX_PADDING),
                                 .width = Asset::BOX_WIDTH,
                                 .height = Asset::BOX_HEIGHT};
 
            m_building_boxes.emplace_back(Building::CreateEmptyBuilding(),
                                          Box{.m_texture = Asset::EMPTY_TEXTURE,
                                              .m_rectangle = rectangle,
                                              .m_is_hoverable = true,
                                              .m_hovered_color = Fade(WHITE, 0.25f),
                                              .m_unhovered_color = BLANK});
        }
    }

    m_buttons.emplace_back(Box{.m_texture = Asset::ADD_BUTTON,
                               .m_rectangle = Rectangle(m_width - Asset::BUTTON_WIDTH - 10,
                                                        m_height - 3 * Asset::BUTTON_HEIGHT - 30, 
                                                        Asset::BUTTON_WIDTH,
                                                        Asset::BUTTON_HEIGHT),
                                .m_is_hoverable = true,
                                .m_hovered_color = SKYBLUE,
                                .m_unhovered_color = WHITE});
    m_buttons.emplace_back(Box{.m_texture = Asset::REMOVE_BUTTON,
                               .m_rectangle = Rectangle(m_width - Asset::BUTTON_WIDTH - 10,
                                                        m_height - 2 * Asset::BUTTON_HEIGHT - 20, 
                                                        Asset::BUTTON_WIDTH,
                                                        Asset::BUTTON_HEIGHT),
                                .m_is_hoverable = true,
                                .m_hovered_color = SKYBLUE,
                                .m_unhovered_color = WHITE});
    m_buttons.emplace_back(Box{.m_texture = Asset::VIEW_BUTTON,
                               .m_rectangle = Rectangle(m_width - Asset::BUTTON_WIDTH - 10,
                                                        m_height - Asset::BUTTON_HEIGHT - 10, 
                                                        Asset::BUTTON_WIDTH,
                                                        Asset::BUTTON_HEIGHT),
                                .m_is_hoverable = true,
                                .m_hovered_color = SKYBLUE,
                                .m_unhovered_color = WHITE});
}

void Game::RegulateCamera(Vector2 lower_bound, Vector2 upper_bound) {
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

void Game::HandleInput(void) {
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

void Game::DrawCall(void) {
    Rectangle button_area {m_buttons[0].m_rectangle.x, m_buttons[0].m_rectangle.y, 60, 180};
    auto real_mouse_position {GetMousePosition()};
    auto relative_mouse_position {GetScreenToWorld2D(real_mouse_position, m_camera)};

    if (m_buttons[0].IsClicked(real_mouse_position, MOUSE_BUTTON_LEFT)) {
        m_mode = Mode::ADD;
        for (auto& [building, box]: m_building_boxes) {
            // no building
            if (building.m_id == 0) {
                box.m_texture = Asset::PLUS_SIGN;
                box.m_hovered_color = WHITE;
                box.m_unhovered_color = Fade(WHITE, 0.25f);
            // there is a building
            } else {
                box.m_hovered_color = SKYBLUE;
                box.m_unhovered_color = WHITE;
            }
        }
    } else if (m_buttons[1].IsClicked(real_mouse_position, MOUSE_BUTTON_LEFT)) {
        m_mode = Mode::REMOVE;
        for (auto& [building, box]: m_building_boxes) {
            if (building.m_id == 0) {
                box.m_texture = Texture2D();
                box.m_hovered_color = BLANK;
                box.m_unhovered_color = BLANK;
            } else {
                box.m_hovered_color = RED;
                box.m_unhovered_color = WHITE;
            }
        }
    } else if (m_buttons[2].IsClicked(real_mouse_position, MOUSE_BUTTON_LEFT)) {
        m_mode = Mode::VIEW;
        for (auto& [building, box]: m_building_boxes) {
            if (building.m_id == 0) {
                box.m_texture = Texture2D();
                box.m_hovered_color = BLANK;
                box.m_unhovered_color = BLANK;
            } else {
                box.m_hovered_color = LIGHTGRAY;
                box.m_unhovered_color = WHITE;
            }
        }
    }

    for (auto& [building, box]: m_building_boxes) {
        if (!CheckCollisionPointRec(real_mouse_position, button_area) &&
            box.IsHeld(relative_mouse_position, MOUSE_BUTTON_LEFT)) {
            switch (m_mode) {
                case Mode::ADD:
                    box.m_texture = Asset::HOUSE;
                    box.m_hovered_color = SKYBLUE;
                    box.m_unhovered_color = WHITE;
                    building.m_id = ::g_building_id++;
                    break;
                case Mode::REMOVE:
                    box.m_texture = Texture2D();
                    box.m_hovered_color = BLANK;
                    box.m_unhovered_color = BLANK;
                    building.m_id = 0;
                    break;
                case Mode::VIEW:
                    break;
            }
        }
    }

    RegulateCamera(m_lower_bound, m_upper_bound);
    BeginDrawing();
    ClearBackground(DEFAULT_COLOR);
    DrawFPS(0, 0);

    BeginMode2D(m_camera);
    for (auto& box: m_map) {
        box.Draw();
    }
    for (auto& [building, box]: m_building_boxes) {
        box.Draw(relative_mouse_position);
    }
    EndMode2D();

    for (auto& box: m_buttons) {
        box.Draw(real_mouse_position);
    }
    DrawText(TextFormat("Mode: %s", ResolveMode(m_mode)),
             10,
             10,
             30,
             PURPLE);

    EndDrawing();
}

void Game::GameLoop(void) {
    while (!WindowShouldClose()) {
        HandleInput();
        DrawCall();
    }
    CloseWindow();
}

int Game::StartGame(void) {
    InitGame();
    GameLoop();
    return 0;
}
