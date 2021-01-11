/**
 * map_view.cpp
 * Implementation of MapView class.
 */

#include "map_view.hpp"
#include <iostream>
#include <random>
#include "save_state.hpp"

namespace zpr {

    /**
     * Parametrized constructor of MapView class.
     * @param data - Struct containing data of current application. (eg. window, assets).
     * @param grid_size - Size of grid chosen by user.
     */
	MapView::MapView(SimulatorDataRef data, int grid_size): data_(data), gridSize_(grid_size){
		init();
        
	}

    
    /**
     * Parametrized constructor of MapView class.
     * @param map_view - MapView object to be copied.
     */
    MapView::MapView(const MapView& map_view): data_(map_view.data_), gridSize_(map_view.gridSize_), cells_(map_view.cells_){
        init();
    }

    /**
     * Method which initializes all elements in the current state to display it properly.
     */
	void MapView::init() {
        this->drawingHelper_ = std::make_unique<DrawingHelper>(this->data_);
        this->converter_ = std::make_unique<Converter>(this->gridSize_);
        this->addingRectangleShapesHelper_ = std::make_unique<AddingHelper>(this->data_, this->gridSize_);
        this->deletingRectangleShapesHelper_ = std::make_unique<DeletingHelper>(this->data_, this->gridSize_);
        
        this->clicked_ = false;
        this->loadAssets();
		//this->setupSelectedCellRect();
		this->backgroundTexture_.setTexture(this->data_->assets_.getTexture("Background"));
		this->backgroundTexture_.setOrigin(sf::Vector2f(800, 800));
		this->backgroundTexture_.setPosition(this->mapView_.getCenter());
		this->cellSize_ = (SCREEN_HEIGHT / this->gridSize_);
		this->row_ = -1;
		this->col_ = -1;
        this->enterGridWidth_ = this->gridSize_;
        this->enterGridHeight_ = 2;
		//this->selectedCellRect_.setTexture(&this->data_->assets_.getTexture("Selected Cell"));
		this->mapView_ = sf::View(sf::FloatRect(0.f, 0.f, (float)(SCREEN_HEIGHT), (float)(SCREEN_HEIGHT)));
		this->mapView_.setViewport(this->calculateViewPort());
		this->generateGridLines();
        //this->generateEnterBoard();
        this->mapView_.zoom(1.4f);
        this->initializeCameras();
        
        
	}

    /**
     * Method initializing all cameras
     */
    void MapView::initializeCameras(){
            sf::RectangleShape temp;
            for(int i = 0; i < 2; i++){
                cameras_[i] = temp;
            }
    }

    /**
     * Method returning current row and col.
     * @return - Returns current row and col.
     */
	sf::Vector2i MapView::getRowCol()
	{
		return sf::Vector2i(this->row_, this->col_);
	}

    /**
     * Method checking if clicked position is inside map_view.
     * @param mouse_position - Current mouse position.
     * @return - Returns true if position is inside map_view, false otherwise.
     */
	bool MapView::isClicked(sf::Vector2i mouse_position)
	{
		if (mapView_.getViewport().contains(static_cast<float>(mouse_position.x) / SCREEN_WIDTH, static_cast<float>(mouse_position.y) / SCREEN_HEIGHT))
        {
			clicked_ = true;
			return true;
		}
		else
			return false;
	}
    /**
     * Method returning map grid size.
     * @return - Size of map's grid.
     */
	int MapView::getGridSize()
	{
		return this->gridSize_;
	}

    /**
     * Method returning size of one cell.
     * @return - Size of one cell.
     */
	int MapView::getCellSize()
	{
		return this->cellSize_;
	}

    /**
     * Method responsible for loading assets_ needed in this view.
     */
	void MapView::loadAssets()
	{
		this->data_->assets_.loadTexture("Selected Cell", SELECTED_CELL_TEXTURE);
		this->data_->assets_.loadTexture("Background", BACKGROUND_TEXTURE_FILEPATH);
		this->data_->assets_.loadTexture("Road", STREET_TEXTURE);
		this->data_->assets_.loadTexture("Turn", TURN_TEXTURE);
		this->data_->assets_.loadTexture("T_Intersection", T_INTERSECTION_TEXTURE);
		this->data_->assets_.loadTexture("Intersection", INTERSECTION_TEXTURE);
		this->data_->assets_.loadTexture("Crossing", CROSSING_TEXTURE);
        this->data_->assets_.loadTexture("Entry", ENTRY_TEXTURE);
        this->data_->assets_.loadTexture("Camera", CAMERA_TEXTURE);
	}

