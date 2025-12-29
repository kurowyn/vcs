#include "gui.hpp"

namespace Asset {
    Texture2D CITY_FIELD;
    Texture2D ADD_BUTTON;
    Texture2D REMOVE_BUTTON;
    Texture2D VIEW_BUTTON;
    Texture2D PLUS_SIGN;
    Texture2D HOUSE;
    Texture2D RESIZED_HOUSE;
    Texture2D PARK;
    Texture2D RESIZED_PARK;
    Texture2D FACTORY;
    Texture2D RESIZED_FACTORY;

    std::map<const char*, Texture2D> BUILDING_TEXTURES;
    std::array<Texture2D, 6> BUTTON_TEXTURES;
    std::array<const char*, 6> BUTTON_NAMES;

    float BUILDING_SQUARE_PADDING;
    float BUILDING_SQUARE_WIDTH;
    float BUILDING_SQUARE_HEIGHT;
    float BUTTON_PADDING;

    float CITY_FIELD_WIDTH;
    float CITY_FIELD_HEIGHT;
    int COLUMN_COUNT;
    int ROW_COUNT;

    int LoadAssets(void) {
        Image RESIZED_HOUSE_IMAGE {LoadImage("../assets/house_assets/house_1.png")};
        Image RESIZED_PARK_IMAGE {LoadImage("../assets/park_assets/park_1.png")};
        Image RESIZED_FACTORY_IMAGE {LoadImage("../assets/factory_assets/factory_1.png")};

        ImageAlphaCrop(&RESIZED_HOUSE_IMAGE, 0.0f);
        ImageAlphaCrop(&RESIZED_PARK_IMAGE, 0.0f);
        ImageAlphaCrop(&RESIZED_FACTORY_IMAGE, 0.0f);

        ImageResizeNN(&RESIZED_HOUSE_IMAGE, 
                      50, 
                      RESIZED_HOUSE_IMAGE.height * 50 / RESIZED_HOUSE_IMAGE.width);
        ImageResizeNN(&RESIZED_PARK_IMAGE, 
                      50, 
                      RESIZED_PARK_IMAGE.height * 50 / RESIZED_PARK_IMAGE.width);
        ImageResizeNN(&RESIZED_FACTORY_IMAGE, 
                      50, 
                      RESIZED_FACTORY_IMAGE.height * 50 / RESIZED_FACTORY_IMAGE.width);

        Asset::CITY_FIELD = LoadTexture("../assets/city_assets/city_texture.png");
        Asset::ADD_BUTTON = LoadTexture("../assets/button_assets/neon_add_button.png");
        Asset::REMOVE_BUTTON = LoadTexture("../assets/button_assets/neon_remove_button.png");
        Asset::VIEW_BUTTON = LoadTexture("../assets/button_assets/neon_view_button.png");
        Asset::PLUS_SIGN = LoadTexture("../assets/city_assets/add_sign.png");
        Asset::HOUSE = LoadTexture("../assets/house_assets/house_1.png");
        Asset::PARK = LoadTexture("../assets/park_assets/park_1.png");
        Asset::FACTORY = LoadTexture("../assets/factory_assets/factory_1.png");
        Asset::RESIZED_PARK = LoadTextureFromImage(RESIZED_PARK_IMAGE);
        Asset::RESIZED_HOUSE = LoadTextureFromImage(RESIZED_HOUSE_IMAGE);
        Asset::RESIZED_FACTORY = LoadTextureFromImage(RESIZED_FACTORY_IMAGE);

        Asset::COLUMN_COUNT = 10;
        Asset::ROW_COUNT = 10;
        Asset::CITY_FIELD_WIDTH = Asset::CITY_FIELD.width;
        Asset::CITY_FIELD_HEIGHT = Asset::CITY_FIELD.height;
        Asset::BUILDING_SQUARE_WIDTH = 294.0f;
        Asset::BUILDING_SQUARE_HEIGHT = 294.0f;
        Asset::BUILDING_SQUARE_PADDING = 3.0f;
        Asset::BUTTON_PADDING = 10.0f;

        Asset::BUTTON_TEXTURES = {Asset::VIEW_BUTTON,
                                  Asset::REMOVE_BUTTON,
                                  Asset::ADD_BUTTON,
                                  Asset::RESIZED_HOUSE,
                                  Asset::RESIZED_FACTORY,
                                  Asset::RESIZED_PARK};

        Asset::BUTTON_NAMES = {"View", "Remove", "Add", "House", "Factory", "Park"};

        Asset::BUILDING_TEXTURES["House"] = Asset::HOUSE;
        Asset::BUILDING_TEXTURES["Factory"] = Asset::FACTORY;
        Asset::BUILDING_TEXTURES["Park"] = Asset::PARK;

        UnloadImage(RESIZED_HOUSE_IMAGE);
        UnloadImage(RESIZED_PARK_IMAGE);
        UnloadImage(RESIZED_FACTORY_IMAGE);

        return 0;
    }
};

