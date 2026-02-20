#pragma once
#include <glm/glm.hpp>

struct Camera
{
    glm::vec2 m_position{};
    float m_zoom = 1.0f; // 1.0 = no zoom

    const float m_width;
    const float m_height;

    Camera(const float _width, const float _height)
        : m_width(_width)
        , m_height(_height)
    { }

    inline glm::vec2 world_to_screen(const glm::vec2& worldPos)
    {
        glm::vec2 centered = (worldPos - m_position) * m_zoom;
        return centered + glm::vec2(this->m_width, this->m_height) * 0.5f;
    }
};