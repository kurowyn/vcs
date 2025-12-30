#ifndef GUI_HPP
#define GUI_HPP

#include <raylib.h>
#include <utility>
#include <chrono>
#include <string>
#include <vector>
#include <print>
#include <format>
#include "box.hpp"
#include "../data/building.hpp"
#include "asset.hpp"

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

// And that should be more than enough.
// Then, we implement the "show city details" button, and that. is. all.
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
        static int FPS;
        static Color BACKGROUND_COLOR;
        static Color NIGHT_COLOR;
        static Color DAY_COLOR;
        static int EVENT_TRIGGER_INTERVAL;
        static std::vector<Event> EVENT_LIST;

        time_point<steady_clock> m_current_time {};
        bool m_event_triggered {};
        int m_column_count {};
        int m_row_count {};
        Vector2 m_mouse_position {};
        Vector2 m_relative_mouse_position {};
        Rectangle m_protective_rectangle {};
        int m_selected_square_id {};

        City m_city {};
        Event m_event {};

        std::vector<Box> m_map {};
        std::vector<std::tuple<int, Box>> m_building_boxes {};
        std::vector<std::tuple<std::string, Box>> m_buttons {};
        std::vector<std::tuple<std::string, Box>> m_building_buttons {};

        std::string m_selected_building_icon_type {"None"};

        Vector2 m_camera_lower_bound {};
        Vector2 m_camera_upper_bound {};
        Camera2D m_camera {};
        State m_state {};
        float m_camera_move_speed {};
        float m_width {};
        float m_height {};

        Game(float width, float height);
        Game(int width, int height);
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

#endif // GUI_HPP
