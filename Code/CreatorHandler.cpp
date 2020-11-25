#include "CreatorHandler.h"

namespace ZPR {
	CreatorHandler::CreatorHandler(int gridSize): _gridSize(gridSize), _row(-1), _col(-1) {}

	void CreatorHandler::init()
	{
		this->GenerateBoard();
		this->NotifyCells(_grid->_cells);
	}

	void CreatorHandler::GenerateBoard()
	{
		std::vector<Cell> cells;
		for (int i = 0; i < this->_gridSize * this->_gridSize; i++)
		{
			cells.push_back(Cell(i / _gridSize, i % _gridSize));
		}
        this->_grid = std::make_unique<Grid>(cells, _gridSize);
	}

	void CreatorHandler::HandleInput(sf::Vector2i possibleSelectedCell)
	{
		if (possibleSelectedCell.x == -1 || possibleSelectedCell.y ==-1) { return; }
		this->_row = possibleSelectedCell.x;
		this->_col = possibleSelectedCell.y;
		this->NotifySelectedCell(sf::Vector2i(this->_row, this->_col));
	}
}
