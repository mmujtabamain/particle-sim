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
        sf::Vector2f position;
        sf::Vector2f velocity;
        sf::Vector2f acceleration;
    };

    class Object
    {
    private: // PRIVATE MEMBERS
        // at the end of every frame th
        ObjectState currentState;

        engine::IScene &myScene;
        sf::RenderWindow &windowRO;

        uint16_t encodedPosition;

    public: // GETTERS AND SETTERS
        const sf::Vector2f &getPosition(bool fromCenter = true);
        const sf::Vector2f &getVelocity();
        float getRadius() const;

        void setPosition(const sf::Vector2f &newPos, bool fromCenter = true);
        void setVelocity(const sf::Vector2f &newVel);

    public: // PUBLIC METHODS
        sf::CircleShape shape;

        Object(engine::IScene &scene, float radius = 5);

        void draw(sf::RenderWindow &window);
        void update(float dt);

    private: // PRIVATE METHODS
    };
}