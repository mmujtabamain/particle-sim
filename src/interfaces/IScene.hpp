#pragma once

#include <SFML/Graphics.hpp>

#include "Vector2M.hpp"

namespace engine
{
    /// @brief Interface to be used by `engine::Object`
    class IScene
    {
    public:
        // if pointer to inherited class (Scene) is destroyed
        // only destructor for IScene is called; given virtual destructor is not implemented
        // this prevents the above
        virtual ~IScene() = default;

        // = 0 implies that defination will be provided in overridden class
        virtual sf::RenderWindow &getWindow() = 0;
        virtual bool isPointOutsideWindow(const lib::Vector2M &p) const = 0;

        virtual void __addDebugDrawables(std::unique_ptr<sf::Drawable> item) = 0;
    };
}