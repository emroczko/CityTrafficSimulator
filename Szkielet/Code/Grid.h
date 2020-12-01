#pragma once
#include <vector>
#include "Cell.h"

namespace ZPR {
	struct Grid
	{
		Grid(std::vector<Cell> cells, int size);
		Cell& GetCell(int row, int column);
		std::vector<Cell> _cells;
		int _size;
	};
}

