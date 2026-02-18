#ifndef GUI_HPP
#define GUI_HPP

#include <raylib.h>

#include <chrono>
#include <format>
#include <print>
#include <string>
#include <utility>
#include <vector>

#include "../data/building.hpp"
#include "asset.hpp"
#include "box.hpp"

using namespace std::chrono;

#define ASSET_PATH "../assets/"

enum class State {
    SELECT_BUILDING_TO_ADD,
    SELECT_SQUARE_TO_ADD_TO,
    SELECT_SQUARE_TO_REMOVE_FROM,
    SELECT_SQUARE_TO_VIEW,
    VIEWING_CITY_INFORMATION,
    VIEWING_BUILDING,
};

enum class Event {
    NIGHT_TIME,
    DAY_TIME,
    BUILDINGS_PRODUCE_RESOURCES,
    BUILDINGS_CONSUME_RESOURCES,
    BUILDINGS_INCREASE_SATISFACTION,
    BUILDINGS_DECREASE_SATISFACTION,
    BUILDINGS_INCREASE_POLLUTION,
    PARKS_DECREASE_POLLUTION,
    DESTROY_BUILDINGS,
};

class Game {
   public:
    static std::string GAME_TITLE;
    static i32 FPS;
    static Color BACKGROUND_COLOR;
    static Color NIGHT_COLOR;
    static Color DAY_COLOR;
    static i32 EVENT_TRIGGER_INTERVAL;
    static std::vector<Event> EVENT_LIST;

    time_point<steady_clock> m_current_time{};
    bool m_event_triggered{};
    i32 m_column_count{};
    i32 m_row_count{};
    Vector2 m_mouse_position{};
    Vector2 m_relative_mouse_position{};
    Rectangle m_protective_rectangle{};
    i32 m_selected_square_id{};

    City m_city{};
    Event m_event{};

    std::vector<Box> m_map{};
    std::vector<std::tuple<i32, Box>> m_building_boxes{};
    std::vector<std::tuple<std::string, Box>> m_buttons{};
    std::vector<std::tuple<std::string, Box>> m_building_buttons{};

    std::string m_selected_building_icon_type{};

    Vector2 m_camera_lower_bound{};
    Vector2 m_camera_upper_bound{};
    Camera2D m_camera{};
    State m_state{};
    f32 m_camera_move_speed{};
    f32 m_width{};
    f32 m_height{};

    Game(f32 width, f32 height);
    Game(i32 width, i32 height);
    Game(void);
    Rectangle GenerateProtectiveRectangle(void);
    void PositionAssets(void);
    void InitGame(void);
    void HandleInput(void);
    void HandleState(void);
    void RegulateCamera(void);
    void DrawCall(void);
    void GameLoop(void);
    void StartGame(void);
    void TriggerEvent(void);
};

#endif  // GUI_HPP
