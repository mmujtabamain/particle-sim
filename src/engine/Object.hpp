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
    private:
        sf::CircleShape shape;
        ObjectState currentFrameState;

        engine::IScene &myScene;
        sf::RenderWindow &windowRO;

    public:
        Object(engine::IScene &scene, float radius = 5);

        sf::Vector2f getCenter() const;
        const sf::Vector2f &getVelocity() const;
        float getRadius() const;

        void setPosition(const sf::Vector2f &newPos);
        void setVelocity(const sf::Vector2f &newVel);

        void draw(sf::RenderWindow &window);
        void update(float dt);

        void physicsLoop(float dt);
    };
}