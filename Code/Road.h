#pragma once
#include <SFML/Graphics.hpp>

namespace ZPR {
    class Road
    {
    public:
        Road(int row, int column);
        Road();
        sf::Vector2i GetPosition();
        bool _north, _south, _east, _west;
    private:
        int _row, _column;
        sf::RectangleShape _road;
    };
}

