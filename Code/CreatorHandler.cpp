#include "CreatorHandler.h"

namespace ZPR {
	CreatorHandler::CreatorHandler(int gridSize): _gridSize(gridSize), _row(-1), _col(-1), isDrawingRoad(false), isDeletingRoad(false) {}

	void CreatorHandler::init()
	{
		this->GenerateBoard();
		this->NotifyCells(_grid->_cells);
		this->NotifyIsDrawingRoad(this->isDrawingRoad);
        this->NotifyIsDeletingRoad(this->isDeletingRoad);
	}
	/*Generuje siatk� zawierajac� kom�rki o wybranej wielko�ci*/
	void CreatorHandler::GenerateBoard()
	{
		std::vector<Cell> cells;
		for (int i = 0; i < this->_gridSize * this->_gridSize; i++)
		{
			cells.push_back(Cell(i / _gridSize, i % _gridSize));
		}
		//AddCellsRef(&cells);																					//*****
        this->_grid = std::make_unique<Grid>(cells, _gridSize);
	}

	/*Dodaje kom�rkom wska�niki do s�siaduj�cych kom�rek														*****
	void CreatorHandler::AddCellsRef(std::vector<Cell>* cells)
	{
		for (int i = 0; i < cells->size(); i++) {
			if (i / _gridSize != 0) {
				cells->at(i).north = std::make_unique<Cell>(cells->at(i - _gridSize));
				cells->at(i).north;
			}
			if (i / _gridSize != _gridSize - 1) {
				cells->at(i).south = std::make_unique<Cell>(cells->at(i + _gridSize));
				cells->at(i).south;
			}
			if (i%_gridSize != 0) {
				cells->at(i).west = std::make_unique<Cell>(cells->at(i - 1));
				cells->at(i).west;
			}
			if (i%_gridSize != _gridSize -1) {
				cells->at(i).east = std::make_unique<Cell>(cells->at(i + 1));
				cells->at(i).east;
			}
		}
	}*/

	/*Ustawia tryb rysowania drogi na w��czony lub wy��czony*/
	void CreatorHandler::UpdateIsDrawingRoad()
	{
        this->isDrawingRoad = !this->isDrawingRoad;
        this->isDeletingRoad = false;
		this->NotifyIsDrawingRoad(this->isDrawingRoad);
	}
	/*Ustawia tryb usuwania drogi na w��czony lub wy��czony*/
    void CreatorHandler::UpdateIsDeletingRoad()
    {
        this->isDeletingRoad = !this->isDeletingRoad;
        this->isDrawingRoad = false;
        this->NotifyIsDeletingRoad(this->isDeletingRoad);
    }
    void CreatorHandler::UpdateIsSimulating(bool isSimulating)
    {
        this->isDeletingRoad = false;
        this->isDrawingRoad = false;
    }

	/*Zajmuje sie obs�ug� zdarze� (zmiana obecnie zanzczonego pola, dodawanie i usuwanie dr�g)*/
	void CreatorHandler::HandleInput(sf::Vector2i possibleSelectedCell)
	{
		if (possibleSelectedCell.x == -1 || possibleSelectedCell.y ==-1) { return; }
		else if (possibleSelectedCell.x > this->_gridSize-1 || possibleSelectedCell.y > this->_gridSize-1) { return; }
		this->_row = possibleSelectedCell.x;
		this->_col = possibleSelectedCell.y;
		if (isDrawingRoad) {
            this->_grid->GetCell(_row, _col)._toDelete = false;
			this->_grid->GetCell(_row, _col)._containsRoad = true;
		}
        if (isDeletingRoad) {
            this->_grid->GetCell(_row, _col)._containsRoad = false;
            this->_grid->GetCell(_row, _col)._toDelete = true;
        }
		this->NotifyCells(_grid->_cells);
		this->NotifySelectedCell(sf::Vector2i(this->_row, this->_col));
	}

}
