#include "SimulationHandler.h"
#include <random>
#include "Definitions.h"

namespace ZPR {
    SimulationHandler::SimulationHandler(int gridSize) : isSimulating(false), _gridSize(gridSize) { init(); }

    void SimulationHandler::init()
    {
        this->timer = Timer();
        this->_cellSize = (SCREEN_HEIGHT / this->_gridSize);
        this->_sidewalkSize = round(SIDEWALK_SIZE * _cellSize / ROAD_IMAGE_SIZE);
        this->_roadSize = round(ROAD_SIZE * _cellSize / ROAD_IMAGE_SIZE);
        this->_roadStripesSize = round(ROAD_STRIPES_SIZE * _cellSize / ROAD_IMAGE_SIZE);
  
        this->_cityExitSite.setSize(sf::Vector2f((SCREEN_HEIGHT / this->_gridSize) / 2, SCREEN_HEIGHT / this->_gridSize));
        this->_cityExitSite.setOrigin(sf::Vector2f(this->_cityExitSite.getSize().x / 2, this->_cityExitSite.getSize().y / 2));
        sf::Vector2f centeredPositionInPixels = sf::Vector2f(STARTING_CELL_COL * this->_cellSize + CalculatePrefix() + this->_cellSize / 2 , STARTING_CELL_ROW * this->_cellSize + CalculatePrefix());
        centeredPositionInPixels.x = centeredPositionInPixels.x + this->_cellSize / 4;
        centeredPositionInPixels.y = centeredPositionInPixels.y + this->_cellSize / 2;
        this->_cityExitSite.setPosition(centeredPositionInPixels);
    }
    /**
    Ustawia tryb symulacji
    */
    void SimulationHandler::UpdateIsSimulating()
    {
        this->isSimulating = !this->isSimulating;
        if (isSimulating){
            SeparateRoadsFromCells();
            this->timer.setInterval([&]() {
                AddCarsToSimulate();
                this->MoveVehicles();
                this->DeleteVehicles();
                this->NotifyVehicles(this->_vehicles);
                this->NotifyIsSimulating(this->isSimulating);
            }, 50);
           
        }
        else{
            this->_roads.clear();
            this->_vehicles.clear();
            NotifyVehicles(this->_vehicles);
        }
        
    }
    void SimulationHandler::UpdateCells(std::vector<Cell> cells)
    {
        this->_cells = cells;
    }

    void SimulationHandler::SeparateRoadsFromCells()
    {
        for (Cell cell : _cells) {
            if (cell._containsRoad) {
                sf::RectangleShape road;
                road.setSize(sf::Vector2f(SCREEN_HEIGHT / this->_gridSize, SCREEN_HEIGHT / this->_gridSize));
                road.setOrigin(sf::Vector2f(road.getSize().x / 2, road.getSize().y / 2));
                sf::Vector2f centeredPositionInPixels = sf::Vector2f(cell.GetPosition().x * this->_cellSize + CalculatePrefix(), cell.GetPosition().y * this->_cellSize + CalculatePrefix());
                centeredPositionInPixels.x = centeredPositionInPixels.x + this->_cellSize / 2;
                centeredPositionInPixels.y = centeredPositionInPixels.y + this->_cellSize / 2;
                road.setPosition(centeredPositionInPixels);
                this->_roads.push_back(road);
            }    
        }
        AddStartingRoad();
    }
    void SimulationHandler::AddStartingRoad() {
        sf::RectangleShape road;
        road.setSize(sf::Vector2f(SCREEN_HEIGHT / this->_gridSize, SCREEN_HEIGHT / this->_gridSize));
        road.setOrigin(sf::Vector2f(road.getSize().x / 2, road.getSize().y / 2));
        sf::Vector2f centeredPositionInPixels = sf::Vector2f(STARTING_CELL_COL * this->_cellSize + CalculatePrefix(), STARTING_CELL_ROW * this->_cellSize + CalculatePrefix());
        centeredPositionInPixels.x = centeredPositionInPixels.x + this->_cellSize / 2;
        centeredPositionInPixels.y = centeredPositionInPixels.y + this->_cellSize / 2;
        road.setPosition(centeredPositionInPixels);
        this->_roads.push_back(road);
    }

    void SimulationHandler::CheckIfRoadIsBlocked()
    {
        for (std::shared_ptr<Vehicle> vehicle : this->_vehicles) {
            vehicle->CheckIsStopped();
        }
    }

    int SimulationHandler::CalculatePrefix() {
        double cellSizeWithPoint = (double)SCREEN_HEIGHT / _gridSize;
        double theRest = cellSizeWithPoint - this->_cellSize;
        int drawPrefix = theRest * _gridSize / 2;
        return drawPrefix;
    }
   
    void SimulationHandler::AddCarsToSimulate()
    {
        int x_start = CalculatePrefix() + _cellSize * STARTING_CELL_COL + this->_sidewalkSize + this->_roadSize/4;
        int y_start = CalculatePrefix() + _cellSize * STARTING_CELL_ROW + ROAD_IMAGE_SIZE / 2;

        std::random_device rng;
        std::mt19937 eng(std::chrono::high_resolution_clock::now().time_since_epoch().count());
        std::uniform_int_distribution<> dist(1, 100);
        int num = dist(eng);
        
        if (StartingCellFree() && num > 0 && num < 7 && this->_vehicles.size() < this->_roads.size()/2) {
            if (num > 4) {
            this->_vehicles.push_back(VehicleFactory::CreateTruck(x_start, y_start, this->_cellSize, this->_roads));
            }
            else {
                this->_vehicles.push_back(VehicleFactory::CreateCar(x_start, y_start, this->_cellSize, this->_roads));
            }
        }
        if(!isSimulating){
            timer.stopTimer();
        }

        
    }
    void SimulationHandler::MoveVehicles()
    {
        for (std::shared_ptr<Vehicle> vehicle : this->_vehicles) {
            vehicle->CheckOnWhichCell(this->CalculatePrefix());
            VehilcesColision();
            CheckIfRoadIsBlocked();
            vehicle->move();
            vehicle->CheckTurn();
        }
    }
    void SimulationHandler::VehilcesColision()
    {
        for (std::shared_ptr<Vehicle> vehicle : this->_vehicles) {
            int colisionCounter = 0;
            for (std::shared_ptr<Vehicle> colider : this->_vehicles) {
                if (vehicle->CheckColision(colider)) {
                    colisionCounter++;
                }
            }
            if (colisionCounter > 0) {
                vehicle->StopVehicle();
            }
            else {
                vehicle->NoColision();
            }
        }
    }
    bool SimulationHandler::StartingCellFree()
    {
        for (std::shared_ptr<Vehicle> vehicle : this->_vehicles) {
            if (this->_roads.back().getGlobalBounds().contains(vehicle->getShape().getPosition())) {
                return false;
            }   
        }
        return true;
    }
    void SimulationHandler::DeleteVehicles()
    {
        int i = 0;
        for (std::shared_ptr<Vehicle> vehicle : this->_vehicles) {
            if (this->_cityExitSite.getGlobalBounds().contains(vehicle->getShape().getPosition())) {
                this->_vehicles.erase(_vehicles.begin() + i);
                return;
            }
            i++;
        }
    }
    /*Zajmuje sie obs≥ugπ zdarzeÒ (zmiana obecnie zanzczonego pola, dodawanie i usuwanie drÛg)*/
    void SimulationHandler::HandleInput()
    {
    
    }
    void SimulationHandler::SaveToFile(){
    
    }
}
