#include "Object.hpp"

#include "Scene.hpp"
#include "Helpers.hpp"

engine::Object::Object(engine::IScene &scene, float radius)
    : shape(radius), myScene(scene), windowRO(scene.getWindow())
{
    shape.setFillColor(sf::Color::Green);
    shape.setOrigin({0.5f, 0.5f});
    shape.setOutlineThickness(4);
    shape.setOutlineColor(sf::Color::Black);
}

// GETTERS AND SETTERS
const sf::Vector2f &engine::Object::getPosition(bool fromCenter)
{
    PRINT("NOT IMPLEMENTED");
    return {0.f, 0.f};
}

const sf::Vector2f &engine::Object::getVelocity()
{
    PRINT("NOT IMPLEMENTED");
    return {0.f, 0.f};
}

float engine::Object::getRadius() const
{
    PRINT("NOT IMPLEMENTED");
    return 0.f;
}

void engine::Object::setPosition(const sf::Vector2f &newPos, bool fromCenter)
{
    PRINT("NOT IMPLEMENTED");
}

void engine::Object::setVelocity(const sf::Vector2f &newVel)
{
    PRINT("NOT IMPLEMENTED");
}

// PUBLIC METHODS
void engine::Object::draw(sf::RenderWindow &window)
{
    window.draw(shape);
}

void engine::Object::update(float dt)
{
    encodedPosition = myScene.getBPE().getEncoded(shape.getPosition() + shape.getRadius());
}
