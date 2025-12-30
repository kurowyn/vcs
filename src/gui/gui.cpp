#include "gui.hpp"

std::vector<Building> g_buildings{};

int Game::EVENT_TRIGGER_INTERVAL = 60;
std::string Game::GAME_TITLE{"vcs - a minimal city simulator"};
int Game::FPS{120};
Color Game::BACKGROUND_COLOR{17, 63, 42, 255};
Color Game::NIGHT_COLOR{70, 82, 125, 255};
Color Game::DAY_COLOR{WHITE};

std::vector<Event> Game::EVENT_LIST{Event::NIGHT_TIME,
                                    Event::DAY_TIME,
                                    Event::BUILDINGS_PRODUCE_RESOURCES,
                                    Event::BUILDINGS_CONSUME_RESOURCES,
                                    Event::BUILDINGS_INCREASE_SATISFACTION,
                                    Event::BUILDINGS_DECREASE_SATISFACTION,
                                    Event::BUILDINGS_INCREASE_POLLUTION,
                                    Event::DESTROY_BUILDINGS};

Game::Game(float width, float height) {
    m_width = width;
    m_height = height;
    m_camera_move_speed = 5.0f;
    m_camera = {Vector2(0, 0), Vector2(0, 0), 0.0f, 1.0f};
    m_camera_lower_bound = Vector2(0.0f, 0.0f);
    m_state = State::SELECT_SQUARE_TO_VIEW;
    m_column_count = 10;
    m_row_count = 10;
    m_current_time = steady_clock::now();
    m_selected_building_icon_type = "None";
}

Game::Game(int width, int height) : Game((float)width, (float)height) {}

Game::Game(void) : Game(GetScreenWidth(), GetScreenHeight()) {}

void Game::InitGame(void) {
    InitWindow(m_width, m_height, Game::GAME_TITLE.c_str());
    SetExitKey(KEY_NULL);
    SetConfigFlags(FLAG_VSYNC_HINT);
    SetTargetFPS(Game::FPS);
    PositionAssets();
    m_protective_rectangle = GenerateProtectiveRectangle();
}

