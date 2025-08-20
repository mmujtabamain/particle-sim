#include "Scene.hpp"

#include "BinaryPositionEncoder.hpp"

engine::Scene::Scene(const sf::Vector2u &size)
    : debugFont("assets/cascadia_code.ttf")
{
    sf::ContextSettings settings;
    settings.antiAliasingLevel = 16;

    window = sf::RenderWindow(sf::VideoMode(size), "Particle Simulation", sf::Style::Close, sf::State::Windowed, settings);
    objects.reserve(128);

    window.setFramerateLimit(60);
    // window.setVerticalSyncEnabled(true);
}

void engine::Scene::startLoop()
{
    sf::Clock deltaClock;
    sf::Clock __fpsClock;

    sf::Text __fpsText(debugFont);
    __fpsText.setPosition({15, 10});
    __fpsText.setCharacterSize(20);
    __fpsText.setFillColor(sf::Color::White);

    std::deque<float> __frameTimes;
    const size_t __FRAMES_SAMPLES = 60;

    while (window.isOpen())
    {
        __fpsClock.start();

        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
        }

        window.clear();

        float dt = deltaClock.restart().asSeconds();

        // FPS
        if (__fpsClock.getElapsedTime().asSeconds() > 0.1f)
        {
            __frameTimes.push_back(dt);

            if (__frameTimes.size() > __FRAMES_SAMPLES)
                __frameTimes.pop_front();

            float __avgTime = 0;
            for (float t : __frameTimes)
                __avgTime += t;
            __avgTime = __avgTime / __frameTimes.size(); // storing avg in same var as sum

            // clang-format off
            __fpsText.setString("<FPS>: " + std::to_string(static_cast<int>(1.f / __avgTime))
                       + "\n" + " FPS : " + std::to_string(static_cast<int>(1.f / dt))
            );
            // clang-format on

            __fpsClock.reset();
        }
        // FPS END

        sf::Vector2i mousePos = sf::Mouse::getPosition(window);

        // return is outside window
        if (mousePos.x > 0 && mousePos.x < window.getSize().x && mousePos.y > 0 && mousePos.y < window.getSize().y)
        {
            lib::BinaryPositionEncoder encoder(window.getSize(), this);

            std::cout << "Encoder: " << std::bitset<16>(encoder.getEncoded(mousePos)) << "\n";
        }

        for (auto &obj : objects)
        {
            obj.update(dt);
            obj.draw(window);
        }

#if DEBUG == 1
        for (auto &__drawable : __debugDrawables)
        {
            window.draw(*__drawable);
        }

        __debugDrawables.clear();

        window.draw(__fpsText);
#endif // DEBUG

        window.display();
    }
}

void appendBit(uint16_t &value, uint8_t bit)
{
    value <<= 1; // preserve previous values
    // (bit & 1) mask last bit && |= adds bit
    value |= (bit & 1);
}

void engine::Scene::addObject(const engine::Object &obj)
{
    objects.push_back(obj);
}

void engine::Scene::objectsForEach(const std::function<void(engine::Object &)> &func)
{
    for (auto &obj : objects)
    {
        func(obj);
    }
}

sf::RenderWindow &engine::Scene::getWindow()
{
    return window;
}

bool engine::Scene::isPointOutsideWindow(const lib::Vector2M &p) const
{
    if (p.x < 0)
    {
        return true;
    }
    else if (p.y < 0)
    {
        return true;
    }
    else if (p.x > window.getSize().x)
    {
        return true;
    }
    else if (p.y > window.getSize().y)
    {
        return true;
    }

    return false;
}