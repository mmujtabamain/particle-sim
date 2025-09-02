#pragma once
#include <iostream>
#include <string>
#include <random>
#include <chrono>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

#include "RectArea.hpp"

namespace utils
{
    inline void printMessage(const std::string &message)
    {
        std::cout << message << "\n";
    }

    template <typename T>
    inline void printVector(const std::string &name, const sf::Vector2<T> &vector)
    {
        std::cout << name << ": " << vector.x << ", " << vector.y << "\n";
    }

    inline float getRandom(float minInclusive, float maxInclusize, float seed)
    {
        static std::mt19937 engine(seed);
        std::uniform_real_distribution<float> dist(minInclusive, maxInclusize);
        return dist(engine);
    }

    inline float getRandom(float minInclusive, float maxInclusize)
    {
        return getRandom(minInclusive, maxInclusize, std::random_device{}());
    }

    inline float getRandom01(float seed)
    {
        static std::mt19937 engine(seed);
        static std::uniform_real_distribution<float> dist(0, 1);
        return dist(engine);
    }

    inline float getRandom01()
    {
        return getRandom01(std::random_device{}());
    }

    inline sf::Vector2f getRandomVector(float magnitude)
    {
        return {getRandom(-1, 1) * magnitude, getRandom(-1, 1) * magnitude};
    }

    inline sf::Vector2f getRandomVector(float magnitude, float seed)
    {
        return {getRandom(-1, 1, seed) * magnitude, getRandom(-1, 1, seed) * magnitude};
    }

    inline sf::Vector2f translatePointInDirection(const sf::Vector2f &p, const sf::Vector2f &dir, float dist)
    {
        return p + dir.normalized() * dist;
    }

    inline sf::Vector2f midpoint(const sf::Vector2f &a, const sf::Vector2f &b)
    {
        return {
            (a.x + b.x) / 2,
            (a.y + b.y) / 2 //
        };
    }

    template <typename T>
    inline void drawPoint(const sf::Vector2<T> &p, sf::RenderWindow &win, float radius = 5.f)
    {
        sf::CircleShape shape(radius);

        shape.setFillColor(sf::Color::Yellow);
        shape.setPosition({
            p.x - radius,
            p.y - radius //
        });

        win.draw(shape);
    }

    template <typename T>
    inline sf::VertexArray drawLine(const sf::Vector2<T> &start, const sf::Vector2<T> &end)
    {
        sf::VertexArray line(sf::PrimitiveType::Lines, 2);
        line[0].color = sf::Color::Magenta;
        line[1].color = sf::Color::Magenta;

        line[0].position = start;
        line[1].position = end;

        return line;
    }

    inline sf::VertexArray drawLine(float distance, bool vertical, const sf::FloatRect &enclosingWindow, const sf::Color &color = sf::Color::Magenta)
    {
        sf::VertexArray line(sf::PrimitiveType::Lines, 2);
        line[0].color = color;
        line[1].color = color;

        if (vertical)
        {
            line[0].position = {
                enclosingWindow.position.x + distance,
                enclosingWindow.position.y //
            };
            line[1].position = {
                enclosingWindow.position.x + enclosingWindow.size.x - distance,
                enclosingWindow.position.y + enclosingWindow.size.y + 0.f //
            };
        }
        else
        {
            line[0].position = {
                enclosingWindow.position.x,
                enclosingWindow.position.y + distance //
            };
            line[1].position = {
                enclosingWindow.position.x + enclosingWindow.size.x + 0.f,
                enclosingWindow.position.y + enclosingWindow.size.y - distance //
            };
        }

        return line;
    }

    inline void drawRect(lib::RectArea r, sf::RenderWindow &win)
    {
        sf::RectangleShape rect;
        rect.setFillColor(sf::Color::Transparent);
        rect.setOutlineColor(sf::Color::Magenta);
        rect.setOutlineThickness(-1);

        rect.setPosition(r.position);
        rect.setSize(r.size);

        win.draw(rect);
    }

    template <typename T>
    inline void drawRect(const sf::Rect<T> &r, sf::RenderWindow &win)
    {
        sf::RectangleShape rect;
        rect.setFillColor(sf::Color::Transparent);
        rect.setOutlineColor(sf::Color::Magenta);
        rect.setOutlineThickness(-1);

        rect.setPosition(r.position);
        rect.setSize(r.size);

        win.draw(rect);
    }

    template <typename T>
    inline void drawVector(const sf::Vector2<T> &v, const sf::Vector2f &pos, sf::RenderWindow &win)
    {
        const int width = 5;
        const float scale = 10; // 100 units of length = 1 unit of rect length

        sf::RectangleShape line;

        line.setFillColor(sf::Color::Magenta);

        line.setPosition(pos);
        line.setOrigin({width / 2.f, 0});
        line.setSize({width, v.length() / scale});
        line.setRotation(sf::radians(std::atan2f(v.y, v.x) - M_PI_2)); // M_PI_2 = pi/2

        sf::VertexArray arrow(sf::PrimitiveType::Triangles, 3);

        arrow[0].color = sf::Color::Magenta;
        arrow[1].color = sf::Color::Magenta;
        arrow[2].color = sf::Color::Magenta;

        arrow[0].position = line.getTransform().transformPoint({
            (width / 2.f) - width,
            v.length() / scale //
        });
        arrow[1].position = line.getTransform().transformPoint({
            (width / 2.f) + width,
            v.length() / scale //
        });
        arrow[2].position = line.getTransform().transformPoint({
            width / 2.f,
            (v.length() / scale) + width //
        });

        win.draw(line);
        win.draw(arrow);
    }
}

namespace sf
{
    // SCALER
    // add Vector2f
    inline sf::Vector2f operator+(const sf::Vector2f &v, float s)
    {
        return {v.x + s, v.y + s};
    }

    // subtract Vector2f
    inline sf::Vector2f operator-(const sf::Vector2f &v, float s)
    {
        return {v.x + s, v.y + s};
    }

    // add Vector2u
    inline sf::Vector2u operator+(const sf::Vector2u &v, unsigned int s)
    {
        return {v.x + s, v.y + s};
    }

    // subtract Vector2u
    inline sf::Vector2u operator-(const sf::Vector2u &v, unsigned int s)
    {
        return {v.x + s, v.y + s};
    }
}

#define PRINT(message) utils::printMessage(message)