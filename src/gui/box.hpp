#ifndef BOX_HPP
#define BOX_HPP

#include <raylib.h>

#include "utils.hpp"

// It's slightly less horrible, now.
struct Box {
    Texture2D m_texture;
    Rectangle m_rectangle{};
    bool m_is_hoverable{};
    Color m_hovered_color{};
    Color m_unhovered_color{};

    WITH_CONSTRUCTOR(Box, Texture2D, texture);
    WITH_CONSTRUCTOR(Box, Rectangle, rectangle);
    WITH_CONSTRUCTOR(Box, bool, is_hoverable);
    WITH_CONSTRUCTOR(Box, Color, hovered_color);
    WITH_CONSTRUCTOR(Box, Color, unhovered_color);

    bool IsClicked(Vector2 mouse_position, MouseButton mouse_button);
    bool IsHeld(Vector2 mouse_position, MouseButton mouse_button);
    bool IsHovered(Vector2 mouse_position);
    void Draw(Vector2 mouse_position = {0, 0});
};

#endif  // BOX_HPP
