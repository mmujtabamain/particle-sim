#include "Timer.hpp"

utils::Timer::Timer(const std::string &name, Unit unit) : name(name), unit(unit)
{
    startTime = std::chrono::high_resolution_clock::now();
}

utils::Timer::~Timer()
{
    endTime = std::chrono::high_resolution_clock::now();

    long long elapsed;
    const char *unitSymbol = "";

    switch (unit)
    {
    case Unit::Second:
    {
        auto time = std::chrono::duration_cast<std::chrono::seconds>(endTime - startTime);
        elapsed = time.count();
        unitSymbol = "s";
        break;
    }
    case Unit::Millisecond:
    {
        auto time = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime);
        elapsed = time.count();
        unitSymbol = "ms";

        break;
    }
    case Unit::Microsecond:
    {
        auto time = std::chrono::duration_cast<std::chrono::microseconds>(endTime - startTime);
        elapsed = time.count();
        unitSymbol = "us";

        break;
    }
    case Unit::Nanosecond:
    {
        auto time = std::chrono::duration_cast<std::chrono::nanoseconds>(endTime - startTime);
        elapsed = time.count();
        unitSymbol = "ns";

        break;
    }

    case Unit::Auto:
    default:
    {
        unitSymbol = unitAsString(getSuitableUnit(endTime - startTime, &elapsed));

        break;
    }
    }

    PRINT(name + ": " + std::to_string(elapsed) + " " + unitSymbol);
}
