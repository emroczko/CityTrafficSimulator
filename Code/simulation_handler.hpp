/**
 * simulation_handler.hpp
 * Header of SimulatonHandler class.
 */

#pragma once
#include "simulation_subject.hpp"
#include "cameras_observer.hpp"
#include "creator_observer.hpp"
#include "Vehicles/vehicle_factory.hpp"
#include <memory>
#include "timer.hpp"
#include "cell.hpp"
#include "camera.hpp"


namespace zpr {

    /**
     * Class responsible for handling simulation of traffic in the application.
     */
    class SimulationHandler : public SimulationSubject, public CamerasObserver, public CreatorObserver{
    public:
        SimulationHandler(int grid_size, std::vector<Cell> cells);
        void init();
        void updateIsSimulating();
        void updateSelectedCell(sf::Vector2i coords) {};
        void updateCells(std::vector<Cell> cells);
        void updateEnterCells(std::vector<Cell> enter_cells);
        void saveToFile();
        void updateIsDrawingRoad(bool is_drawing_road) {};
        void updateIsDeletingRoad(bool is_deleting_road) {};
        void updateIsAddingCamera(bool is_adding_camera, int which_camera) {};
        void updateIsAddingCamera(int which_camera) {}
        void updateCameraAdded(int which_camera, int row, int col) {}
        void updateIsDeletingCamera(int which_camera) {}
        void handleInput();
    private:
        Timer startSimulationTimer_, clearDataTimer_;
        int calculatePrefix();
        void addCarsToSimulate();
        void addStartingRoad();
        void moveVehicles();
        void vehiclesColision();
        void checkCameraVision();
        void checkCameraColision(Camera camera);
        void checkVehicleTypeAndNotify(std::shared_ptr<Vehicle> vehicle, int camera_number);
        bool startingCellFree();
        void deleteVehicles();
        void separateUserRoadsFromCells();
        void separateRoadsFromCells(Cell& cell);
        void separateEnterRoadsFromCells();
        void separateCamerasFromCells();
        sf::RectangleShape convertCellToCenteredRectShape(Cell cell);
        bool isSimulating_;
        int gridSize_, cellSize_;
        int roadSize_, sidewalkSize_, roadStripesSize_;
        sf::RectangleShape cityExitSite_;
        std::vector<Cell> cells_, enterCells_;
        std::vector<sf::RectangleShape> roads_;
        std::vector<Camera> cameras_;
        std::vector<std::shared_ptr<Vehicle>> vehicles_;
    };
}
