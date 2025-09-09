#pragma once

#include <SFML/Graphics.hpp>

#include "Vector2M.hpp"
#include "BinaryPositionEncoder.hpp"

namespace lib
{
    class BinaryPositionEncoder;
}

namespace engine
{
    enum class PointOutsideLocation;

    /// @brief Interface to be used by `engine::Object`
    class IScene
    {
    public:
        // if pointer to inherited class (Scene) is destroyed
        // only destructor for IScene is called; given virtual destructor is not implemented
        // this prevents the above
        virtual ~IScene() = default;

        // = 0 implies that defination will be provided in overridden class
        virtual sf::RenderWindow &GetWindow() = 0;
        virtual PointOutsideLocation GetOutsideLocation(const lib::Vector2M &p, int padding = 0) const = 0;

        virtual const lib::BinaryPositionEncoder &GetBPE() = 0;

        virtual void __AddDebugDrawables(std::unique_ptr<sf::Drawable> item) = 0;
    };
}