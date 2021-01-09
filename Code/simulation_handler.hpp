#pragma once
#include "simulation_subject.hpp"
#include "cameras_observer.hpp"
#include "creator_observer.hpp"
#include "Vehicles/vehicle_factory.hpp"
#include <memory>
#include "timer.hpp"
#include "cell.hpp"
#include "camera.hpp"


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
        void UpdateIsAddingCamera(bool isAddingCamera, int whichCamera, int row, int col) {};
        void UpdateIsAddingCamera(int whichCamera) {}
        void UpdateIsDeletingCamera(int whichCamera) {}
        void HandleInput();
    private:
        Timer timer;
        int CalculatePrefix();
        void AddCarsToSimulate();
        void AddStartingRoad();
        void MoveVehicles();
        void VehilcesColision();
        void CheckCameraVision();
        void CheckCameraColision(Camera camera);
        void CheckVehicleTypeAndNotify(std::shared_ptr<Vehicle> vehicle, int cameraNumber);
        bool StartingCellFree();
        void DeleteVehicles();
        void SeparateRoadsFromCells();
        void SeparateCamerasFromCells();
        sf::RectangleShape ConvertCellToCenteredRectShape(Cell cell);
        bool isSimulating;
        int _gridSize, _cellSize;
        int _roadSize, _sidewalkSize, _roadStripesSize;
        sf::RectangleShape _cityExitSite;
        std::vector<Cell> _cells;
        std::vector<sf::RectangleShape> _roads;
        std::vector<Camera> _cameras;
        std::vector<std::shared_ptr<Vehicle>> _vehicles;
    };
}
