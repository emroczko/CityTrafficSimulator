#include "CreatorHandler.h"

namespace ZPR {
	CreatorHandler::CreatorHandler(int gridSize): _gridSize(gridSize), _row(-1), _col(-1), isDrawingRoad(false), isDeletingRoad(false), _enterGridHeight(2) {}

	void CreatorHandler::init()
	{
		this->GenerateBoard();
		this->NotifyCells(_grid->_cells);
		this->NotifyIsDrawingRoad(this->isDrawingRoad);
        this->NotifyIsDeletingRoad(this->isDeletingRoad);
	}
	/*Generuje siatkê zawierajac¹ komórki o wybranej wielkoœci*/
	void CreatorHandler::GenerateBoard()
	{
		std::vector<Cell> cells;
		for (int i = 0; i < this->_gridSize * this->_gridSize; i++)
		{
			cells.push_back(Cell(i / _gridSize, i % _gridSize));
		}
		cells.at(4).isStartingCell = true;
        this->_grid = std::make_unique<Grid>(cells, _gridSize);
	}
	/*Ustawia tryb rysowania drogi na w³¹czony lub wy³¹czony*/
	void CreatorHandler::UpdateIsDrawingRoad()
	{
        this->isDrawingRoad = !this->isDrawingRoad;
        this->isDeletingRoad = false;
		this->NotifyIsDrawingRoad(this->isDrawingRoad);
	}
	/*Ustawia tryb usuwania drogi na w³¹czony lub wy³¹czony w zale¿noœci od obecnego stanu*/
    void CreatorHandler::UpdateIsDeletingRoad()
    {
        this->isDeletingRoad = !this->isDeletingRoad;
        this->isDrawingRoad = false;
        this->NotifyIsDeletingRoad(this->isDeletingRoad);
    }
    void CreatorHandler::SaveToFile(){
        this->NotifySave();
    }
	/*Ustawia tryb symulacji*/
    void CreatorHandler::UpdateIsSimulating()
    {
        this->isDeletingRoad = false;
        this->isDrawingRoad = false;
		this->NotifyCells(_grid->_cells);
    }
	/*Zajmuje sie obs³ug¹ zdarzeñ (zmiana obecnie zanzczonego pola, dodawanie i usuwanie dróg)*/
	void CreatorHandler::HandleInput(sf::Vector2i possibleSelectedCell)
	{
		if (possibleSelectedCell.x == -1 || possibleSelectedCell.y ==-1) { return; }
		else if (possibleSelectedCell.x > this->_gridSize-1 || possibleSelectedCell.y > this->_gridSize-1) { return; }
		this->_row = possibleSelectedCell.y;
		this->_col = possibleSelectedCell.x;
		if (isDrawingRoad) {
            this->_grid->GetCell(_row, _col)._toDelete = false;
			this->_grid->GetCell(_row, _col)._containsRoad = true;
            this->NotifyCells(_grid->_cells);
            this->NotifySelectedCell(sf::Vector2i(this->_row, this->_col));
		}
        if (isDeletingRoad) {
            this->_grid->GetCell(_row, _col)._containsRoad = false;
            this->_grid->GetCell(_row, _col)._toDelete = true;
            this->NotifyCells(_grid->_cells);
            this->NotifySelectedCell(sf::Vector2i(this->_row, this->_col));
        }
        
		
	}
}
