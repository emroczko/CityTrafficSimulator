#include "CreatorHandler.h"

namespace ZPR {
	CreatorHandler::CreatorHandler(int gridSize): _gridSize(gridSize), _row(-1), _col(-1), isDrawingRoad(false) {}

	void CreatorHandler::init()
	{
		this->GenerateBoard();
		this->NotifyCells(_grid->_cells);
		this->NotifyIsDrawingRoad(this->isDrawingRoad);
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

	void CreatorHandler::UpdateIsDrawingRoad()
	{
		this->isDrawingRoad = !this->isDrawingRoad;
		this->NotifyIsDrawingRoad(this->isDrawingRoad);
	}

	void CreatorHandler::HandleInput(sf::Vector2i possibleSelectedCell)
	{
		if (possibleSelectedCell.x == -1 || possibleSelectedCell.y ==-1) { return; }
		else if (possibleSelectedCell.x > this->_gridSize-1 || possibleSelectedCell.y > this->_gridSize-1) { return; }
		this->_row = possibleSelectedCell.x;
		this->_col = possibleSelectedCell.y;
		if (isDrawingRoad) {
			this->_grid->GetCell(_row, _col)._containsRoad = true;
		}
		this->NotifyCells(_grid->_cells);
		this->NotifySelectedCell(sf::Vector2i(this->_row, this->_col));
	}

}
