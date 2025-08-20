#pragma once

#include <SFML/Graphics.hpp>

namespace lib
{
    ///  @brief A minimized version of `sf::Vector2<T>` containing only x, y floats along with a constructor from `sf::Vector2<T>` to `lib::Vector2M`.
    /// Only to be used when only x, y values are required
    ///
    /// ---
    ///
    /// Conversion operators:
    ///
    /// - to `sf::Vector2<T>`
    ///
    struct Vector2M
    {
        float x, y;

        Vector2M(float x = 0, float y = 0) : x(x), y(y) {}

        template <typename T>
        Vector2M(const sf::Vector2<T> &v) : x(static_cast<float>(v.x)), y(static_cast<float>(v.y)) {}

        // decleration of Vector2M::zero
        static const Vector2M zero;

        /// @brief Custom converstion to `sf::Vector2<T>`
        /// @tparam T type of `sf::Vector2<T>`
        template <typename T>
        inline operator sf::Vector2<T>() const { return sf::Vector2<T>(x, y); }

        inline Vector2M operator+(const Vector2M &other)
        {
            return Vector2M(
                x + other.x,
                y + other.y //
            );
        }

        inline Vector2M &operator*=(float s)
        {
            // & is reference to current object
            x *= s;
            y *= s;
            // returns reference after updating values
            return *this;
        }

        inline Vector2M operator*(float s) const
        {
            return Vector2M(
                x * s,
                y * s //
            );
        }
    };

    /// @brief Vector2M initialized to zero can be accessed with `lib::zeroVector2M`
    inline const Vector2M Vector2M::zero = Vector2M(0, 0);
}