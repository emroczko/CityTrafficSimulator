/**
 * simulation_handler.cpp
 * Implementation of SimulatonHandler class.
 */

#include "simulation_handler.hpp"
#include <random>
#include "definitions.hpp"

namespace zpr {

    /**
     * Parametrized constructor of SimulationHandler class.
     * @param grid_size - Size of current grid.
     * @param cells - Vector of cells containg information about roads.
     */
    SimulationHandler::SimulationHandler(int grid_size, std::vector<Cell> cells) : isSimulating_(false), gridSize_(grid_size), cells_(cells)
    {
        init();
    }
    /**
     * Method which initializes elements of this class.
     */
    void SimulationHandler::init()
    {
        this->cellSize_ = (SCREEN_HEIGHT / this->gridSize_);
        this->sidewalkSize_ = round(SIDEWALK_SIZE * cellSize_ / ROAD_IMAGE_SIZE);
        this->roadSize_ = round(ROAD_SIZE * cellSize_ / ROAD_IMAGE_SIZE);
        this->roadStripesSize_ = round(ROAD_STRIPES_SIZE * cellSize_ / ROAD_IMAGE_SIZE);
  
        this->cityExitSite_.setSize(sf::Vector2f((SCREEN_HEIGHT / this->gridSize_) / 2, SCREEN_HEIGHT / this->gridSize_));
        this->cityExitSite_.setOrigin(sf::Vector2f(this->cityExitSite_.getSize().x / 2, this->cityExitSite_.getSize().y / 2));
        sf::Vector2f centered_position_in_pixels = sf::Vector2f(STARTING_CELL_COL * this->cellSize_ + this->calculatePrefix() + this->cellSize_ / 2 , STARTING_CELL_ROW * this->cellSize_ + this->calculatePrefix());
        centered_position_in_pixels.x = centered_position_in_pixels.x + this->cellSize_ / 4;
        centered_position_in_pixels.y = centered_position_in_pixels.y + this->cellSize_ / 2;
        this->cityExitSite_.setPosition(centered_position_in_pixels);
    }

    /**
     * Method which starts simulation. It also launches timer (new thread) to handle simulation.
     */
    void SimulationHandler::updateIsSimulating()
    {
        this->isSimulating_ = !this->isSimulating_;
        if (isSimulating_){
            this->separateRoadsFromCells();
            this->separateCamerasFromCells();
            this->startSimulationTimer_.setInterval([&]() {
                this->addCarsToSimulate();
                this->moveVehicles();
                this->deleteVehicles();
                this->notifyVehicles(this->vehicles_);
                
            }, 17);
        }
        else{
            this->startSimulationTimer_.stopTimer();
            std::this_thread::sleep_for(std::chrono::milliseconds(5));
            this->vehicles_.clear();
            this->notifyVehicles(this->vehicles_);
            this->roads_.clear();
            this->cameras_.clear();
            /*
            this->clearDataTimer_.setTimeout([&]() {
                this->vehicles_.clear();
                this->roads_.clear();
                this->cameras_.clear();
                this->notifyVehicles(this->vehicles_);
            }, 10);*/
        }
        this->notifyIsSimulating(this->isSimulating_);

    }

    /**
     * Method which update cells of object of this class.
     * @param cells - Updated cells.
     */
    void SimulationHandler::updateCells(std::vector<Cell> cells)
    {
        this->cells_ = cells;
        this->separateCamerasFromCells();
    }

    /**
     * Method which gets roads from vector of cells.
     */
    void SimulationHandler::separateRoadsFromCells()
    {
        for (Cell& cell : cells_) {
            if (cell.containsRoad_) {
                this->roads_.push_back(this->convertCellToCenteredRectShape(cell));
            }    
        }
        this->addStartingRoad();
    }

    /**
     * Method which gets cameras from vector of cells.
     */
    void SimulationHandler::separateCamerasFromCells()
    {

        this->cameras_.clear();
        for (Cell& cell : this->cells_) {
            if (cell.containsCamera_) {
                this->cameras_.push_back(Camera(cell.whichCamera_, this->convertCellToCenteredRectShape(cell)));
            }
        }
    }

    /**
     * Method which converts Cell object to sf::RectangleShape object.
     * @param cell - Cell to convert.
     * @return - Converted sf::RectangleShape object.
     */
    sf::RectangleShape SimulationHandler::convertCellToCenteredRectShape(Cell cell)
    {
        sf::RectangleShape rect_shape;
        rect_shape.setSize(sf::Vector2f(SCREEN_HEIGHT / this->gridSize_, SCREEN_HEIGHT / this->gridSize_));
        rect_shape.setOrigin(sf::Vector2f(rect_shape.getSize().x / 2, rect_shape.getSize().y / 2));
        sf::Vector2f centered_position_in_pixels = sf::Vector2f(cell.getPosition().x * this->cellSize_ + this->calculatePrefix(), cell.getPosition().y * this->cellSize_ + this->calculatePrefix());
        centered_position_in_pixels.x = centered_position_in_pixels.x + this->cellSize_ / 2;
        centered_position_in_pixels.y = centered_position_in_pixels.y + this->cellSize_ / 2;
        rect_shape.setPosition(centered_position_in_pixels);
        return rect_shape;
    }

