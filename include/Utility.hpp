#pragma once

#include <cmath>
#include <limits>
#include <random>
#include <memory>

inline const double infinity = std::numeric_limits<double>::infinity();
inline const double pi = 3.1415926535897932385;

inline double degreesToRadians(double degrees)
{
    return degrees * pi / 180.0;
}

inline double random_double() {
    static std::uniform_real_distribution<double> distribution(0.0, 1.0);
    static std::mt19937 generator;
    return distribution(generator);
}

inline double random_double(double min, double max) {
    static std::uniform_real_distribution<double> distribution(min, max);
    static std::mt19937 generator;
    return distribution(generator);
}