#include "Grid.h"

namespace ZPR {

	Grid::Grid(std::vector<Cell> cells, int size): _cells(cells), _size(size) {}

	ZPR::Cell& Grid::GetCell(int row, int column)
	{
		return this->_cells.at(row * _size + column);
	}
}
