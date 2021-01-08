#include "CreatorHandler.h"

<<<<<<< HEAD
namespace ZPR{
	CreatorHandler::CreatorHandler(int gridSize): _gridSize(gridSize), _row(-1), _col(-1), _isDrawingRoad(false), _isDeletingRoad(false), _isAddingCameras(false), _enterGridHeight(2) {}
    CreatorHandler::CreatorHandler(int gridSize, std::vector<Cell> cells): _gridSize(gridSize), _cells(cells), _row(-1), _col(-1), _isDrawingRoad(false), _isDeletingRoad(false), _isAddingCameras(false), _enterGridHeight(2) {}
=======
namespace ZPR {
	CreatorHandler::CreatorHandler(int gridSize): _gridSize(gridSize), _row(-1), _col(-1), _isDrawingRoad(false), _isDeletingRoad(false), _enterGridHeight(2) {}
    CreatorHandler::CreatorHandler(int gridSize, std::vector<Cell> cells): _gridSize(gridSize), _cells(cells), _row(-1), _col(-1), _isDrawingRoad(false), _isDeletingRoad(false), _enterGridHeight(2) {}
>>>>>>> parent of 6541e9a... Merge branch 'main' of https://github.com/emroczko/CityTrafficSimulator_ZPR into main

	void CreatorHandler::init()
	{
        if (_cells.empty()) {
            this->GenerateBoard();
<<<<<<< HEAD
        }
        else{
=======
        
        else {
>>>>>>> parent of 6541e9a... Merge branch 'main' of https://github.com/emroczko/CityTrafficSimulator_ZPR into main
            this->ClearRoads();
            this->NotifyCells(_grid->_cells);
            this->NotifyIsDrawingRoad(this->_isDrawingRoad);
            this->NotifyIsDeletingRoad(this->_isDeletingRoad);
        }
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
    void CreatorHandler::ClearRoads(){
        for (Cell& cell: _cells){
            cell._roadDrawn = false;
        }
        this->_grid = std::make_unique<Grid>(_cells, _gridSize);
    }
	/*Ustawia tryb rysowania drogi na w³¹czony lub wy³¹czony*/
	void CreatorHandler::UpdateIsDrawingRoad()
	{
        this->_isDrawingRoad = !this->_isDrawingRoad;
        this->_isDeletingRoad = false;
		this->NotifyIsDrawingRoad(this->_isDrawingRoad);
	}
	/*Ustawia tryb usuwania drogi na w³¹czony lub wy³¹czony w zale¿noœci od obecnego stanu*/
    void CreatorHandler::UpdateIsDeletingRoad()
    {
        this->_isDeletingRoad = !this->_isDeletingRoad;
        this->_isDrawingRoad = false;
        this->NotifyIsDeletingRoad(this->_isDeletingRoad);
    }
    void CreatorHandler::SaveToFile(){
        this->NotifySave();
    }
	/*Ustawia tryb symulacji*/
    void CreatorHandler::UpdateIsSimulating()
    {
        this->_isDeletingRoad = false;
        this->_isDrawingRoad = false;
		this->NotifyCells(_grid->_cells);
    }
	/*Zajmuje sie obs³ug¹ zdarzeñ (zmiana obecnie zanzczonego pola, dodawanie i usuwanie dróg)*/
	void CreatorHandler::HandleInput(sf::Vector2i possibleSelectedCell)
	{
		if (possibleSelectedCell.x == -1 || possibleSelectedCell.y ==-1) { return; }
		else if (possibleSelectedCell.x > this->_gridSize-1 || possibleSelectedCell.y > this->_gridSize-1) { return; }
		this->_row = possibleSelectedCell.y;
		this->_col = possibleSelectedCell.x;
		if (_isDrawingRoad) {
            this->_grid->GetCell(_row, _col)._toDelete = false;
			this->_grid->GetCell(_row, _col)._containsRoad = true;
            this->NotifyCells(_grid->_cells);
            this->NotifySelectedCell(sf::Vector2i(this->_row, this->_col));
		}
        if (_isDeletingRoad) {
            this->_grid->GetCell(_row, _col)._containsRoad = false;
            this->_grid->GetCell(_row, _col)._toDelete = true;
            this->NotifyCells(_grid->_cells);
            this->NotifySelectedCell(sf::Vector2i(this->_row, this->_col));
        }
	}
}

