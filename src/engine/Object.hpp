#pragma once

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include <iostream>

#include "IScene.hpp"

namespace engine
{
    struct ObjectState
    {
        sf::Vector2f position{0.f, 0.f};
        sf::Vector2f velocity{0.f, 0.f};
        sf::Vector2f acceleration{0.f, 0.f};
    };

    class Object
    {
    private: // PRIVATE MEMBERS
        /// @brief State of previous frame
        ObjectState m_passedState;
        /// @brief State of upcoming frame
        ObjectState m_upcomingState;

        sf::CircleShape m_shape;

        engine::IScene &m_Scene;
        sf::RenderWindow &m_window;
        const sf::RenderWindow &m_ro_window;

        uint16_t m_encodedPosition;

    public: // GETTERS AND SETTERS
        // Contains no dependency on other getters and setters

        float getRadius() const;

        sf::Vector2f getPosition(bool fromCenter = true) const; // no const & explanation in function
        void setPosition(const sf::Vector2f &newPos, bool fromCenter = true);

        const sf::Vector2f &getVelocity();
        void setVelocity(const sf::Vector2f &newVel);

        const sf::Vector2f &getAcceleration();
        void setAcceleration(const sf::Vector2f &newAcc);

    private: // PRIVATE METHODS
        void updateState();
        void applyState();

    public: // PUBLIC METHODS
        Object(engine::IScene &scene, float radius = 2);

        void move(const sf::Vector2f &relativePos, bool fromCenter = true);

        void draw(sf::RenderWindow &window);
        void update(float dt);
    };
}
