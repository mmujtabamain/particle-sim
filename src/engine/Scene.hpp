#pragma once
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include <vector>
#include <functional>
#include <deque>

#include "IScene.hpp"
#include "BinaryPositionEncoder.hpp"
#include "Object.hpp"
#include "Timer.hpp"

#include "_macros.hpp"

namespace engine
{
    // public IScene implies Scene = IScene
    // allows other classes to refer to Scene as IScene instead of Scene

    class Scene : public IScene
    {
    private:
        sf::RenderWindow m_window;
        std::vector<engine::Object> m_objects;
        sf::Font debugFont;
        const lib::BinaryPositionEncoder m_encoder;

    public:
        Scene() = delete;
        Scene(const sf::Vector2u &size);

        void startLoop();
        void addObject(const engine::Object &obj);

        void objectsForEach(const std::function<void(engine::Object &)> &func);

        sf::RenderWindow &getWindow() override;
        bool isPointOutsideWindow(const lib::Vector2M &p) const override;

        const lib::BinaryPositionEncoder &getBPE() override;

        std::vector<std::unique_ptr<sf::Drawable>> __debugDrawables;
        void __addDebugDrawables(std::unique_ptr<sf::Drawable> item) override;
    };
}