    /**
     * Method responsible for setting parameters of selected cell.
     */
	void MapView::setupSelectedCellRect()
	{
		this->selectedCellRect_.setSize(sf::Vector2f(SCREEN_HEIGHT / this->gridSize_, SCREEN_HEIGHT / this->gridSize_));
		this->selectedCellRect_.setTexture(&this->data_->assets_.getTexture("Selected Cell"));
	}
    
    /**
     * Method responsible for calculating viewport of this view.
     * @return - Calculated viewport.
     */
	sf::FloatRect MapView::calculateViewPort()
	{
        float rect_width = (float)SCREEN_HEIGHT / (float)SCREEN_WIDTH;
		float rect_left = (1.f - rect_width)/2;
		return sf::FloatRect(rect_left, 0.f, rect_width, 1.f);
	}

    /**
     * Method responsible for generating grid lines representing map.
     */
	void MapView::generateGridLines() {
		int draw_prefix = this->converter_->calculatePrefix();
		for (int i = 0; i <= gridSize_; i++)
		{
			sf::RectangleShape vertical_line(sf::Vector2f(2, (gridSize_)*this->cellSize_));
			vertical_line.setPosition(sf::Vector2f(i * this->cellSize_ + draw_prefix, draw_prefix));
			sf::RectangleShape horizontal_line(sf::Vector2f((gridSize_)*this->cellSize_, 2));
			horizontal_line.setPosition(sf::Vector2f(draw_prefix, i * this->cellSize_ + draw_prefix));
			this->gridLines_.push_back(vertical_line);
			this->gridLines_.push_back(horizontal_line);
		}
	}

    /**
     * Method responsible for filling cells in corect way - adding or deleting road to cells.
     */
	void MapView::fillCells()
	{
		for (Cell& cell : this->cells_) {
			int row = cell.getPosition().x;
			int col = cell.getPosition().y;
			if (cell.containsRoad_ && !cell.roadDrawn_) {
				cell.roadDrawn_ = true;
                this->addingRectangleShapesHelper_->addUserRoad(sf::Vector2i(row, col), this->roads_);
			}
            if (cell.toDelete_) {
                this->deletingRectangleShapesHelper_->deleteRoad(sf::Vector2i(row, col), this->roads_);
				cell.toDelete_ = false;
            }
		}
	}

    /**
     * Method responsible for filling entry cells in corect way - adding or deleting road to entry cells.
     */
    void MapView::fillEnterCells()
    {
        for (Cell& cell : this->enterCells_) {
            int row = cell.getPosition().y;
            int col = cell.getPosition().x;
            if (cell.containsRoad_ && !cell.roadDrawn_) {
                cell.roadDrawn_ = true;
                this->addingRectangleShapesHelper_->addEnterRoad(sf::Vector2i(row, col), roads_);
            }
		}
    
        this->addingRectangleShapesHelper_->addGarage(sf::Vector2i(0, -2), roads_);
        this->addingRectangleShapesHelper_->addGarage(sf::Vector2i(gridSize_-1, -2), roads_);
        
	}

    

    /**
     * Inherited method responsible for handling actions when camera is deleting.
     * @param which_camera - Number of camera to delete.
     */
    void MapView::updateIsDeletingCamera(int which_camera){
        this->whichCamera_ = which_camera;
        this->deletingRectangleShapesHelper_->deleteCamera(sf::Vector2f(cameras_[which_camera-1].getPosition().x, cameras_[which_camera-1].getPosition().y), this->cameras_, this->whichCamera_);
        this->isAddingCamera_ = false;
    }
 
    /**
     * Method which draws elements of map on the screen.
     */
	void MapView::draw()
	{
		this->data_->window_.setView(this->mapView_);
		this->data_->window_.draw(this->backgroundTexture_);
		this->fillCells();
        this->drawingHelper_->drawRoads(this->roads_);
        this->drawingHelper_->drawGrid(this->isSimulating_, gridLines_);
        this->drawingHelper_->drawCameras(this->cameras_);
        this->drawingHelper_->drawVehicles(this->vehicles_);
	}
    
    
    /**
     * Method which handles zooming.
     * @param zoom - Value of zoom.
     */
    void MapView::zoomViewAt(float zoom)
    {
        if (zoom < 0)
            this->mapView_.zoom(1.f/abs(zoom));
        else
            this->mapView_.zoom(zoom);
    }

    /**
     * Method which handles moving view with keys.
     * @param key - Which key was clicked.
     */
    void MapView::move(keysEnum key){
        switch (key){
        case LEFT: this->mapView_.move(-90.f, 0);
            break;
        case RIGHT: this->mapView_.move(90.f, 0);
            break;
        case UP: this->mapView_.move(0, -90.f);
            break;
        case DOWN: this->mapView_.move(0, 90.f);
            break;
        }
    }

