#pragma once

#include <SFML/Graphics.hpp>

#include "Vector2M.hpp"

namespace lib
{
    /// @brief Consists of only two `lib::Vector2M`s one for size and another for position
    class RectArea
    {
    public:
        Vector2M size;
        Vector2M position;

    public:
        RectArea(Vector2M size = Vector2M::zero, Vector2M position = Vector2M::zero) : size(size), position(position) {}
    };
}