std::string Game::GAME_TITLE {"vcs - a minimal city simulator"};
int Game::DEFAULT_FPS {120};
Color Game::DEFAULT_COLOR {17, 63, 42, 255};

Game::Game(float width, float height) {
    m_width = width; 
    m_height = height;
    m_camera_move_speed = 5.0f;
    m_camera = {Vector2(0, 0), Vector2(0, 0), 0.0f, 1.0f};
    m_camera_lower_bound = Vector2(0.0f, 0.0f);
    m_mode = Mode::SELECT_SQUARE_TO_VIEW;
}

Game::Game(int width, int height): Game((float)width, (float)height) {}

Game::Game(void): Game(GetScreenWidth(), GetScreenHeight()) {}

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

    m_camera_upper_bound = Vector2{.x = Asset::CITY_FIELD_WIDTH - m_width, 
                                   .y = Asset::CITY_FIELD_HEIGHT - m_height};

    m_map.emplace_back(Box()
                       .with_texture(Asset::CITY_FIELD)
                       .with_rectangle(Rectangle{.x = 0,
                                                 .y = 0, 
                                                 .width = Asset::CITY_FIELD_WIDTH,
                                                 .height = Asset::CITY_FIELD_HEIGHT})
                       .with_is_hoverable(false)
                       .with_hovered_color(BLANK)
                       .with_unhovered_color(WHITE));

    for (auto row{0}; row < Asset::ROW_COUNT; ++row) {
        for (auto column{0}; column < Asset::COLUMN_COUNT; ++column) {
            Rectangle position {.x = Asset::BUILDING_SQUARE_PADDING + column * 
                                (Asset::BUILDING_SQUARE_WIDTH + Asset::BUILDING_SQUARE_PADDING),
                                .y = Asset::BUILDING_SQUARE_PADDING + row * 
                                (Asset::BUILDING_SQUARE_HEIGHT + Asset::BUILDING_SQUARE_PADDING),
                                .width = Asset::BUILDING_SQUARE_WIDTH,
                                .height = Asset::BUILDING_SQUARE_HEIGHT};
 
            m_building_boxes.emplace_back(Building::CreateEmptyBuilding(),
                                          Box()
                                          .with_texture(Texture2D{})
                                          .with_rectangle(position)
                                          .with_is_hoverable(true)
                                          .with_hovered_color(BLANK)
                                          .with_unhovered_color(BLANK));
        }
    }

    for (auto row {0}; row < 6; ++row) {
        static Vector2 position {m_width - Asset::BUTTON_TEXTURES[row].width - Asset::BUTTON_PADDING, 
                                 m_height};
        position.y -= Asset::BUTTON_PADDING + Asset::BUTTON_TEXTURES[row].height;
        m_buttons[Asset::BUTTON_NAMES[row]] = Box()
                                              .with_texture(Asset::BUTTON_TEXTURES[row])
                                              .with_rectangle(Rectangle(position.x,
                                                                        position.y,
                                                                        Asset::BUTTON_TEXTURES[row].width,
                                                                        Asset::BUTTON_TEXTURES[row].height))
                                              .with_is_hoverable(true)
                                              .with_hovered_color(SKYBLUE)
                                              .with_unhovered_color(WHITE);
    }

    m_buttons["House"].m_unhovered_color = BLANK;
    m_buttons["House"].m_hovered_color = BLANK;

    m_buttons["Factory"].m_unhovered_color = BLANK;
    m_buttons["Factory"].m_hovered_color = BLANK;

    m_buttons["Park"].m_unhovered_color = BLANK;
    m_buttons["Park"].m_hovered_color = BLANK;
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
    static char* selected_building {"None"};
    auto mouse_position {GetMousePosition()};
    auto relative_mouse_position {GetScreenToWorld2D(mouse_position, m_camera)};

    if (m_buttons["Add"].IsClicked(mouse_position, MOUSE_LEFT_BUTTON)) {
        if (m_mode != Mode::SELECT_SQUARE_TO_ADD_TO) {
            m_buttons["House"].m_unhovered_color = 
                m_buttons["Factory"].m_unhovered_color =
                m_buttons["Park"].m_unhovered_color = Fade(WHITE, 0.25f);

            m_buttons["House"].m_hovered_color =
                m_buttons["Factory"].m_hovered_color =
                m_buttons["Park"].m_hovered_color = WHITE;

            m_mode = Mode::SELECT_BUILDING_TO_ADD;

            for (auto& [building, box]: m_building_boxes) {
                if (building.m_id == 0) {
                    
                    box.m_texture = Asset::PLUS_SIGN;
                    box.m_hovered_color = WHITE;
                    box.m_unhovered_color = Fade(WHITE, 0.25f);
                } else {
                    box.m_hovered_color = SKYBLUE;
                    box.m_unhovered_color = WHITE;
                }
            }
        }
    } else if (m_buttons["Remove"].IsClicked(mouse_position, MOUSE_LEFT_BUTTON)) {
        m_buttons["House"].m_unhovered_color = 
            m_buttons["Factory"].m_unhovered_color = 
            m_buttons["Park"].m_unhovered_color = BLANK;

        m_buttons["House"].m_hovered_color =
            m_buttons["Factory"].m_hovered_color =
            m_buttons["Park"].m_hovered_color = BLANK;

        m_mode = Mode::SELECT_SQUARE_TO_REMOVE_FROM;

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
    } else if (m_buttons["View"].IsClicked(mouse_position, MOUSE_LEFT_BUTTON)) {
        m_buttons["House"].m_unhovered_color =
            m_buttons["Factory"].m_unhovered_color =
            m_buttons["Park"].m_unhovered_color = BLANK;

        m_buttons["House"].m_hovered_color =
            m_buttons["Factory"].m_hovered_color =
            m_buttons["Park"].m_hovered_color = BLANK;

        m_mode = Mode::SELECT_SQUARE_TO_VIEW;

        for (auto& [building, box]: m_building_boxes) {
            if (building.m_id == 0) {
                box.m_texture = Texture2D();
                box.m_hovered_color = BLANK;
                box.m_unhovered_color = BLANK;
            } else {
                box.m_hovered_color = SKYBLUE;
                box.m_unhovered_color = WHITE;
            }
        }
    } 

    for (auto& [name, box]: m_buttons) {
        if (name == "House" || name == "Factory" || name == "Park") {
            if (box.IsClicked(mouse_position, MOUSE_LEFT_BUTTON)) {
                m_mode = Mode::SELECT_SQUARE_TO_ADD_TO;

                m_buttons["House"].m_unhovered_color = Fade(WHITE, 0.25f);
                m_buttons["Factory"].m_unhovered_color = Fade(WHITE, 0.25f);
                m_buttons["Park"].m_unhovered_color = Fade(WHITE, 0.25f);
                box.m_unhovered_color = WHITE;

                selected_building = const_cast<char*>(name);
            }
        }
    }

    

    for (auto& [building, box]: m_building_boxes) {
        if (box.IsHeld(relative_mouse_position, MOUSE_LEFT_BUTTON)) {
            switch (m_mode) {
                case Mode::SELECT_BUILDING_TO_ADD:
                    break;
                case Mode::SELECT_SQUARE_TO_ADD_TO:
                    box.m_texture = Asset::BUILDING_TEXTURES[selected_building];
                    box.m_unhovered_color = WHITE;
                    box.m_hovered_color = SKYBLUE;
                    building.m_id = ::g_building_id++;
                    break;
                case Mode::SELECT_SQUARE_TO_REMOVE_FROM:
                    box.m_texture = Texture2D();
                    box.m_hovered_color = BLANK;
                    box.m_unhovered_color = BLANK;
                    building.m_id = 0;
                    break;
                case Mode::SELECT_SQUARE_TO_VIEW:
                    break;
            }
        }
    }

    RegulateCamera(m_camera_lower_bound, m_camera_upper_bound);
    BeginDrawing();
    ClearBackground(Game::DEFAULT_COLOR);
    BeginMode2D(m_camera);
    for (auto& box: m_map) {
        box.Draw(mouse_position);
    }

    for (auto& [building, box]: m_building_boxes) {
        box.Draw(relative_mouse_position);
    }

    EndMode2D();

    for (auto& [name, button]: m_buttons) {
        button.Draw(mouse_position);
    }

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
