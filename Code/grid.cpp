/**
 * grid.cpp
 * Implementation of Grid struct.
 */

#include "grid.hpp"

namespace zpr {

    /**
     * Parametrized constructor of Grid struct.
     * @param cells - Vector of cells from which grid will be built.
     * @param size - Size of grid.
     */
	Grid::Grid(std::vector<Cell> cells, int size): cells_(cells), size_(size) {}
	
    /**
     * Parametrized constructor of Grid struct.
     * @param cells - Vector of cells from which grid will be built.
     * @param width - Width of the grid.
     * @param height - Height of the grid.
     */
    Grid::Grid(std::vector<Cell> cells, int width, int height): cells_(cells), height_(height), width_(width) {}
    
    /**
     * Method returning reference to cell at certain position represented by row and column.
     * @param row - Row where the cell is at.
     * @param column - Column where the cell is at.
     */
	Cell& Grid::getCell(int row, int column)
	{
		return this->cells_.at(row * size_ + column);
	}
}
