#include "Object.hpp"

#include "Scene.hpp"
#include "Helpers.hpp"

engine::Object::Object(engine::IScene &scene, float radius)
    : m_shape(radius), m_Scene(scene), m_ro_windowRO(scene.GetWindow())
{
    m_shape.setFillColor(sf::Color::Green);
    m_shape.setOrigin({0.f, 0.f});
    m_shape.setOutlineThickness(4);
    m_shape.setOutlineColor(sf::Color::Black);
}

// MARK: GETTERS AND SETTERS

float engine::Object::getRadius() const
{
    return m_shape.getRadius();
}

sf::Vector2f engine::Object::getPosition(bool fromCenter) const
{
    // no const & is used as values are being calculated at runtime
    // if `return a + b;` is used then
    // at runtime it allocates the memory at another place temporarily (for this scope only) to store the result
    // then if & is used, reference to temporary allocation will be returned
    // after exiting this scope the reference will become invalid
    // therefore "return by value" is used instead of "return by reference"
    return (fromCenter ? m_shape.getPosition() + m_shape.getRadius() : m_shape.getPosition());
}

void engine::Object::setPosition(const sf::Vector2f &newPos, bool fromCenter)
{
    m_shape.setPosition({
        fromCenter ? newPos - m_shape.getRadius() //
                   : newPos                       //
    });
}

/// @brief Get the velocity for last frame
/// @return `sf::Vector2f` representing velocity
const sf::Vector2f &engine::Object::getVelocity()
{
    return m_passedState.velocity;
}

void engine::Object::setVelocity(const sf::Vector2f &newVel)
{
    m_upcomingState.velocity = newVel;
}

// MARK: PUBLIC METHODS

void engine::Object::move(const sf::Vector2f &relativePos, bool fromCenter)
{
    // setPosition(getPosition(fromCenter) + relativePos, fromCenter);
}

void engine::Object::draw(sf::RenderWindow &window)
{
    window.draw(m_shape);
}

// MARK: PRIVATE METHODS
/*
Usage:
```cpp
updateState(); // stores data in m_passedState from m_shape

// apply state transformation to m_upcomingState

applyState(); // applies data from m_upcomingState to m_shape
```
*/

void engine::Object::updateState()
{
    m_passedState.position = getPosition();
}

void engine::Object::applyState()
{
    setPosition(m_upcomingState.position);
}

// MARK: Update

void engine::Object::update(float dt)
{
    // m_encodedPosition = m_Scene.GetBPE().getEncoded(m_shape.getPosition() + m_shape.getRadius());

    updateState();

    // m_upcomingState.position = m_passedState.position;
    m_upcomingState.position = m_passedState.position + (m_passedState.velocity * dt);
    m_upcomingState.velocity = m_passedState.velocity + m_passedState.acceleration * dt;

    applyState();
}