void Game::PositionAssets(void) {
    Asset::LoadAssets();

    m_map.emplace_back(
        Box()
            .with_texture(Asset::CITY_FIELD)
            .with_rectangle(Rectangle{.x = 0,
                                      .y = 0,
                                      .width = Asset::CITY_FIELD.width,
                                      .height = Asset::CITY_FIELD.height})
            .with_is_hoverable(false)
            .with_hovered_color(BLANK)
            .with_unhovered_color(WHITE));

    m_buttons.emplace_back("View", Box()
                                       .with_texture(Asset::VIEW_BUTTON)
                                       .with_rectangle(Rectangle())
                                       .with_is_hoverable(true)
                                       .with_hovered_color(SKYBLUE)
                                       .with_unhovered_color(WHITE));

    m_buttons.emplace_back("Remove", Box()
                                         .with_texture(Asset::REMOVE_BUTTON)
                                         .with_rectangle(Rectangle())
                                         .with_is_hoverable(true)
                                         .with_hovered_color(SKYBLUE)
                                         .with_unhovered_color(WHITE));

    m_buttons.emplace_back("Add", Box()
                                      .with_texture(Asset::ADD_BUTTON)
                                      .with_rectangle(Rectangle())
                                      .with_is_hoverable(true)
                                      .with_hovered_color(SKYBLUE)
                                      .with_unhovered_color(WHITE));

    m_buttons.emplace_back("City",
                           Box()
                               .with_texture(Asset::VIEW_CITY_INFO_BUTTON)
                               .with_rectangle(Rectangle())
                               .with_is_hoverable(true)
                               .with_hovered_color(SKYBLUE)
                               .with_unhovered_color(WHITE));

    m_building_buttons.emplace_back("House",
                                    Box()
                                        .with_texture(Asset::RESIZED_HOUSE)
                                        .with_rectangle(Rectangle())
                                        .with_is_hoverable(true)
                                        .with_hovered_color(BLANK)
                                        .with_unhovered_color(BLANK));
    m_building_buttons.emplace_back("Factory",
                                    Box()
                                        .with_texture(Asset::RESIZED_FACTORY)
                                        .with_rectangle(Rectangle())
                                        .with_is_hoverable(true)
                                        .with_hovered_color(BLANK)
                                        .with_unhovered_color(BLANK));
    m_building_buttons.emplace_back("Park",
                                    Box()
                                        .with_texture(Asset::RESIZED_PARK)
                                        .with_rectangle(Rectangle())
                                        .with_is_hoverable(true)
                                        .with_hovered_color(BLANK)
                                        .with_unhovered_color(BLANK));

    Vector2 button_position{
        .x = m_width - Asset::ADD_BUTTON.width - Asset::BUTTON_PADDING,
        .y = m_height};

    for (auto& button : m_buttons) {
        button_position.y -=
            std::get<Box>(button).m_texture.height + Asset::BUTTON_PADDING;
        std::get<Box>(button).m_rectangle =
            Rectangle{.x = button_position.x,
                      .y = button_position.y,
                      .width = std::get<Box>(button).m_texture.width,
                      .height = std::get<Box>(button).m_texture.height};
    }

    for (auto& button : m_building_buttons) {
        button_position.y -=
            std::get<Box>(button).m_texture.height + Asset::BUTTON_PADDING;
        std::get<Box>(button).m_rectangle =
            Rectangle{.x = button_position.x,
                      .y = button_position.y,
                      .width = std::get<Box>(button).m_texture.width,
                      .height = std::get<Box>(button).m_texture.height};
    }

    for (auto row{0}; row < m_row_count; ++row) {
        for (auto column{0}; column < m_column_count; ++column) {
            Rectangle rectangle{.x = Asset::BUILDING_SQUARE_PADDING +
                                     column * (Asset::BUILDING_SQUARE_WIDTH +
                                               Asset::BUILDING_SQUARE_PADDING),
                                .y = Asset::BUILDING_SQUARE_PADDING +
                                     row * (Asset::BUILDING_SQUARE_HEIGHT +
                                            Asset::BUILDING_SQUARE_PADDING),
                                .width = Asset::BUILDING_SQUARE_WIDTH,
                                .height = Asset::BUILDING_SQUARE_HEIGHT};

            m_building_boxes.emplace_back(0, Box()
                                                 .with_texture(Texture2D())
                                                 .with_rectangle(rectangle)
                                                 .with_is_hoverable(true)
                                                 .with_hovered_color(BLANK)
                                                 .with_unhovered_color(BLANK));
        }
    }

    m_camera_upper_bound = {.x = Asset::CITY_FIELD.width - m_width,
                            .y = Asset::CITY_FIELD.height - m_height};
}

