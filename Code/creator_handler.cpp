/**
 * creator_handler.cpp
 * Implementation of CreatorHandler class.
 */


#include "creator_handler.hpp"

namespace zpr {

    /**
     * Parametrized constructor of CreatorHandler class.
     * @param grid_size - Size of current grid.
     */
	CreatorHandler::CreatorHandler(int grid_size): gridSize_(grid_size), row_(-1), col_(-1), isDrawingRoad_(false), isDeletingRoad_(false), isAddingCameras_(false), enterGridHeight_(2) {}

    /**
     * Parametrized constructor of CreatorHandler class.
     * @param grid_size - Size of current grid.
     * @param cells - Vector of cells containg information about roads.
     */
    CreatorHandler::CreatorHandler(int grid_size, std::vector<Cell> cells): gridSize_(grid_size), cells_(cells), row_(-1), col_(-1), isDrawingRoad_(false), isDeletingRoad_(false), isAddingCameras_(false), enterGridHeight_(2) {}


    /**
     * Method which initializes elements of this class. It also notifies observers about its state.
     */
	void CreatorHandler::init()
	{
        if (cells_.empty())
            this->generateBoard();
        
//        else
//            this->clearRoads();
        
        this->generateEnterBoard();
        
        this->notifyEnterCells(enterCells_);
		this->notifyCells(cells_);
		this->notifyIsDrawingRoad(this->isDrawingRoad_);
        this->notifyIsDeletingRoad(this->isDeletingRoad_);
	}

    
    /**
     * Method which generates grid containing cells of previously chosen size.
     */
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

    /**
     * Method responsible for generating grid containing enter road.
     */
    void CreatorHandler::generateEnterBoard()
    {
        std::vector<Cell> enterCells;
        for (int i = 0; i < this->enterGridHeight_ * this->gridSize_; i++)
        {
            enterCells_.push_back(Cell(((i / gridSize_)-2), i % gridSize_));
        }
        for (Cell& cell : enterCells_){
            int row = cell.getPosition().x;
            int col = cell.getPosition().y;
            if(row == -2 && col != 0 && col != gridSize_-1){
                cell.containsRoad_ = true;
            }
            else if(row == -1 && col == 4){
                cell.containsRoad_ = true;
            }
        }
    }

    /**
     * Method which clears the vector of cells from drawn roads.
     */
    void CreatorHandler::clearRoads(){
        for (Cell& cell: cells_){
            cell.roadDrawn_ = false;
        }
        this->grid_ = std::make_unique<Grid>(cells_, gridSize_);
    }

    /**
     * Method which sets drawing road mode on or off.
     */
	void CreatorHandler::updateIsDrawingRoad()
	{
        this->isDrawingRoad_ = !this->isDrawingRoad_;
        this->isDeletingRoad_ = false;
        this->isAddingCameras_ = false;
		this->notifyIsDrawingRoad(this->isDrawingRoad_);
	}

    /**
     * Method which sets deleting road mode on or off.
     */
    void CreatorHandler::updateIsDeletingRoad()
    {
        this->isDeletingRoad_ = !this->isDeletingRoad_;
        this->isDrawingRoad_ = false;
        this->isAddingCameras_ = false;
        this->notifyIsDeletingRoad(this->isDeletingRoad_);
    }

    /**
     * Method which sets adding camera mode on or off.
     * @param which_camera - Being added camera number.
     */
    void CreatorHandler::updateIsAddingCamera(int which_camera)
    {
        this->whichCamera_ = which_camera;
        this->isAddingCameras_ = !this->isAddingCameras_;
        this->isDeletingRoad_ = false;
        this->isDrawingRoad_ = false;
        this->notifyIsAddingCamera(this->isAddingCameras_, this->whichCamera_);
    }

    /**
     * Method which sets deleting camera mode on or off.
     * @param which_camera - Deleted camera number.
     */
    void CreatorHandler::updateIsDeletingCamera(int which_camera)
    {
        this->whichCamera_ = which_camera;
        this->notifyIsDeletingCamera(this->whichCamera_);
        for (Cell& cell : grid_->cells_){
            if (cell.containsCamera_ == true && cell.whichCamera_ == which_camera){
                cell.containsCamera_ = false;
                cell.whichCamera_ = 0;
                cell.cameraToDelete_ = false;
                this->notifyCells(grid_->cells_);
            }
        }
    }

    /**
     * Method which inform observer about user clicking "Save to file" button.
     */
    void CreatorHandler::saveToFile(){
        this->notifySave();
    }

    /**
     * Method which sets simulation mode on or off.
     */
    void CreatorHandler::updateIsSimulating()
    {
        this->isDeletingRoad_ = false;
        this->isDrawingRoad_ = false;
		this->notifyCells(grid_->cells_);
    }
    

    /**
     * Method which handles user input (currently chosen cell, adding and deleting roads and cameras)
     * @param possible_selected_cell - Cell selected by user.
     */
	void CreatorHandler::handleInput(sf::Vector2i possible_selected_cell)
	{
		if (possible_selected_cell.x == -1 || possible_selected_cell.y ==-1) { return; }
		else if (possible_selected_cell.x > this->gridSize_-1 || possible_selected_cell.y > this->gridSize_-1) { return; }
		this->row_ = possible_selected_cell.y;
		this->col_ = possible_selected_cell.x;
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
            this->notifyIsAddingCamera(isAddingCameras_, whichCamera_);
            this->notifyCameraAdded(whichCamera_, row_, col_);
        }
	}
}
