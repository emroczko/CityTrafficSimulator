#pragma once
#include "SimulationSubject.h"
#include "CamerasObserver.h"
#include "CreatorObserver.h"
#include "Vehicles/VehicleFactory.h"
#include <memory>
#include <chrono>
#include "Cell.h"

namespace ZPR {
    class SimulationHandler : public SimulationSubject, public CamerasObserver, public CreatorObserver{
    public:
        SimulationHandler(int gridSize);
        void init();
        void UpdateIsSimulating();
        void UpdateSelectedCell(sf::Vector2i coords) {};
        void UpdateCells(std::vector<Cell> cells);
        void UpdateIsDrawingRoad(bool isDrawingRoad) {};
        void UpdateIsDeletingRoad(bool isDeletingRoad) {};
        void SimulateCars();
        void HandleInput();
    private:
        void SeparateRoadsFromCells();
        int CalculatePrefix();
    
        void MoveVehicles();
        bool isSimulating;
        int _gridSize, _cellSize;
        int _roadSize, _sidewalkSize, _roadStripesSize;
        std::vector<Cell> _cells;
        std::vector<Cell> _roads;
        std::vector<std::shared_ptr<Vehicle>> _vehicles;
    };
}
