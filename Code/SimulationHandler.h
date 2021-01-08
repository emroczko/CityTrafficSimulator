#pragma once
#include "SimulationSubject.h"
#include "CamerasObserver.h"
#include "CreatorObserver.h"
#include "Vehicles/VehicleFactory.h"
#include <memory>
#include "Timer.h"
#include "Cell.h"


namespace ZPR {
    class SimulationHandler : public SimulationSubject, public CamerasObserver, public CreatorObserver{
    public:
        SimulationHandler(int gridSize, std::vector<Cell> cells);
        void init();
        void UpdateIsSimulating();
        void UpdateSelectedCell(sf::Vector2i coords) {};
        void UpdateCells(std::vector<Cell> cells);
        void SaveToFile();
        void UpdateIsDrawingRoad(bool isDrawingRoad) {};
        void UpdateIsDeletingRoad(bool isDeletingRoad) {};
        void UpdateIsAddingCamera(bool isAddingCamera, int whichCamera) {};
        void UpdateIsDeletingCamera(int whichCamera) {};
        void HandleInput();
    private:
        Timer timer;
        void SeparateRoadsFromCells();
        int CalculatePrefix();
        void AddCarsToSimulate();
        void AddStartingRoad();
        void CheckIfRoadIsBlocked();
        void MoveVehicles();
        void VehilcesColision();
        bool StartingCellFree();
        void DeleteVehicles();
        bool isSimulating;
        int _gridSize, _cellSize;
        int _roadSize, _sidewalkSize, _roadStripesSize;
        sf::RectangleShape _cityExitSite;
        std::vector<Cell> _cells;
        std::vector<sf::RectangleShape> _roads;
        std::vector<std::shared_ptr<Vehicle>> _vehicles;
    };
}
