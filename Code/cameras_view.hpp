/**
 * cameras_view.hpp
 * Header of CamerasView class.
 */
#pragma once
#include "simulator.hpp"
#include "definitions.hpp"
#include "button.hpp"
#include "cameras_subject.hpp"
#include "simulation_observer.hpp"
#include "creator_observer.hpp"

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
        void updateVehicles(std::vector<std::shared_ptr<Vehicle>> vehicles) {}
        void updateIsSimulating(bool is_simulating);
        void updateIsDeletingCamera(int which_camera);
        void updateIsAddingCamera(bool is_adding_camera, int which_camera);
        void updateCameraAdded(int which_camera, int row, int col);
        void updateSelectedCell(sf::Vector2i coords) {}
        void updateCells(std::vector<Cell> cells) {}
        void saveToFile()  {}
        void updateIsDrawingRoad(bool is_drawing_road) {}
        void updateIsDeletingRoad(bool is_deleting_road) {}
        void updateCarsLabel(int which_label);
        void updateTrucksLabel(int which_label);
	private:
        void initializeVehiclesCounters();
        void addButtons();
        void camerasLabels(std::string text, int y_position);
        void drawButtons();
        sf::FloatRect calculateViewPort();
        std::vector<Button> buttons_, removeButtons_;
		SimulatorDataRef data_;
		sf::RectangleShape background_;
		sf::View camerasView_;
        std::vector<sf::Text> camerasLabels_;
        bool isSimulating_, isAddingCamera_;
        std::vector<bool> camerasOn_;
        int numberOfCars_[3], numberOfTrucks_[3];

	};
};

