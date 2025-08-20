#pragma once

#include <iostream>
#include <chrono>
#include <functional>

#include "Helpers.hpp"

namespace utils
{
    class Timer
    {
    public:
        enum class Unit
        {
            Auto,
            Second,
            Millisecond,
            Microsecond,
            Nanosecond
        };

    private:
        std::chrono::time_point<std::chrono::high_resolution_clock> startTime;
        std::chrono::time_point<std::chrono::high_resolution_clock> endTime;

        std::string name;
        Unit unit;

        static constexpr const char *unitMaps[] = {
            "auto", "s", "ms", "us", "ns" //
        };

    public:
        Timer() = delete;
        Timer(const std::string &name, Unit unit = Unit::Auto);
        ~Timer();

        inline const char *unitAsString(Unit u)
        {
            return unitMaps[static_cast<int>(u)];
        }

        template <typename Rep, typename Period>
        Unit getSuitableUnit(std::chrono::duration<Rep, Period> time, long long *outTime)
        {
            // greater than second
            if (time.count() >= 1'000'000'000) // 1'000'000'000 ns in 1 s
            {
                *outTime = std::chrono::duration_cast<std::chrono::seconds>(time).count();
                return Unit::Second;
            }
            // greater than millisecond
            else if (time.count() >= 1'000'000) // 1'000'000 ns in 1 ms
            {
                *outTime = std::chrono::duration_cast<std::chrono::milliseconds>(time).count();
                return Unit::Millisecond;
            }
            // greater than microsecond
            else if (time.count() >= 1'000) // 1'000 ns in 1 us
            {
                *outTime = std::chrono::duration_cast<std::chrono::microseconds>(time).count();
                return Unit::Microsecond;
            }
            else
            {
                *outTime = std::chrono::duration_cast<std::chrono::nanoseconds>(time).count();
                return Unit::Nanosecond;
            }
        }
    };
}