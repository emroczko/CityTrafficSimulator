#pragma once
#include "simulator.hpp"
#include "button.hpp"
#include "definitions.hpp"
#include "tools_subject.hpp"
#include "simulation_observer.hpp"
#include "creator_observer.hpp"


namespace zpr {
    class ToolsView : public ToolsSubject, public SimulationObserver, public CreatorObserver{
	public:
		ToolsView(SimulatorDataRef data);
		void draw();
        bool isClicked(sf::Vector2i mouse_position);
        sf::View getView();
        void handleInput();
        void updateIsSimulating(bool is_simulating);
        void updateIsAddingCameras(bool is_adding_camera);
		void updateVehicles(std::vector<std::shared_ptr<Vehicle>> vehicles) {};
        void updateCarsLabel(int which_label){}
        void updateTrucksLabel(int which_label){}
        void updateSelectedCell(sf::Vector2i coords) {}
        void updateCells(std::vector<Cell> cells) {}
        void saveToFile() {}
        void updateIsDrawingRoad(bool is_drawing_road) {}
        void updateIsDeletingRoad(bool is_deleting_road) {}
        void updateIsAddingCamera(bool is_adding_camera, int which_camera, int row, int col);
        void updateIsDeletingCamera(int which_camera) {}
	private:
		sf::FloatRect calculateViewPort();
		void drawButtons();
        void buttonInitializer();
		SimulatorDataRef data_;
		std::vector<Button> buttons_;
		sf::RectangleShape background_;
		sf::View toolsView_;
        bool isSimulating_, isAddingCameras_;
	};

}
