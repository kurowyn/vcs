#ifndef BOX_HPP
#define BOX_HPP

#include <raylib.h>

// It's slightly less horrible, now.
struct Box {
    Texture2D m_texture;
    Rectangle m_rectangle {};
    bool m_is_hoverable {};
    Color m_hovered_color {};
    Color m_unhovered_color {};
    bool IsClicked(Vector2 mouse_position, MouseButton mouse_button);
    bool IsHeld(Vector2 mouse_position, MouseButton mouse_button);
    bool IsHovered(Vector2 mouse_position);
    void Draw(Vector2 mouse_position = {0, 0}, MouseButton mouse_button = MOUSE_BUTTON_LEFT);
};

#endif // BOX_HPP

