#include "Scene.hpp"

#include "BinaryPositionEncoder.hpp"

engine::Scene::Scene(const sf::Vector2u &size)
    : debugFont("assets/cascadia_code.ttf"), m_encoder(size, this)
{
    sf::ContextSettings settings;
    settings.antiAliasingLevel = 16;

    m_window = sf::RenderWindow(sf::VideoMode(size), "Particle Simulation", sf::Style::Close, sf::State::Windowed, settings);
    m_objects.reserve(128);

    // m_window.setFramerateLimit(60);
    // m_window.setVerticalSyncEnabled(true);
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

    while (m_window.isOpen())
    {
        __fpsClock.start();

        while (const std::optional event = m_window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                m_window.close();
        }

        m_window.clear();

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

        sf::Vector2i mousePos = sf::Mouse::getPosition(m_window);

        // return is outside window
        if (mousePos.x > 0 && mousePos.x < m_window.getSize().x && mousePos.y > 0 && mousePos.y < m_window.getSize().y)
        {
            lib::BinaryPositionEncoder encoder(m_window.getSize(), this);

            std::cout << "Mouse Pos Encoded: " << std::bitset<16>(encoder.getEncoded(mousePos)) << "\n";
        }

#if DEBUG == 1
        for (auto &__drawable : __debugDrawables)
        {
            m_window.draw(*__drawable);
        }

        __debugDrawables.clear();

#endif // DEBUG
        m_window.draw(__fpsText);

        for (auto &obj : m_objects)
        {
            obj.update(dt);
            obj.draw(m_window);
        }

        m_window.display();
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
    m_objects.push_back(obj);
}

void engine::Scene::objectsForEach(const std::function<void(engine::Object &)> &func)
{
    for (auto &obj : m_objects)
    {
        func(obj);
    }
}

sf::RenderWindow &engine::Scene::getWindow()
{
    return m_window;
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
    else if (p.x > m_window.getSize().x)
    {
        return true;
    }
    else if (p.y > m_window.getSize().y)
    {
        return true;
    }

    return false;
}

const lib::BinaryPositionEncoder &engine::Scene::getBPE()
{
    return m_encoder;
}

void engine::Scene::__addDebugDrawables(std::unique_ptr<sf::Drawable> item)
{
    // using std::move because copy constructor of unique_ptr is deleted
    // without std::move item is passed in by value we want to just move it
    __debugDrawables.push_back(std::move(item));
}