void Game::RegulateCamera(void) {
    if (m_camera.target.x >= m_camera_upper_bound.x) {
        m_camera.target.x = m_camera_upper_bound.x;
    }

    if (m_camera.target.y >= m_camera_upper_bound.y) {
        m_camera.target.y = m_camera_upper_bound.y;
    }

    if (m_camera.target.x <= m_camera_lower_bound.x) {
        m_camera.target.x = m_camera_lower_bound.x;
    }

    if (m_camera.target.y <= m_camera_lower_bound.y) {
        m_camera.target.y = m_camera_lower_bound.y;
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

    if (m_camera.zoom <= 0) return auto old_camera_zoom = m_camera.zoom;
    if (IsKeyPressed(KEY_MINUS)) {
        m_camera.zoom =
            m_camera.zoom > 0 ? m_camera.zoom - 0.1f : m_camera.zoom;
    } else if (IsKeyPressed(KEY_EQUAL)) {
        m_camera.zoom += 0.1f;
    }

    m_camera.zoom += (GetMouseWheelMove() * 0.1f);

    if (m_camera.zoom < 0) {
        m_camera.zoom = old_camera_zoom;
    }
    return;
}

Rectangle Game::GenerateProtectiveRectangle(void) {
    Rectangle rectangle{};
    rectangle.x =
        m_width - (std::get<Box>(m_building_buttons.back()).m_texture.width +
                   Asset::BUTTON_PADDING);
    rectangle.y = m_height;
    rectangle.width = m_width - rectangle.x;

    for (auto& button : m_buttons) {
        rectangle.y -=
            std::get<Box>(button).m_texture.height + Asset::BUTTON_PADDING;
    }

    for (auto& button : m_building_buttons) {
        rectangle.y -=
            std::get<Box>(button).m_texture.height + Asset::BUTTON_PADDING;
    }

    rectangle.height = m_height - rectangle.y;

    return rectangle;
}

void Game::DrawCall(void) {
    m_mouse_position = GetMousePosition();
    m_relative_mouse_position = GetScreenToWorld2D(m_mouse_position, m_camera);

    // city button
    if (std::get<Box>(m_buttons[3])
            .IsClicked(m_mouse_position, MOUSE_LEFT_BUTTON)) {
        m_state = State::VIEWING_CITY_INFORMATION;
        for (auto& [type, building_button] : m_building_buttons) {
            building_button.m_unhovered_color = BLANK;
            building_button.m_hovered_color = BLANK;
        }

        for (auto& [id, building] : m_building_boxes) {
            if (id == 0) {
                building.m_unhovered_color = BLANK;
                building.m_hovered_color = BLANK;
            } else {
                building.m_unhovered_color = WHITE;
                building.m_hovered_color = WHITE;
            }
        }
    } else if (std::get<Box>(m_buttons[2])
                   .IsClicked(m_mouse_position, MOUSE_LEFT_BUTTON)) {
        m_state = State::SELECT_BUILDING_TO_ADD;
        for (auto& [type, building_button] : m_building_buttons) {
            building_button.m_unhovered_color = Fade(WHITE, 0.25f);
            building_button.m_hovered_color = WHITE;
        }

        for (auto& [id, building] : m_building_boxes) {
            if (id == 0) {
                building.m_texture = Asset::PLUS_SIGN;
                building.m_unhovered_color = Fade(WHITE, 0.25f);
                building.m_hovered_color = WHITE;
            } else {
                building.m_unhovered_color = WHITE;
                building.m_hovered_color = SKYBLUE;
            }
        }
        // remove button
    } else if (std::get<Box>(m_buttons[1])
                   .IsClicked(m_mouse_position, MOUSE_LEFT_BUTTON)) {
        m_state = State::SELECT_SQUARE_TO_REMOVE_FROM;
        for (auto& [type, building_button] : m_building_buttons) {
            building_button.m_unhovered_color = BLANK;
            building_button.m_hovered_color = BLANK;
        }

        for (auto& [id, building] : m_building_boxes) {
            if (id == 0) {
                building.m_texture = Texture2D();
                building.m_unhovered_color = BLANK;
                building.m_hovered_color = BLANK;
            } else {
                building.m_unhovered_color = WHITE;
                building.m_hovered_color = RED;
            }
        }
        m_selected_building_icon_type = "None";
        // view button
    } else if (std::get<Box>(m_buttons[0])
                   .IsClicked(m_mouse_position, MOUSE_LEFT_BUTTON)) {
        m_state = State::SELECT_SQUARE_TO_VIEW;
        for (auto& [type, building_button] : m_building_buttons) {
            building_button.m_unhovered_color = BLANK;
            building_button.m_hovered_color = BLANK;
        }

        for (auto& [id, building] : m_building_boxes) {
            if (id == 0) {
                building.m_texture = Texture2D();
                building.m_unhovered_color = BLANK;
                building.m_hovered_color = BLANK;
            } else {
                building.m_unhovered_color = WHITE;
                building.m_hovered_color = YELLOW;
            }
        }
        m_selected_building_icon_type = "None";
    }

    for (auto& [type, building_button] : m_building_buttons) {
        if ((m_state == State::SELECT_BUILDING_TO_ADD ||
             m_state == State::SELECT_SQUARE_TO_ADD_TO) &&
            building_button.IsClicked(m_mouse_position, MOUSE_LEFT_BUTTON)) {
            for (auto& [type, building_button] : m_building_buttons) {
                building_button.m_unhovered_color = Fade(WHITE, 0.25f);
                building_button.m_hovered_color = WHITE;
            }

            m_state = State::SELECT_SQUARE_TO_ADD_TO;
            building_button.m_unhovered_color = WHITE;
            building_button.m_hovered_color = WHITE;
            m_selected_building_icon_type = type;
            break;
        }
    }

    for (auto& [id, building_box] : m_building_boxes) {
        bool isDown = building_box.IsClicked(m_relative_mouse_position,
                                             MOUSE_LEFT_BUTTON);
        bool isColliding =
            CheckCollisionPointRec(m_mouse_position, m_protective_rectangle);

        if (!(isDown && !isColliding)) continue;

        switch (m_state) {
            case State::SELECT_SQUARE_TO_VIEW:
                if (id != 0) {
                    m_state = State::VIEWING_BUILDING;
                    m_selected_square_id = id;
                }
                break;
            case State::SELECT_SQUARE_TO_ADD_TO: {
                if (id == 0) {
                    m_city.AddBuilding(Building(m_selected_building_icon_type));
                    id = m_city.m_buildings.back().m_id;
                    // there was a building
                } else {
                    Building old_building{m_city.SearchBuilding(id)};
                    m_city.ModifyBuilding(
                        id, Building(Building::GenerateBuildingName(
                                         m_selected_building_icon_type),
                                     m_selected_building_icon_type,
                                     old_building.m_id));
                }

                building_box.m_texture =
                    Asset::TEXTURE_MAP[m_selected_building_icon_type];
                building_box.m_unhovered_color = WHITE;
                building_box.m_hovered_color = SKYBLUE;
                break;
            }
            case State::SELECT_SQUARE_TO_REMOVE_FROM: {
                m_city.RemoveBuilding(id);
                building_box.m_texture = Texture2D();
                building_box.m_hovered_color = BLANK;
                building_box.m_unhovered_color = BLANK;
                id = 0;
                break;
            }
        }
    }

    if (m_state == State::VIEWING_BUILDING) {
        if (IsKeyPressed(KEY_ESCAPE) || IsMouseButtonDown(MOUSE_RIGHT_BUTTON)) {
            m_state = State::SELECT_SQUARE_TO_VIEW;
        }

        BeginDrawing();

        ClearBackground(Color(70, 77, 79, 255));

        Building selected_building{m_city.SearchBuilding(m_selected_square_id)};
        Texture2D selected_building_texture{
            Asset::TEXTURE_MAP[selected_building.m_type]};

        DrawTextEx(Asset::DEFAULT_FONT, "BUILDING INFORMATION", Vector2(10, 10),
                   40, 1.5f, LIME);

        DrawTextureV(selected_building_texture, {60, 90}, WHITE);

        std::array building_information_strings{
            std::format("ID: {}", selected_building.m_id),
            std::format("Name: {}", selected_building.m_name),
            std::format("Type: {}", selected_building.m_type),
            std::format("Pollution Effect: {}",
                        selected_building.m_pollution_effect),
            std::format("Satisfaction Effect: {}",
                        selected_building.m_satisfaction_effect),
            std::format("Inhabitant Count: {}",
                        selected_building.m_inhabitant_count),
            std::format("Inhabitant Capacity: {}",
                        selected_building.m_inhabitant_capacity),
            std::format("Consumed Water: {} {}(s)",
                        selected_building.m_consumed_water.m_quantity,
                        selected_building.m_consumed_water.m_unit),
            std::format("Consumed Electricity: {} {}(s)",
                        selected_building.m_consumed_electricity.m_quantity,
                        selected_building.m_consumed_electricity.m_unit),
            std::format("Produced Water: {} {}(s)",
                        selected_building.m_produced_water.m_quantity,
                        selected_building.m_produced_water.m_unit),
            std::format("Produced Electricity: {} {}(s)",
                        selected_building.m_produced_electricity.m_quantity,
                        selected_building.m_produced_electricity.m_unit)};

        for (auto i{0}; i < building_information_strings.size(); ++i) {
            DrawTextEx(
                Asset::DEFAULT_FONT, building_information_strings[i].c_str(),
                Vector2(selected_building_texture.width + 40, 70 + 40 * i), 40,
                1.5f, WHITE);
        }

        DrawTextEx(Asset::DEFAULT_FONT, "Press ESC or right click to go back!",
                   Vector2(20, m_height - 100), 50, 1.5f, WHITE);

        EndDrawing();
    } else if (m_state == State::VIEWING_CITY_INFORMATION) {
        if (IsKeyPressed(KEY_ESCAPE) || IsMouseButtonDown(MOUSE_RIGHT_BUTTON)) {
            m_state = State::SELECT_SQUARE_TO_VIEW;
        }

        BeginDrawing();

        ClearBackground(Color(70, 77, 79, 255));

        DrawTextEx(Asset::DEFAULT_FONT, "CITY INFORMATION", Vector2(10, 10), 40,
                   1.5f, LIME);

        std::array building_information_strings{
            std::format("Name: {}", m_city.m_name),
            std::format("Population: {}", m_city.m_population),
            std::format("Satisfaction Rate: {}", m_city.m_satisfaction_level),
            std::format("Pollution Rate: {}", m_city.m_pollution_level),
            std::format("Water Consumption: {} {}(s)",
                        m_city.m_consumed_water.m_quantity,
                        m_city.m_consumed_water.m_unit),
            std::format("Electricity Consumption: {} {}(s)",
                        m_city.m_consumed_electricity.m_quantity,
                        m_city.m_consumed_electricity.m_unit),
            std::format("Water Production: {} {}(s)",
                        m_city.m_produced_water.m_quantity,
                        m_city.m_produced_water.m_unit),
            std::format("Electricity Production: {} {}(s)",
                        m_city.m_produced_electricity.m_quantity,
                        m_city.m_produced_electricity.m_unit),
        };

        for (auto i{0}; i < building_information_strings.size(); ++i) {
            DrawTextEx(Asset::DEFAULT_FONT,
                       building_information_strings[i].c_str(),
                       Vector2(10, 70 + 40 * i), 40, 1.5f, WHITE);
        }

        DrawTextEx(Asset::DEFAULT_FONT, "Press ESC or right click to go back!",
                   Vector2(20, m_height - 100), 50, 1.5f, WHITE);

        EndDrawing();

    } else {
        RegulateCamera();
        BeginDrawing();
        ClearBackground(Game::BACKGROUND_COLOR);

        BeginMode2D(m_camera);
        for (auto& map : m_map) {
            map.Draw();
        }
        for (auto& [id, building] : m_building_boxes) {
            building.Draw(m_relative_mouse_position);
        }
        EndMode2D();

        for (auto& [type, button] : m_buttons) {
            button.Draw(m_mouse_position);
        }

        for (auto& [type, building_button] : m_building_buttons) {
            building_button.Draw(m_mouse_position);
        }

        switch (m_state) {
            case State::SELECT_BUILDING_TO_ADD:
                DrawTextEx(Asset::DEFAULT_FONT, "Select a building to add!",
                           Vector2(10, 10), 40, 1.5f, WHITE);
                break;
            case State::SELECT_SQUARE_TO_ADD_TO:
                DrawTextEx(
                    Asset::DEFAULT_FONT,
                    std::format("Selected: {}", m_selected_building_icon_type)
                        .c_str(),
                    Vector2(10, 10), 40, 1.5f, WHITE);
                DrawTextEx(Asset::DEFAULT_FONT,
                           "Select a square to add the building to!",
                           Vector2(10, 50), 40, 1.5f, WHITE);
                break;
            case State::SELECT_SQUARE_TO_REMOVE_FROM:
                DrawTextEx(Asset::DEFAULT_FONT,
                           "Select a square to remove a building from!",
                           Vector2(10, 10), 40, 1.5f, WHITE);
                break;
            case State::SELECT_SQUARE_TO_VIEW:
                DrawTextEx(Asset::DEFAULT_FONT, "Select a square to view!",
                           Vector2(10, 10), 40, 1.5f, WHITE);
                break;
        }

        if (m_event_triggered) {
            DrawTextEx(Asset::DEFAULT_FONT, "Random Event!",
                       Vector2(20, m_height - 100), 50, 1.5f, WHITE);
            // Makes this stay for only five seconds.
            auto time_elapsed{static_cast<int>(
                duration<double>(steady_clock::now() - m_current_time)
                    .count())};
            if (time_elapsed == 5) m_event_triggered = false;
        }

        EndDrawing();
    }
}

void Game::TriggerEvent(void) {
    auto delta{static_cast<int>(
        duration<double>(steady_clock::now() - m_current_time).count())};

    if (delta == Game::EVENT_TRIGGER_INTERVAL) {
        m_current_time = steady_clock::now();
        m_event_triggered = true;
        m_event = Game::EVENT_LIST[Random::GenerateRandomInteger(
            0, Game::EVENT_LIST.size() - 1)];

        if (m_event == Event::NIGHT_TIME) {
            for (auto& map : m_map) {
                map.m_unhovered_color = Game::NIGHT_COLOR;
            }
        } else if (m_event == Event::DAY_TIME) {
            for (auto& map : m_map) map.m_unhovered_color = Game::DAY_COLOR;

        } else if (m_event == Event::BUILDINGS_PRODUCE_RESOURCES) {
            m_city.ProduceResources();
        } else if (m_event == Event::BUILDINGS_CONSUME_RESOURCES) {
            m_city.ConsumeResources();
        } else if (m_event == Event::BUILDINGS_INCREASE_SATISFACTION) {
            for (auto& building : m_city.m_buildings) {
                m_city.m_satisfaction_level += building.m_satisfaction_effect;
            }
        } else if (m_event == Event::BUILDINGS_INCREASE_POLLUTION) {
            for (auto& building : m_city.m_buildings) {
                m_city.m_pollution_level += building.m_pollution_effect;
            }
        } else if (m_event == Event::PARKS_DECREASE_POLLUTION) {
            for (auto& building : m_city.m_buildings)
                if (building.m_type == BuildingType::PARK) {
                    m_city.ModifyPollutionLevel(
                        -Random::GenerateRandomInteger(10, 1000));
                }
        } else if (m_event == Event::DESTROY_BUILDINGS) {
            if (m_city.m_satisfaction_level < 100) {
                for (auto& [id, building_box] : m_building_boxes) {
                    if (id != 0 && Random::GenerateRandomInteger(0, 1) == 1) {
                        if (m_state == State::SELECT_SQUARE_TO_ADD_TO) {
                            building_box.m_texture = Asset::PLUS_SIGN;
                            building_box.m_hovered_color = WHITE;
                            building_box.m_unhovered_color = Fade(WHITE, 0.25f);
                        } else {
                            building_box.m_texture = Texture2D();
                            building_box.m_hovered_color = BLANK;
                            building_box.m_unhovered_color = BLANK;
                        }
                        m_city.RemoveBuilding(id);
                        id = 0;
                    }
                }
            }
        }
    }
}

void Game::GameLoop(void) {
    while (!WindowShouldClose()) {
        TriggerEvent();
        HandleInput();
        DrawCall();
    }
    CloseWindow();
}

void Game::StartGame(void) {
    InitGame();
    GameLoop();
}
