#include "box.hpp"

bool Box::IsClicked(Vector2 mouse_position, MouseButton mouse_button) {
    return IsHovered(mouse_position) && IsMouseButtonPressed(mouse_button);
}

bool Box::IsHeld(Vector2 mouse_position, MouseButton mouse_button) {
    return IsHovered(mouse_position) && IsMouseButtonDown(mouse_button);
}

bool Box::IsHovered(Vector2 mouse_position) {
    return CheckCollisionPointRec(mouse_position, m_rectangle);
}

void Box::Draw(Vector2 mouse_position, 
               MouseButton mouse_button) {
    Color color {};

    if (!m_is_hoverable) {
        color = m_unhovered_color;
    } else {
        color = IsHovered(mouse_position) ? m_hovered_color : m_unhovered_color;
    }

    switch (m_texture.id) {
        case 0:
            DrawRectangleRec(m_rectangle, color);
            break;
        default:
            DrawTextureV(m_texture, Vector2(m_rectangle.x, m_rectangle.y), color);
            break;
    }
}
