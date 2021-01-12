/**
 * cameras_view.hpp
 * Header of CamerasView class.
 */
#pragma once
#include "../simulator.hpp"
#include "../definitions.hpp"
#include "../Components/button.hpp"
#include "../Subjects/cameras_subject.hpp"
#include "../Observers/simulation_observer.hpp"
#include "../Observers/creator_observer.hpp"
#include "../Helpers/viewport_calculator.hpp"
#include "../Vehicles/vehicle.hpp"
#include "../Components/cell.hpp"

namespace zpr{

    /**
     * Class responsible for drawing create, delete, and save buttons, and handle actions from and to that buttons and labels
     * in the left window of the main application window.
     */
    class CamerasView : public CamerasSubject, public SimulationObserver, public CreatorObserver{
	public:
		CamerasView(SimulatorDataRef data);
		void draw();
        bool isClicked(sf::Vector2i &mouse_position);
        void handleInput();
        void updateIsSimulating(bool is_simulating);
        void updateIsDeletingCamera(int which_camera);
        void updateIsAddingCamera(bool is_adding_camera, int which_camera);
        void updateCameraAdded(int which_camera, int row, int col);
        void updateCells(std::vector<Cell> cells);
        void updateCarsLabel(int which_label);
        void updateTrucksLabel(int which_label);
	private:
        void initializeVehiclesCounters();
        void addButtons();
        sf::Text createLabel(std::string text, int y_position);
        void camerasInitialization();
        void drawButtons();
        void drawLabels();
        bool startingRoadConnected();
        void resetCameraCounter(int which_camera);
        std::vector<Button> buttons_, removeButtons_;
		SimulatorDataRef data_;
		sf::RectangleShape background_;
		sf::View camerasView_;
        std::vector<Cell> cells_;
        std::vector<sf::Text> camerasLabels_;
        sf::Text startSimulationLabel_;
        bool isSimulating_, isAddingCamera_;
        std::vector<bool> camerasOn_;
        int numberOfCars_[3], numberOfTrucks_[3];
        ViewportCalculator viewportCalculator_;

	};
};

