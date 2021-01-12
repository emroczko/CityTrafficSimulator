/**
 * grid.hpp
 * Header for Grid structure.
 */

#pragma once
#include <vector>
#include "cell.hpp"

namespace zpr {

    /**
     * Struct responsible for grid used in the application (mapView).
     */
	struct Grid
	{
        Grid(std::vector<Cell> cells, int width, int height);
		Grid(std::vector<Cell> cells, int size);
		Cell& getCell(int row, int column);
		std::vector<Cell> cells_;
        int size_, height_, width_;
        ~Grid() {};
	};
}

