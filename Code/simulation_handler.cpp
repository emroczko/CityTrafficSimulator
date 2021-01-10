#include "simulation_handler.hpp"
#include <random>
#include "definitions.hpp"

namespace zpr {
    SimulationHandler::SimulationHandler(int gridSize, std::vector<Cell> cells) : isSimulating_(false), gridSize_(gridSize), cells_(cells) { init(); }

    void SimulationHandler::init()
    {
        this->timer_ = Timer();
        this->cellSize_ = (SCREEN_HEIGHT / this->gridSize_);
        this->sidewalkSize_ = round(SIDEWALK_SIZE * cellSize_ / ROAD_IMAGE_SIZE);
        this->roadSize_ = round(ROAD_SIZE * cellSize_ / ROAD_IMAGE_SIZE);
        this->roadStripesSize_ = round(ROAD_STRIPES_SIZE * cellSize_ / ROAD_IMAGE_SIZE);
  
        this->cityExitSite_.setSize(sf::Vector2f((SCREEN_HEIGHT / this->gridSize_) / 2, SCREEN_HEIGHT / this->gridSize_));
        this->cityExitSite_.setOrigin(sf::Vector2f(this->cityExitSite_.getSize().x / 2, this->cityExitSite_.getSize().y / 2));
        sf::Vector2f centeredPositionInPixels = sf::Vector2f(STARTING_CELL_COL * this->cellSize_ + this->calculatePrefix() + this->cellSize_ / 2 , STARTING_CELL_ROW * this->cellSize_ + this->calculatePrefix());
        centeredPositionInPixels.x = centeredPositionInPixels.x + this->cellSize_ / 4;
        centeredPositionInPixels.y = centeredPositionInPixels.y + this->cellSize_ / 2;
        this->cityExitSite_.setPosition(centeredPositionInPixels);
    }
    /**
    Ustawia tryb symulacji
    */
    void SimulationHandler::updateIsSimulating()
    {
        this->isSimulating_ = !this->isSimulating_;
        if (isSimulating_){
            this->separateRoadsFromCells();
            this->separateCamerasFromCells();
            this->timer_.setInterval([&]() {
                this->addCarsToSimulate();
                this->moveVehicles();
                this->deleteVehicles();
                this->notifyVehicles(this->vehicles_);
                this->notifyIsSimulating(this->isSimulating_);
            }, 50);
        }
        else{
            this->timer_.stopTimer();
            this->roads_.clear();
            this->cameras_.clear();
            this->vehicles_.clear();
            this->notifyVehicles(this->vehicles_);
        }
        
    }
    void SimulationHandler::updateCells(std::vector<Cell> cells)
    {
        this->cells_ = cells;
        this->separateCamerasFromCells();
    }

    void SimulationHandler::separateRoadsFromCells()
    {
        for (Cell& cell : cells_) {
            if (cell.containsRoad_) {
                this->roads_.push_back(this->convertCellToCenteredRectShape(cell));
            }    
        }
        this->addStartingRoad();
    }
    void SimulationHandler::separateCamerasFromCells()
    {

        this->cameras_.clear();
        for (Cell& cell : this->cells_) {
            if (cell.containsCamera_) {
                this->cameras_.push_back(Camera(cell.whichCamera_, this->convertCellToCenteredRectShape(cell)));
            }
        }
    }
    sf::RectangleShape SimulationHandler::convertCellToCenteredRectShape(Cell cell)
    {
        sf::RectangleShape rectShape;
        rectShape.setSize(sf::Vector2f(SCREEN_HEIGHT / this->gridSize_, SCREEN_HEIGHT / this->gridSize_));
        rectShape.setOrigin(sf::Vector2f(rectShape.getSize().x / 2, rectShape.getSize().y / 2));
        sf::Vector2f centeredPositionInPixels = sf::Vector2f(cell.getPosition().x * this->cellSize_ + this->calculatePrefix(), cell.getPosition().y * this->cellSize_ + this->calculatePrefix());
        centeredPositionInPixels.x = centeredPositionInPixels.x + this->cellSize_ / 2;
        centeredPositionInPixels.y = centeredPositionInPixels.y + this->cellSize_ / 2;
        rectShape.setPosition(centeredPositionInPixels);
        return rectShape;
    }
    void SimulationHandler::addStartingRoad() {
        sf::RectangleShape road;
        road.setSize(sf::Vector2f(SCREEN_HEIGHT / this->gridSize_, SCREEN_HEIGHT / this->gridSize_));
        road.setOrigin(sf::Vector2f(road.getSize().x / 2, road.getSize().y / 2));
        sf::Vector2f centeredPositionInPixels = sf::Vector2f(STARTING_CELL_COL * this->cellSize_ + this->calculatePrefix(), STARTING_CELL_ROW * this->cellSize_ + this->calculatePrefix());
        centeredPositionInPixels.x = centeredPositionInPixels.x + this->cellSize_ / 2;
        centeredPositionInPixels.y = centeredPositionInPixels.y + this->cellSize_ / 2;
        road.setPosition(centeredPositionInPixels);
        this->roads_.push_back(road);
    }

    int SimulationHandler::calculatePrefix() {
        double cellSizeWithPoint = (double)SCREEN_HEIGHT / gridSize_;
        double theRest = cellSizeWithPoint - this->cellSize_;
        int drawPrefix = theRest * gridSize_ / 2;
        return drawPrefix;
    }
   
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
    void SimulationHandler::moveVehicles()
    {
        for (std::shared_ptr<Vehicle> vehicle : this->vehicles_) {
            vehicle->checkOnWhichCell();
            this->vehilcesColision();
            vehicle->move();
            vehicle->checkTurn();
            this->checkCameraVision();
        }
    }
    void SimulationHandler::vehilcesColision()
    {
        for (std::shared_ptr<Vehicle> vehicle : this->vehicles_) {
            int colisionCounter = 0;
            for (std::shared_ptr<Vehicle> colider : this->vehicles_) {
                if (vehicle->checkColision(colider)) {
                    colisionCounter++;
                }
            }
            if (colisionCounter > 0) {
                vehicle->stopVehicle();
            }
            else {
                vehicle->noColision();
            }
        }
    }
    void SimulationHandler::checkCameraVision()
    {
        for (Camera camera : this->cameras_) {
            this->checkCameraColision(camera);
        }
    }

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


    void SimulationHandler::checkVehicleTypeAndNotify(std::shared_ptr<Vehicle> vehicle, int cameraNumber)
    {
        if (!vehicle->seenByCamera_[cameraNumber-1]) {
            if (vehicle->getShape().getSize().x == vehicle->getShape().getSize().y)
                this->notifyCarsLabel(cameraNumber);
            
            else
                this->notifyTrucksLabel(cameraNumber);
            
        }
    }


    bool SimulationHandler::startingCellFree()
    {
        for (std::shared_ptr<Vehicle> vehicle : this->vehicles_) {
            if (this->roads_.back().getGlobalBounds().contains(vehicle->getShape().getPosition())) {
                return false;
            }   
        }
        return true;
    }
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

    /*Zajmuje sie obs≥ugπ zdarzeÒ (zmiana obecnie zanzczonego pola, dodawanie i usuwanie drÛg)*/
    void SimulationHandler::handleInput()
    {
    
    }
    void SimulationHandler::saveToFile(){
    
    }
}
