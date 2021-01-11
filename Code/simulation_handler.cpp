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
     */
    SimulationHandler::SimulationHandler(int grid_size) : isSimulating_(false), gridSize_(grid_size)
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
  
        
    }

    /**
     * Method which starts simulation. It also launches timer (new thread) to handle simulation.
     */
    void SimulationHandler::updateIsSimulating()
    {
    
        this->isSimulating_ = !this->isSimulating_;
        
        if (isSimulating_){
            this->separateUserRoadsFromCells();
            this->separateCamerasFromCells();
            this->setupExitSites();
            this->startSimulationTimer_.setInterval([&]() {
                this->addCarsToSimulate();
                this->moveVehicles();
                this->deleteVehicles();
                this->notifyVehicles(this->vehicles_);
            }, 17);
        }
        else {
            this->startSimulationTimer_.stopTimer();
            std::this_thread::sleep_for(std::chrono::milliseconds(400));
            this->vehicles_.clear();
            this->notifyVehicles(this->vehicles_);
            this->roads_.erase(roads_.begin()+15, roads_.end());
            this->cameras_.clear();
            this->cityExitSite_.clear();
            
//            this->clearDataTimer_.setTimeout([&]() {
//                this->vehicles_.clear();
//                this->notifyVehicles(this->vehicles_);
//                //this->roads_.clear();
//                this->roads_.erase(roads_.begin()+15, roads_.end());
//                this->cameras_.clear();
//                this->notifyVehicles(this->vehicles_);
//            }, 5);
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
     * Method which update enter cells of object of this class.
     * @param enter_cells - Updated enter cells.
     */
    void SimulationHandler::updateEnterCells(std::vector<Cell> enter_cells)
    {
        this->enterCells_ = enter_cells;
        this->separateEnterRoadsFromCells();
    }

    /**
     * Method which gets roads from vector of cells.
     */
    void SimulationHandler::separateUserRoadsFromCells()
    {
        for (Cell& cell : cells_) {
            this->separateRoadsFromCells(cell);
        }
        this->addStartingRoad();
    }

    /**
     * Method which gets roads from vector of enter cells.
     */
    void SimulationHandler::separateEnterRoadsFromCells()
    {
        for (Cell& cell : enterCells_) {
            if (cell.containsRoad_) {
                this->roads_.push_back(this->convertCellToCenteredRectShape2(cell));
            }
        }
        
    }
    /**
     * Method which checks if cell contains road and if yes, it adds this cell to vector of roads.
     * @param cell - Cell we are currently checking.
     */
    void SimulationHandler::separateRoadsFromCells(Cell& cell)
    {
        if (cell.containsRoad_) {
            this->roads_.push_back(this->convertCellToCenteredRectShape(cell));
        }
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
     * Method which converts Cell object to sf::RectangleShape object.
     * @param cell - Cell to convert.
     * @return - Converted sf::RectangleShape object.
     */
    sf::RectangleShape SimulationHandler::convertCellToCenteredRectShape2(Cell cell)
    {
        sf::RectangleShape rect_shape;
        rect_shape.setSize(sf::Vector2f(SCREEN_HEIGHT / this->gridSize_, SCREEN_HEIGHT / this->gridSize_));
        rect_shape.setOrigin(sf::Vector2f(rect_shape.getSize().y / 2, rect_shape.getSize().x / 2));
        sf::Vector2f centered_position_in_pixels = sf::Vector2f(cell.getPosition().y * this->cellSize_ + this->calculatePrefix(), cell.getPosition().x * this->cellSize_ + this->calculatePrefix());
        centered_position_in_pixels.x = centered_position_in_pixels.x + this->cellSize_ / 2;
        centered_position_in_pixels.y = centered_position_in_pixels.y + this->cellSize_ / 2;
        rect_shape.setPosition(centered_position_in_pixels);
        return rect_shape;
    }

    /**
     * Method which adds starting road to roads vector.
     */
    
    void SimulationHandler::addStartingRoad() {
        int starting_cell_x[2];
        starting_cell_x[0] = 0;
        starting_cell_x[1] = sqrt(this->cells_.size()) - 1;
        for (int i = 0; i < 2; i++) {
            sf::RectangleShape road;
            road.setSize(sf::Vector2f(SCREEN_HEIGHT / this->gridSize_, SCREEN_HEIGHT / this->gridSize_));
            road.setOrigin(sf::Vector2f(road.getSize().x / 2, road.getSize().y / 2));
            sf::Vector2f centered_position_in_pixels = sf::Vector2f(starting_cell_x[i] * this->cellSize_ + this->calculatePrefix(), -2 * this->cellSize_ + this->calculatePrefix());
            centered_position_in_pixels.x = centered_position_in_pixels.x + this->cellSize_ / 2;
            centered_position_in_pixels.y = centered_position_in_pixels.y + this->cellSize_ / 2;
            road.setPosition(centered_position_in_pixels);
            this->roads_.push_back(road);
        }
    }


    void SimulationHandler::setupExitSites()
    {
        int exit_cell_x[2];
        exit_cell_x[0] = 0;
        exit_cell_x[1] = sqrt(this->cells_.size()) - 1;
        for (int i = 0; i < 2; i++) {
            sf::RectangleShape exit_site;
            exit_site.setSize(sf::Vector2f(SCREEN_HEIGHT / this->gridSize_, (SCREEN_HEIGHT / this->gridSize_) / 2));
            exit_site.setOrigin(sf::Vector2f(exit_site.getSize().x / 2, exit_site.getSize().y / 2));
            sf::Vector2f centered_position_in_pixels = sf::Vector2f(exit_cell_x[i] * this->cellSize_ + this->calculatePrefix(), -2 * this->cellSize_ + this->calculatePrefix());
            centered_position_in_pixels.x = centered_position_in_pixels.x + this->cellSize_ / 2;
            centered_position_in_pixels.y = centered_position_in_pixels.y + this->cellSize_ * (2 * i + 1) / 4;
            exit_site.setPosition(centered_position_in_pixels);
            this->cityExitSite_.push_back(exit_site);
        }
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

        if (this->startingCellFree() && this->vehicles_.size() < this->roads_.size() / 2) {
            
            int x_start_1 =this->calculatePrefix() + cellSize_ * STARTING_CELL_COL +  ROAD_IMAGE_SIZE / 2;
            int y_start_1 = this->calculatePrefix() + cellSize_ * STARTING_CELL_ROW + this->sidewalkSize_ + this->roadSize_/4;
            int x_start_2 = this->calculatePrefix() + cellSize_ * STARTING_CELL_COL2 + ROAD_IMAGE_SIZE / 2;
            int y_start_2 = this->calculatePrefix() + cellSize_ * STARTING_CELL_ROW2 + this->sidewalkSize_ + this->roadSize_ / 4;
        
            std::random_device rng;
            std::mt19937 eng(std::chrono::high_resolution_clock::now().time_since_epoch().count());
            std::uniform_int_distribution<> dist(1, 100);
            int num = dist(eng);

            if (num > 0 && num < 7) {
                if (num > 4) {
                    if (num == 5) {
                        this->vehicles_.push_back(VehicleFactory::createTruck(x_start_1, y_start_1, this->cellSize_, this->roads_, "East"));
                    }
                    else {
                        this->vehicles_.push_back(VehicleFactory::createTruck(x_start_2, y_start_2, this->cellSize_, this->roads_, "West"));
                    }
                }
                else {
                    if (num <= 2) {
                        this->vehicles_.push_back(VehicleFactory::createCar(x_start_1, y_start_1, this->cellSize_, this->roads_, "East"));
                    }
                    else {
                        this->vehicles_.push_back(VehicleFactory::createCar(x_start_2, y_start_2, this->cellSize_, this->roads_, "West"));
                    }
                }
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
            if (this->roads_.back().getGlobalBounds().contains(vehicle->getShape().getPosition()) || this->roads_.at(this->roads_.size()-2).getGlobalBounds().contains(vehicle->getShape().getPosition())) {
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
            for (sf::RectangleShape exit_site : this->cityExitSite_) {
                if (exit_site.getGlobalBounds().contains(vehicle->getShape().getPosition())) {
                    this->vehicles_.erase(vehicles_.begin() + i);
                    return;
                }
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
