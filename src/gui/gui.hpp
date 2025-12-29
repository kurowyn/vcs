#ifndef GUI_HPP
#define GUI_HPP

#include <raylib.h>
#include <string>
#include <vector>
#include <print>
#include "box.hpp"
#include "../data/building.hpp"

#define ASSET_PATH "../assets/"

enum class Mode {
    SELECT_BUILDING_TO_ADD = 1,
    SELECT_SQUARE_TO_ADD_TO,
    SELECT_SQUARE_TO_REMOVE_FROM,
    SELECT_SQUARE_TO_VIEW,
};

class Game {
    public:
        static std::string GAME_TITLE;
        static int DEFAULT_FPS;
        static Color DEFAULT_COLOR;

        std::vector<std::tuple<Building, Box>> m_building_boxes {};
        std::vector<Box> m_map {};
        std::map<const char*, Box> m_buttons {};
        Vector2 m_camera_lower_bound {};
        Vector2 m_camera_upper_bound {};
        Camera2D m_camera {};
        Mode m_mode {};
        float m_camera_move_speed {};
        float m_width {};
        float m_height {};

        Game(float width, float height);
        Game(int width, int height);
        Game(void);
        const char* ResolveMode(Mode mode);
        void PositionAssets(void);
        int InitGame(void);
        void HandleInput(void);
        void RegulateCamera(Vector2 lower_bound, Vector2 upper_bound);
        void AddBuilding(void);
        void RemoveBuilding(void);
        void ViewBuilding(void);
        void DrawCall(void);
        void GameLoop(void);
        int StartGame(void);
};

#endif // GUI_HPP
