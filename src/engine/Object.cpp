#include "Object.hpp"

#include "Scene.hpp"

engine::Object::Object(engine::IScene &scene, float radius)
    : shape(radius), myScene(scene), windowRO(scene.getWindow())
{
    shape.setFillColor(sf::Color(0, 100, 0, 100));
    shape.setPosition({100, 100});
    shape.setOrigin({0.5f, 0.5f});
    shape.setOutlineThickness(4);
    shape.setOutlineColor(sf::Color::Black);

    currentFrameState.velocity = {0, 0};
    currentFrameState.acceleration = {0, 1000};
    currentFrameState.position = shape.getPosition();
}

sf::Vector2f engine::Object::getCenter() const
{
    return shape.getPosition() + shape.getRadius();
}

const sf::Vector2f &engine::Object::getVelocity() const
{
    return currentFrameState.velocity;
}

float engine::Object::getRadius() const
{
    return shape.getRadius();
}

void engine::Object::setPosition(const sf::Vector2f &newPos)
{
    shape.setPosition(newPos);
}

void engine::Object::setVelocity(const sf::Vector2f &newVel)
{
    currentFrameState.velocity = newVel;
}

void engine::Object::draw(sf::RenderWindow &window)
{
    window.draw(shape);

    utils::drawVector(currentFrameState.velocity, getCenter(), window);
    // utils::drawVector(currentFrameState.acceleration, getPosition(), window);
}

void engine::Object::update(float dt)
{
    physicsLoop(dt);
}

sf::Vector2f lerp(const sf::Vector2f &a, const sf::Vector2f &b, float t)
{
    return {
        (1 - t) * a.x + t * b.x,
        (1 - t) * a.y + t * b.y //
    };
}

// continous collision detection by using crude and lackluster implementation of verlet integration
void engine::Object::physicsLoop(float dt)
{
    sf::Vector2f posP = currentFrameState.position;
    sf::Vector2f velP = currentFrameState.velocity;

    sf::Vector2f velN = velP + dt * currentFrameState.acceleration;
    sf::Vector2f posN = posP + dt * velN;

    utils::printVector("posN", posN);
    utils::printVector("velN", velN);

    utils::drawPoint(utils::translatePointInDirection(getCenter(), {0, 1}, dt * velN.length()), windowRO);

    // boundaries (only floor for now)
    // check if nextPos is outside boundaries
    if (myScene.isPointOutsideWindow(utils::translatePointInDirection(getCenter(), {0, 1}, dt * velN.length())))
    {
        PRINT("abc");
        sf::Vector2f collisionPoint;
        float collisionTime;

        // find collision time
        collisionTime = (windowRO.getSize().y + shape.getRadius() - posN.y) / (posP.y - posN.y);

        // lerp currentPos and nextPos to find collision point
        collisionPoint = lerp(posP, posN, collisionTime);

        // resolve collision
        collisionPoint.y = windowRO.getSize().y - collisionPoint.y;
        // posN.y = collisionPoint.y;
        velN.y = -velN.y;
    }

    // update position
    setPosition(posN);

    // update prev state for next iteration (currentFrame now = prevFrame in next iteration)
    currentFrameState.position = shape.getPosition();
    currentFrameState.velocity = velN;
}