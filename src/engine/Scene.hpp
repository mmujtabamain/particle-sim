#pragma once
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include <vector>
#include <functional>
#include <deque>

#include "IScene.hpp"

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
        sf::RenderWindow window;

        std::vector<engine::Object> objects;

        sf::Font debugFont;
        int lastIndex;

    public:
        Scene() = delete;
        Scene(const sf::Vector2u &size);

        void startLoop();
        void addObject(const engine::Object &obj);

        void objectsForEach(const std::function<void(engine::Object &)> &func);

        sf::RenderWindow &getWindow() override;
        bool isPointOutsideWindow(const lib::Vector2M &p) const override;

        std::vector<std::unique_ptr<sf::Drawable>> __debugDrawables;
    };
}