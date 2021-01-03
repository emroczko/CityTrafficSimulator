#include "SimulationHandler.h"
#include <thread>
#include <random>
#include "Definitions.h"

namespace ZPR {
    SimulationHandler::SimulationHandler(int gridSize) : isSimulating(false), isRunning(false), _gridSize(gridSize) { init(); }

    void SimulationHandler::init()
    {
        this->_cellSize = (SCREEN_HEIGHT / this->_gridSize);
        this->_sidewalkSize = round(SIDEWALK_SIZE * _cellSize / ROAD_IMAGE_SIZE);
        this->_roadSize = round(ROAD_SIZE * _cellSize / ROAD_IMAGE_SIZE);
        this->_roadStripesSize = round(ROAD_STRIPES_SIZE * _cellSize / ROAD_IMAGE_SIZE);
    }
    /**
    Ustawia tryb symulacji
    */
    void SimulationHandler::UpdateIsSimulating()
    {
        this->isSimulating = !this->isSimulating;
        if (isSimulating == false) {
            isRunning = false;
        }
        this->Run();
    }
    void SimulationHandler::UpdateCells(std::vector<Cell> cells)
    {
        this->_cells = cells;
        for (Cell cell : _cells) {
            if (cell._containsRoad) {
                _roads.push_back(cell);
            }
        }
    }
    int SimulationHandler::CalculatePrefix() {
        double cellSizeWithPoint = (double)SCREEN_HEIGHT / _gridSize;
        double theRest = cellSizeWithPoint - this->_cellSize;
        int drawPrefix = theRest * _gridSize / 2;
        return drawPrefix;
    }
    void SimulationHandler::Run()
    {
        if (this->isSimulating && !this->isRunning) {
            this->isRunning = true;
            //std::thread simulation(&SimulationHandler::SimulateCars, this);
            sf::Thread thread(&SimulationHandler::SimulateCars, this);
            thread.launch();
        }
    }
    void SimulationHandler::SimulateCars()
    {
        int x_start = CalculatePrefix() + _cellSize * STARTING_CELL_COL + this->_sidewalkSize + this->_roadSize/2;
        int y_start = CalculatePrefix() + _cellSize * STARTING_CELL_ROW + ROAD_IMAGE_SIZE / 2;
        while (this->isSimulating) {
            std::random_device rng;
            std::mt19937 eng(std::chrono::high_resolution_clock::now().time_since_epoch().count());
            std::uniform_int_distribution<> dist(1, 100);
            int num = dist(eng);
            if (num > 0 && num < 20) {
                if (num > 15) {
                    this->_vehicles.push_back(VehicleFactory::CreateTruck(x_start, y_start));
                }
            }
            else {
                this->_vehicles.push_back(VehicleFactory::CreateCar(x_start, y_start));
            }
            this->NotifyVehicles(this->_vehicles);
            this->MoveVehicles();
        }
    }
    void SimulationHandler::MoveVehicles()
    {
        for (std::shared_ptr<Vehicle> vehicle : this->_vehicles) {
            vehicle->move();
        }
    }
    /*Zajmuje sie obs≥ugπ zdarzeÒ (zmiana obecnie zanzczonego pola, dodawanie i usuwanie drÛg)*/
    void SimulationHandler::HandleInput()
    {
    
    }
}