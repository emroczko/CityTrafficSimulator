#include "creator_handler.hpp"

namespace zpr {
	CreatorHandler::CreatorHandler(int gridSize_): gridSize_(gridSize_), row_(-1), col_(-1), isDrawingRoad_(false), isDeletingRoad_(false), isAddingCameras_(false), enterGridHeight_(2) {}

    
    CreatorHandler::CreatorHandler(int grid_size, std::vector<Cell> cells): gridSize_(grid_size), cells_(cells), row_(-1), col_(-1), isDrawingRoad_(false), isDeletingRoad_(false), isAddingCameras_(false), enterGridHeight_(2) {}

	void CreatorHandler::init()
	{
        if (cells_.empty())
            this->generateBoard();
        
        else
            this->clearRoads();
        
		this->notifyCells(grid_->cells_);
		this->notifyIsDrawingRoad(this->isDrawingRoad_);
        this->notifyIsDeletingRoad(this->isDeletingRoad_);
	}
	/*Generuje siatkê zawierajac¹ komórki o wybranej wielkoœci*/
	void CreatorHandler::generateBoard()
	{
		std::vector<Cell> cells;
		for (int i = 0; i < this->gridSize_ * this->gridSize_; i++)
		{
			cells.push_back(Cell(i / gridSize_, i % gridSize_));
		}
		cells.at(4).isStartingCell_ = true;
        this->grid_ = std::make_unique<Grid>(cells, gridSize_);
	}
    void CreatorHandler::clearRoads(){
        for (Cell& cell: cells_){
            cell.roadDrawn_ = false;
        }
        this->grid_ = std::make_unique<Grid>(cells_, gridSize_);
    }
	/*Ustawia tryb rysowania drogi na w³¹czony lub wy³¹czony*/
	void CreatorHandler::updateIsDrawingRoad()
	{
        this->isDrawingRoad_ = !this->isDrawingRoad_;
        this->isDeletingRoad_ = false;
        this->isAddingCameras_ = false;
		this->notifyIsDrawingRoad(this->isDrawingRoad_);
	}
	/*Ustawia tryb usuwania drogi na w³¹czony lub wy³¹czony w zale¿noœci od obecnego stanu*/
    void CreatorHandler::updateIsDeletingRoad()
    {
        this->isDeletingRoad_ = !this->isDeletingRoad_;
        this->isDrawingRoad_ = false;
        this->isAddingCameras_ = false;
        this->notifyIsDeletingRoad(this->isDeletingRoad_);
    }
    void CreatorHandler::updateIsAddingCamera(int whichCamera)
    {
        this->whichCamera_ = whichCamera;
        this->isAddingCameras_ = !this->isAddingCameras_;
        this->isDeletingRoad_ = false;
        this->isDrawingRoad_ = false;
        this->notifyIsAddingCamera(this->isAddingCameras_, this->whichCamera_, this->row_, this->col_);
    }
    void CreatorHandler::updateIsDeletingCamera(int whichCamera)
    {
        int row, col;
        //this->isAddingCameras_ = false;
        this->whichCamera_ = whichCamera;
        this->notifyIsDeletingCamera(this->whichCamera_);
        for (Cell& cell : grid_->cells_){
            if (cell.containsCamera_ == true && cell.whichCamera_ == whichCamera){
                row = cell.getPosition().x;
                col = cell.getPosition().y;
                this->grid_->getCell(row_, col_).containsCamera_ = false;
                this->grid_->getCell(row_, col_).whichCamera_ = 0;
                this->grid_->getCell(row_, col_).cameraToDelete_ = false;
                this->notifyCells(grid_->cells_);
                this->notifySelectedCell(sf::Vector2i(row, col));
            }
        }
        
        
        
    }
    void CreatorHandler::saveToFile(){
        this->notifySave();
    }
	/*Ustawia tryb symulacji*/
    void CreatorHandler::updateIsSimulating()
    {
        this->isDeletingRoad_ = false;
        this->isDrawingRoad_ = false;
		this->notifyCells(grid_->cells_);
    }
	/*Zajmuje sie obs³ug¹ zdarzeñ (zmiana obecnie zanzczonego pola, dodawanie i usuwanie dróg)*/
	void CreatorHandler::handleInput(sf::Vector2i possibleSelectedCell)
	{
		if (possibleSelectedCell.x == -1 || possibleSelectedCell.y ==-1) { return; }
		else if (possibleSelectedCell.x > this->gridSize_-1 || possibleSelectedCell.y > this->gridSize_-1) { return; }
		this->row_ = possibleSelectedCell.y;
		this->col_ = possibleSelectedCell.x;
		if (isDrawingRoad_) {
            this->grid_->getCell(row_, col_).toDelete_ = false;
			this->grid_->getCell(row_, col_).containsRoad_ = true;
            this->notifyCells(grid_->cells_);
            this->notifySelectedCell(sf::Vector2i(this->row_, this->col_));
		}
        if (isDeletingRoad_) {
            this->grid_->getCell(row_, col_).containsRoad_ = false;
            this->grid_->getCell(row_, col_).toDelete_ = true;
            this->notifyCells(grid_->cells_);
            this->notifySelectedCell(sf::Vector2i(this->row_, this->col_));
        }
        if (isAddingCameras_ && this->grid_->getCell(row_, col_).toDelete_ == false && this->grid_->getCell(row_, col_).containsRoad_ == true){
            this->grid_->getCell(row_, col_).containsCamera_ = true;
            this->grid_->getCell(row_, col_).whichCamera_ = this->whichCamera_;
            this->notifyCells(grid_->cells_);
            this->notifySelectedCell(sf::Vector2i(this->row_, this->col_));
            this->isAddingCameras_ = false;
            this->notifyIsAddingCamera(isAddingCameras_, whichCamera_, this->row_, this->col_);
        }
        
		
	}
}
