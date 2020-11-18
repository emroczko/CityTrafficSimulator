#pragma once
#include <vector>
#include "Cell.h"

namespace ZPR {
	class Grid
	{
	public:
		Grid(std::vector<Cell> cells, int size);
		Cell& GetCell(int row, int column);
	private:
		std::vector<Cell> _cells;
		int _size;
	};
}