    /**
     * Method responsible for updating variable which tells MapView whether we are in simulating mode.
     * @param is_simulating - True if we are simulating, false otherwise.
     */
    void MapView::updateIsSimulating(bool is_simulating){
        this->isSimulating_ = is_simulating;
        this->isDeletingRoad_ = false;
        this->isDrawingRoad_ = false;
    }

    /**
        * Method responsible for updating variable which tells MapView whether we are in drawing road mode.
        * @param is_drawing_road - True if we are drawing road, false otherwise.
        */
       void MapView::updateIsDrawingRoad(bool is_drawing_road)
       {
           this->isDrawingRoad_ = is_drawing_road;
           this->isDeletingRoad_ = false;
           this->isSimulating_ = false;
       }

    /**
     * Method responsible for updating variable which tells MapView whether we are in deleting road mode.
     * @param is_deleting_road - True if we are deleting road, false otherwise.
     */
    void MapView::updateIsDeletingRoad(bool is_deleting_road)
    {
        this->isDeletingRoad_ = is_deleting_road;
        this->isDrawingRoad_ = false;
        this->isSimulating_ = false;
    }

    /**
     * Method responsible for updating coordinates of currently clicked cell.
     * @param coords - Current coordinates.
     */
	void MapView::updateSelectedCell(sf::Vector2i coords)
	{
		this->row_ = coords.x;
		this->col_ = coords.y;
	}

    /**
     * Method responsible for update vector of cells on the map.
     * @param cells - Vector of new cells.
     */
	void MapView::updateCells(std::vector<Cell> cells)
	{
        this->cells_ = cells;
	}

    /**
     * Method responsible for update vector of enter cells on the map.
     * @param enter_cells - Vector of new enter cells.
     */
    void MapView::updateEnterCells(std::vector<Cell> enter_cells)
    {
        this->enterCells_ = enter_cells;
        this->fillEnterCells();
    }

    /**
     * Method responsible for update vector of roads on the map.
     * @param roads - Vector of new roads.
     */
    void MapView::updateRoads(std::vector<sf::RectangleShape> roads)
    {
        this->roads_ = roads;
    }

    /**
     * Method responsible for updating mapView wheteher camera is added.
     * @param which_camera - Number of which camera we added.
     * @param row - Row where should camera is placed.
     * @param col - Column where should camera is placed.
    */
    void MapView::updateCameraAdded(int which_camera, int row, int col)
    {
        this->whichCamera_ = which_camera;
        for (Cell& cell : this->cells_) {
            int row = cell.getPosition().x;
            int col = cell.getPosition().y;
            if (cell.containsCamera_ && !cell.cameraDrawn_) {
                cell.cameraDrawn_ = true;
                this->addingRectangleShapesHelper_->addCamera(sf::Vector2i(row, col), this->cameras_, this->whichCamera_);
            }
        }
    }

    /**
     * Method responsible for creating save state where we can save our map.
     */
    void MapView::saveToFile(){
        this->data_->machine_.addState(StateRef(new SaveState(this->data_, this->cells_, this->gridSize_)), false);
    }

    /**
     * Method responsible for updating vector of vehicles that are on the map.
     * @param vehicles - Vector of the vehicles.
     */
	void MapView::updateVehicles(std::vector<std::shared_ptr<Vehicle>> vehicles)
	{
        if(vehicles.size()==0){
            this->vehicles_.clear();
        }
        else{
            this->vehicles_ = vehicles;
        }
	}

    /**
     * Method returning cells which are on the map.
     * @return - Vector of current cells.
     */
    std::vector<Cell> MapView::getCells(){
        return cells_;
    }
    
    /**
     * Method responsible for initial handling user clicks on the map.
     * @param mouse_position - Position of the mouse.
     * @return - Possible selected row and column.
     */
	sf::Vector2i MapView::handleInput(sf::Vector2f mouse_position)
	{
		int possible_sellected_row = (int)(mouse_position.y / this->cellSize_);
		int possible_sellected_col = (int)(mouse_position.x / this->cellSize_);
		return sf::Vector2i(possible_sellected_row, possible_sellected_col);
	}

    /**
     * Method returning View object representing map.
     * @return - sf::View mapView this mapView object.
     */
	sf::View MapView::getView()
	{
		return this->mapView_;
	}

    /**
     * Overloaded << operator, which is responsible for printing mapView object.
     * @param os - Ofstream object.
     * @param current_map_view - Current mapView object which is to print.
     * @return - Ofstream to where data is passed.
     */
    std::ofstream& operator<< (std::ofstream& os, const MapView& current_map_view){
        os << current_map_view.gridSize_ << std::endl;
        for(auto p : current_map_view.cells_)
            os << p.getPosition().x <<" & "<< p.getPosition().y<<" % "<<p.containsRoad_<<std::endl;
        return os;
    }
}
