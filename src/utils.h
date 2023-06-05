#ifndef UTILS_H
#define UTILS_H

#include <math.h>
#include <SFML/Graphics.hpp>

namespace utils {
    int distance(const int &x1, const int &y1, const int &x2, const int &y2) {
        return sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
    }

    sf::Vector2f midpoint(const int &x1, const int &y1, const int &x2, const int &y2) {
        return sf::Vector2f((x1+x2)/2, (y1+y2)/2); 
    }

    int man_distance(const int &x1, const int &y1, const int &x2, const int &y2) {
        return (x2 - x1) + abs(y2 - y1);
    }
}

#endif
