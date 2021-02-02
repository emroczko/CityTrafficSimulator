/**
 * simulation_handler.hpp
 * Header of SimulatonHandler class.
 */

#pragma once
#include "subjects/simulation_subject.hpp"
#include "observers/cameras_observer.hpp"
#include "observers/creator_observer.hpp"
#include "vehicles/vehicle_factory.hpp"
#include <memory>
#include "components/timer.hpp"
#include "components/cell.hpp"
#include "components/camera.hpp"
#include "helpers/converter.hpp"
#include "helpers/spawn_points.hpp"


namespace zpr {

    /**
     * Class responsible for handling simulation of traffic in the application.
     */
    class SimulationHandler : public SimulationSubject, public CamerasObserver, public CreatorObserver{
    public:
        SimulationHandler(int grid_size);
        void init();
        void updateIsSimulating();
        void updateCells(std::vector<Cell> cells);
        void updateEnterCells(std::vector<Cell> enter_cells);
        void saveToFile();
        void handleInput();
    private:
        Timer startSimulationTimer_, clearDataTimer_;
        void addCarsToSimulate();
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
        bool isSimulating_;
        int gridSize_, cellSize_;
        int roadSize_, sidewalkSize_, roadStripesSize_;
        std::vector<sf::RectangleShape> cityExitSite_;
        std::vector<Cell> cells_, enterCells_;
        std::vector<sf::RectangleShape> roads_;
        std::vector<Camera> cameras_;
        std::vector<std::shared_ptr<Vehicle>> vehicles_;
        std::unique_ptr<Converter> converter_;
        std::unique_ptr<SpawnPoints> spawnPoints_;
    };
}