    /**
     * Method which adds starting road to roads vector.
     */
    void SimulationHandler::addStartingRoad() {
        sf::RectangleShape road;
        road.setSize(sf::Vector2f(SCREEN_HEIGHT / this->gridSize_, SCREEN_HEIGHT / this->gridSize_));
        road.setOrigin(sf::Vector2f(road.getSize().x / 2, road.getSize().y / 2));
        sf::Vector2f centered_position_in_pixels = sf::Vector2f(STARTING_CELL_COL * this->cellSize_ + this->calculatePrefix(), STARTING_CELL_ROW * this->cellSize_ + this->calculatePrefix());
        centered_position_in_pixels.x = centered_position_in_pixels.x + this->cellSize_ / 2;
        centered_position_in_pixels.y = centered_position_in_pixels.y + this->cellSize_ / 2;
        road.setPosition(centered_position_in_pixels);
        this->roads_.push_back(road);
    }

    /**
     * Method responsible for calculating prefix - to drawing grid in the center of view.
     * @return - Calculated prefix.
     */
    int SimulationHandler::calculatePrefix() {
        double cell_size_with_point = (double)SCREEN_HEIGHT / gridSize_;
        double the_rest = cell_size_with_point - this->cellSize_;
        int draw_prefix = the_rest * gridSize_ / 2;
        return draw_prefix;
    }
   
    /**
     * Method which add cars to simulation.
     */
    void SimulationHandler::addCarsToSimulate()
    {
        int x_start =this->calculatePrefix() + cellSize_ * STARTING_CELL_COL + this->sidewalkSize_ + this->roadSize_/4;
        int y_start = this->calculatePrefix() + cellSize_ * STARTING_CELL_ROW + ROAD_IMAGE_SIZE / 2;

        std::random_device rng;
        std::mt19937 eng(std::chrono::high_resolution_clock::now().time_since_epoch().count());
        std::uniform_int_distribution<> dist(1, 100);
        int num = dist(eng);
        
        if (this->startingCellFree() && num > 0 && num < 7 && this->vehicles_.size()<this->roads_.size()/2) {
            if (num > 4) {
            this->vehicles_.push_back(VehicleFactory::createTruck(x_start, y_start, this->cellSize_, this->roads_));
            }
            else {
                this->vehicles_.push_back(VehicleFactory::createCar(x_start, y_start, this->cellSize_, this->roads_));
            }
        }  
    }

    /**
     * Method responsible for moving vehicles - triggering certain methods to properly move the vehicle.
     */
    void SimulationHandler::moveVehicles()
    {
        for (std::shared_ptr<Vehicle> vehicle : this->vehicles_) {
            vehicle->checkOnWhichCell();
            this->vehiclesColision();
            vehicle->move();
            vehicle->checkTurn();
            this->checkCameraVision();
        }
    }

    /**
     * Method responsible for checking vehicles colisions with other vehicles.
     */
    void SimulationHandler::vehiclesColision()
    {
        for (std::shared_ptr<Vehicle> vehicle : this->vehicles_) {
            int colision_counter = 0;
            for (std::shared_ptr<Vehicle> colider : this->vehicles_) {
                if (vehicle->checkColision(colider)) {
                    colision_counter++;
                }
            }
            if (colision_counter > 0) {
                vehicle->stopVehicle();
            }
            else {
                vehicle->noColision();
            }
        }
    }

    /**
     * Method responsible for checking what do cameras see.
     */
    void SimulationHandler::checkCameraVision()
    {
        for (Camera camera : this->cameras_) {
            this->checkCameraColision(camera);
        }
    }

    /**
     * Method responsible for checking if camera sees the car.
     * @param camera - Camera object which the method is checking.s
     */
    void SimulationHandler::checkCameraColision(Camera camera)
    {

        for (std::shared_ptr<Vehicle>& vehicle : this->vehicles_) {
            if (camera.checkColision(vehicle)) {
                this->checkVehicleTypeAndNotify(vehicle, camera.cameraNumber_);
                vehicle->seenByCamera_[camera.cameraNumber_-1] = true;
            }
            else {
                vehicle->seenByCamera_[camera.cameraNumber_-1] = false;
            }
        }
    }

    /**
     * Method responsible for checking if vehicle is a car or truck and notify proper labels.
     * @param vehicle - Vehicle to check.
     * @param camera_label_number - Label number to update.
     */
    void SimulationHandler::checkVehicleTypeAndNotify(std::shared_ptr<Vehicle> vehicle, int camera_label_number)
    {
        if (!vehicle->seenByCamera_[camera_label_number-1]) {
            if (vehicle->getShape().getSize().x == vehicle->getShape().getSize().y)
                this->notifyCarsLabel(camera_label_number);
            
            else
                this->notifyTrucksLabel(camera_label_number);
            
        }
    }

    /**
     * Method responsible for checking if starting cell is free. (not to spawn vehicle on vehicle)
     * @return - True if starting cell is free, false otherwise.
     */
    bool SimulationHandler::startingCellFree()
    {
        for (std::shared_ptr<Vehicle> vehicle : this->vehicles_) {
            if (this->roads_.back().getGlobalBounds().contains(vehicle->getShape().getPosition())) {
                return false;
            }   
        }
        return true;
    }

    /**
     * Method responsible for deleting the vehicles.
     */
    void SimulationHandler::deleteVehicles()
    {
        int i = 0;
        for (std::shared_ptr<Vehicle> vehicle : this->vehicles_) {
            if (this->cityExitSite_.getGlobalBounds().contains(vehicle->getShape().getPosition())) {
                this->vehicles_.erase(vehicles_.begin() + i);
                return;
            }
            i++;
        }
    }
    
    /**
     * Method responsible for handle input.
     */
    void SimulationHandler::handleInput()
    {
    
    }

    /**
     * Method responsible for saving to file.
     */
    void SimulationHandler::saveToFile(){
    
    }
}
