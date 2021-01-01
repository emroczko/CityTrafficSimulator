#include "Grid.h"

namespace ZPR {

	Grid::Grid(std::vector<Cell> cells, int size): _cells(cells), _size(size) {}

    Grid::Grid(std::vector<Cell> cells, int width, int height): _cells(cells), _height(height), _width(width) {}

	ZPR::Cell& Grid::GetCell(int row, int column)
	{
		return this->_cells.at(row * _size + column);
	}
}
