#ifndef UTILS_H
#define UTILS_H

#include <math.h>
#include <SFML/Graphics.hpp>

namespace utils {
    int distance(const int &x1, const int &y1, const int &x2, const int &y2);
    sf::Vector2f midpoint(const int &x1, const int &y1, const int &x2, const int &y2);
    int man_distance(const int &x1, const int &y1, const int &x2, const int &y2);
}

#endif
