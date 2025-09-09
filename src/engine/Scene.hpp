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

    enum class PointOutsideLocation : int
    {
        Inside = 0,
        XPlus = 1,
        XMinus = 2,
        YPlus = 3,
        YMinus = 4
    };

    class Scene : public IScene
    {
    private:
        sf::RenderWindow m_window;
        std::vector<engine::Object> m_objects;
        const lib::BinaryPositionEncoder m_encoder;
        sf::Font __debugFont;

    public:
        Scene() = delete;
        Scene(const sf::Vector2u &size);

        void StartLoop();
        void AddObject(const engine::Object &obj);

        void ObjectsForEach(const std::function<void(engine::Object &)> &func);

        sf::RenderWindow &GetWindow() override;
        PointOutsideLocation GetOutsideLocation(const lib::Vector2M &p, int padding) const override;

        const lib::BinaryPositionEncoder &GetBPE() override;

        std::vector<std::unique_ptr<sf::Drawable>> __m_debugDrawables;
        void __AddDebugDrawables(std::unique_ptr<sf::Drawable> item) override;
    };
}