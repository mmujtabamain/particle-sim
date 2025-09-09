#include "Object.hpp"

#include "Scene.hpp"
#include "Helpers.hpp"

engine::Object::Object(engine::IScene &scene, float radius)
    : m_shape(radius), m_Scene(scene), m_window(scene.GetWindow()), m_ro_window(scene.GetWindow())
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

/// @brief Set the velocity for upcoming frame
/// @param newVel New velocity
void engine::Object::setVelocity(const sf::Vector2f &newVel)
{
    m_upcomingState.velocity = newVel;
}

const sf::Vector2f &engine::Object::getAcceleration()
{
    return m_passedState.acceleration;
}

void engine::Object::setAcceleration(const sf::Vector2f &newAcc)
{
    m_upcomingState.acceleration = newAcc;
}

// MARK: PUBLIC METHODS

void engine::Object::move(const sf::Vector2f &relativePos, bool fromCenter)
{
    setPosition(getPosition(fromCenter) + relativePos, fromCenter);
}

void engine::Object::draw(sf::RenderWindow &window)
{
    window.draw(m_shape);
}

// MARK: PRIVATE METHODS
/*
Usage:
```cpp
setupState(); // stores data in m_passedState from m_shape

// apply state transformation to m_upcomingState

applyState(); // applies data from m_upcomingState to m_shape
```
*/

void engine::Object::setupState()
{
    // getPosition for accurate position
    m_passedState.position = getPosition();
    // pass upcoming state into passed state (upcoming state has been resovled)
    m_passedState.velocity = m_upcomingState.velocity;
    m_passedState.acceleration = m_upcomingState.acceleration;
    // clear upcoming state
    m_upcomingState.position = utils::zeroVector2f;
    m_upcomingState.velocity = utils::zeroVector2f;
    m_upcomingState.acceleration = utils::zeroVector2f;
}

void engine::Object::applyState()
{
    setPosition(m_upcomingState.position);
}

// MARK: Update

void engine::Object::update(float dt)
{
    setupState();

    // m_upcomingState.position = m_passedState.position;
    utils::printVector("PS Pos", m_passedState.position);
    utils::printVector("US Pos", m_upcomingState.position);
    utils::printVector("GP Pos", getPosition());
    utils::printVector("PS Vel", m_passedState.velocity);
    utils::printVector("US Vel", m_upcomingState.velocity);
    utils::printVector("PS Acl", m_passedState.acceleration);
    utils::printVector("US Acl", m_upcomingState.acceleration);
    PRINT("=====================");

    // check collision

    // updating state
    m_upcomingState.acceleration = m_passedState.acceleration;
    m_upcomingState.velocity = m_passedState.velocity + m_upcomingState.acceleration * dt;
    m_upcomingState.position = m_passedState.position + m_upcomingState.velocity * dt;

    switch (m_Scene.GetOutsideLocation(m_upcomingState.position, getRadius()))
    {
    case engine::PointOutsideLocation::XPlus:
    case engine::PointOutsideLocation::XMinus:
        m_upcomingState.velocity.x = -m_upcomingState.velocity.x;
        break;
    case engine::PointOutsideLocation::YMinus:
    case engine::PointOutsideLocation::YPlus:
        m_upcomingState.velocity.y = -m_upcomingState.velocity.y;
        break;
    }

    applyState();

    // currently lags in low fps, position provided is correct
    // m_encodedPosition = m_Scene.GetBPE().getEncoded(getPosition());
}