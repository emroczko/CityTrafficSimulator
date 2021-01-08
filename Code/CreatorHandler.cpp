#include "CreatorHandler.h"

namespace ZPR{
	CreatorHandler::CreatorHandler(int gridSize): _gridSize(gridSize), _row(-1), _col(-1), _isDrawingRoad(false), _isDeletingRoad(false), _isAddingCameras(false), _enterGridHeight(2) {}
    CreatorHandler::CreatorHandler(int gridSize, std::vector<Cell> cells): _gridSize(gridSize), _cells(cells), _row(-1), _col(-1), _isDrawingRoad(false), _isDeletingRoad(false), _isAddingCameras(false), _enterGridHeight(2) {}

	void CreatorHandler::init()
	{
        if (_cells.empty()) {
            this->GenerateBoard();
        }
        else{
            this->ClearRoads();
            this->NotifyCells(_grid->_cells);
            this->NotifyIsDrawingRoad(this->_isDrawingRoad);
            this->NotifyIsDeletingRoad(this->_isDeletingRoad);
        }

		//this->NotifyCells(_grid->_cells);
		//this->NotifyIsDrawingRoad(this->_isDrawingRoad);
        //this->NotifyIsDeletingRoad(this->_isDeletingRoad);
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
    void CreatorHandler::UpdateIsAddingCamera(int whichCamera)
    {
        this->_whichCamera = whichCamera;
        this->_isAddingCameras = !this->_isAddingCameras;
        this->_isDeletingRoad = false;
        this->_isDrawingRoad = false;
        this->NotifyIsAddingCamera(this->_isAddingCameras, this->_whichCamera);
    }
    void CreatorHandler::UpdateIsDeletingCamera(int whichCamera)
    {
        int row, col;
        //this->_isAddingCameras = false;
        this->_whichCamera = whichCamera;
        this->NotifyIsDeletingCamera(this->_whichCamera);
        for (Cell& cell : _grid->_cells){
            if (cell._containsCamera == true && cell._whichCamera == whichCamera){
                row = cell.GetPosition().x;
                col = cell.GetPosition().y;
                this->_grid->GetCell(_row, _col)._containsCamera = false;
                this->_grid->GetCell(_row, _col)._whichCamera = 0;
                this->_grid->GetCell(_row, _col)._cameraToDelete = true;
                //this->_grid->GetCell(_row, _col)._cameraDrawn = false;
                this->NotifyCells(_grid->_cells);
                this->NotifySelectedCell(sf::Vector2i(row, col));
            }
        }
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
        if (_isAddingCameras && this->_grid->GetCell(_row, _col)._toDelete == false && this->_grid->GetCell(_row, _col)._containsRoad == true){
            this->_grid->GetCell(_row, _col)._containsCamera = true;
            this->_grid->GetCell(_row, _col)._whichCamera = this->_whichCamera;
            this->NotifyCells(_grid->_cells);
            this->NotifySelectedCell(sf::Vector2i(this->_row, this->_col));
            this->_isAddingCameras = false;
            this->NotifyIsAddingCamera(_isAddingCameras, _whichCamera);
        }
        
		
	}
}

