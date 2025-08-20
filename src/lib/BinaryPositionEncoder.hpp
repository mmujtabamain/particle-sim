#pragma once

#include <SFML/Graphics.hpp>
#include <stdexcept>

#include "Scene.hpp"

#include "Helpers.hpp"
#include "RectArea.hpp"
#include "Vector2M.hpp"

#include "_macros.hpp"

namespace lib
{
    enum class Direction : bool
    {
        Vertical = true,
        Horizontal = false
    };

    // When Decoding what point of rect is given
    enum class DecodeType
    {
        TopLeft,
        BottomRight,
        Center
    };

    class BinaryPositionEncoder
    {
    public:
        /// @brief Used to initialize the encoder with a specific window size
        /// @param windowSize Takes in `const sf::Vector2u&` and x, y internally
        /// @param __scene (optional) DEBUG ONLY parameter; specifies what scene to draw the quadrant rects on.
        BinaryPositionEncoder(const sf::Vector2u &windowSize, engine::Scene *__scene = nullptr);

    public:
        BinaryPositionEncoder() = delete;

        /* @brief Encodes the position of a point on a screen to a seperate quadrants of the screen
        * in binary, can be used to determined how close objects are to each other.
        * 
        * Works by manipulating the bits of `uint16_t` (2 bytes). Following algorithm is used to fill bits from left to right:
        * 
        * - Set `searchRect` to (windowSize.x / 2, windowSize.y / 2)
        * 
        * - If point is left of searchRect.x (vertical line check); append 1 if true else 0
        * 
        * - Shrink searchRect in x direction
        * 
        * - If point is below of searchRect.y (horizontal line check); append 1 if true else 0
        * 
        * - Shrink searchRect in y direction
        * 
        * - Move searchRect to next quadrant and goto Step 2
        * 
        * - Repeat above step until all bits are fill
        * 
        * Leftmost bits are of bigger quadrants
        * while Rightmost bits are for close quadrants.
        * 
        * ---
        * 
        * Depends on the window size being constant; thus it is initalized by creating an instance of class `lib::BinaryPositionEncoder`.
        * @param point The point to encode
        * @return `uint16_t` with bits manipulated to resemble the address in binary.
        */
        uint16_t getEncoded(const lib::Vector2M &point);

        /// @brief ! Current not working correctly !
        /// @param addr the encoded bit address
        /// @return `lib::Vector2M` wirh x, y initalized to decoded values
        lib::Vector2M getDecoded(uint16_t addr);

    public:
        DecodeType decodeType = DecodeType::TopLeft;

        // DEBUG ONLY; will be removed by compiler automatically (i think)
        engine::Scene *__scene = nullptr;
        std::vector<lib::RectArea> __drawAreas;

    private:
        static constexpr size_t NUM_BITS = sizeof(uint16_t) * 8;

        unsigned int windowX, windowY;
    };

    // Add bits from right to left
    template <typename T>
    inline void appendBit(T &appendTo, uint8_t bit)
    {
        appendTo <<= 1; // move previous bits to left to preserve them
        // (bit & 1u) applies mask to get the last bit : 1u = rightmost bit = ... 00000001
        // |= adds the bit to "appendTo"
        appendTo |= (bit & 1u);
    }

    // Gets bit at specified indexFromLeft
    // (0 - 15) for uint16_t; sizeof(uint16_t) * 8 = 16
    template <typename T>
    inline bool getBit(const T &from, size_t indexFromLeft)
    {
        constexpr size_t NUM_BITS = sizeof(T) * 8;

        if (indexFromLeft >= NUM_BITS)
        {
            throw std::runtime_error("[engine::utils::getBit] indexFromLeft(" + std::to_string(indexFromLeft) + ") >= NUM_BITS(" + std::to_string(NUM_BITS) + ")\n");
        }

        // get index from right
        // NUM_BITS - 1 to allow iterating from 0 to (NUM_BITS - 1)
        size_t indexFromRight = (NUM_BITS - 1) - indexFromLeft;
        // move the bit to read at the right most position
        // i.e consider 00001000
        // to read one we bitshift right till 1 is at right most position i.e 00000001
        // then apply `bitwise and`; returns `0` when reading bit is 0 (0 AND 1) and returns `1` when reading bit is 1 (1 AND 1)
        return (from >> indexFromRight) & 1u;
    }

    // Sets bit at specified indexFromLeft
    // (0 - 15) for uint16_t; sizeof(uint16_t) * 8 = 16
    // bitValue true = 1 and false = 0
    template <typename T>
    inline void setBit(T &to, size_t indexFromLeft, bool bitValue)
    {
        constexpr size_t NUM_BITS = sizeof(T) * 8;

        if (indexFromLeft >= NUM_BITS)
        {
            throw std::runtime_error("[engine::utils::setBit] indexFromLeft(" + std::to_string(indexFromLeft) + ") >= NUM_BITS(" + std::to_string(NUM_BITS) + ")\n");
        }

        // get index from right
        // NUM_BITS - 1 to allow iterating from 0 to (NUM_BITS - 1)
        size_t indexFromRight = (NUM_BITS - 1) - indexFromLeft;
        // only use right most digit of bitValue
        if (bitValue)
            // T(1) instead of 1u to allows shifts greater than 255; incase uint32_t or greater is used as T
            to |= T(1) << indexFromRight; // add one to `to` at selected index
        else
            // take ... 00000001 and shift to right till required index is reached
            // when reached invert it so in mask everywhere else is `1` except at index
            // then apply and between every value of `to` and the mask
            // the value at index will be x & 0 = 0 (always); rest will be same since 0 & 1 = 0, 1 & 1 = 1
            // at index & 0 is performed but everywhere else & 1 is performed
            to &= ~(T(1) << indexFromRight);
    }
}