#include "BinaryPositionEncoder.hpp"

lib::BinaryPositionEncoder::BinaryPositionEncoder(const sf::Vector2u &windowSize, engine::IScene *__scene)
    : windowX(windowSize.x), windowY(windowSize.y), __scene(__scene)
{
}

uint16_t lib::BinaryPositionEncoder::getEncoded(const lib::Vector2M &point) const
{
    // optimized away by compiler
    enum class Direction : bool
    {
        Vertical = true,
        Horizontal = false
    };

    uint16_t result;

    // first check vertical direction; first bit is vertical
    Direction nextDir(Direction::Vertical);

    lib::RectArea searchRect;
    searchRect.size = lib::Vector2M(
        windowX / 2,
        windowY / 2 //
    );

    // create info for each bit
    for (size_t i = 0; i < NUM_BITS; i++)
    {
        switch (nextDir)
        {
        case Direction::Vertical:
        {
            // point is left of line dividing the rect in half parallel to y axis
            if (point.x > searchRect.position.x + searchRect.size.x)
            {
                appendBit(result, 1);
                // reducing search size (1) : move left
                searchRect.position.x += searchRect.size.x;
            }
            else
            {
                appendBit(result, 0);
            }

            // reducing search size (2) : shrink horizontal size
            searchRect.size.x /= 2;
            nextDir = Direction::Horizontal; // switch dir
            break;
        }
        case Direction::Horizontal:
        {
            // point is below the line diving the rect in half parallel to x axis
            if (point.y > searchRect.position.y + searchRect.size.y)
            {
                appendBit(result, 1);
                // reducing search size (1) : move down
                searchRect.position.y += searchRect.size.y;
            }
            else
            {
                appendBit(result, 0);
            }

            // reducing search size (2) : shrink vertical size
            searchRect.size.y /= 2;
            nextDir = Direction::Vertical; // switch dir
            break;
        }
        };

        // DEBUG ONLY; will be removed by compiler automatically (i think)

        // construct on the heap will be deleted after drawn by the scene
        std::unique_ptr<sf::RectangleShape> __drawRect = std::make_unique<sf::RectangleShape>();
        __drawRect->setFillColor(sf::Color::Transparent);
        __drawRect->setOutlineColor(sf::Color::Magenta);
        __drawRect->setOutlineThickness(-1);

        __drawRect->setPosition(searchRect.position);
        // size * 2 (works but idk why completely)
        __drawRect->setSize(searchRect.size * 2);

        if (__scene)
            __scene->__addDebugDrawables(std::move(__drawRect));
            // using std::move because copy constructor of unique_ptr is deleted
            // without std::move item is passed in by value we want to just move it
    }

    return result;
}

lib::Vector2M lib::BinaryPositionEncoder::getDecoded(uint16_t addr)
{
    lib::RectArea searchRect;
    searchRect.size = {
        windowX + 0.f,
        windowY + 0.f //
    };

    for (size_t i = 0; i < NUM_BITS; i++)
    {
        bool bit = getBit(addr, i);
        // 0th, 2nd, 4th ... bits represent vertical side
        bool isVerticalBit = i % 2;

        // bit is `1`, so point to to the left side
        if (bit)
        {
            if (isVerticalBit)
            {
                // vertical bit refers to bit that is used to encode wheather the bit is left or right of the line
                searchRect.position.x += searchRect.size.x;
            }
            else
            {
                // horizontal bit refers to bit that is used to encode wheather the bit is above or below the line
                searchRect.position.y += searchRect.size.y;
            }
        }
        else
        {
            // position remains same
        }

        // size is shrunk regardless
        if (isVerticalBit)
        {
            searchRect.size.x /= 2;
        }
        else
        {
            searchRect.size.y /= 2;
        }
    }

    switch (decodeType)
    {
    case DecodeType::TopLeft:
    {
        // top-left corner
        return searchRect.position;
        break;
    }
    case DecodeType::BottomRight:
    {
        // bottom-right corner
        return searchRect.position + searchRect.size;
        break;
    }
    case DecodeType::Center:
    {
        // :: since we want utils from global namespace
        return ::utils::midpoint(searchRect.position, searchRect.position + searchRect.size);
        break;
    }
    };
}
