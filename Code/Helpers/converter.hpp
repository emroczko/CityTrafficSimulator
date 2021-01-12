/**
 * converter.hpp
 * Header of Converter class.
 */
#pragma once
#include "SFML/Graphics.hpp"
#include "../definitions.hpp"
#include "../Components/cell.hpp"

namespace zpr{

    /**
     * Class responsible for helping transforming values.
     */
    class Converter{
    public:
        Converter(int grid_size);
        sf::Vector2f transformRowColToPixels(sf::Vector2i rowcol);
        int transformPixelsToRowCol(double pixels);
        int calculatePrefix();
        int getCellSize();
        sf::RectangleShape convertCellToCenteredRectShape(Cell cell, std::string whichRoad);
    private:
        int cellSize_;
        int gridSize_;
    };
}
