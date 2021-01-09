#pragma once
#include "Simulator.h"
#include "Button.h"
#include "Definitions.h"
#include "ToolsSubject.h"
#include "SimulationObserver.h"
#include "CreatorObserver.h"


namespace ZPR {
    class ToolsView : public ToolsSubject, public SimulationObserver, public CreatorObserver{
	public:
		ToolsView(SimulatorDataRef data);
		void Draw();
        bool isClicked(sf::Vector2i mousePosition);
        sf::View GetView();
        void HandleInput();
        void UpdateIsSimulating(bool isSimulating);
        void UpdateIsAddingCameras(bool isAddingCamera);
		void UpdateVehicles(std::vector<std::shared_ptr<Vehicle>> vehicles) {};
        void UpdateCarsLabel(int whichLabel){}
        void UpdateTrucksLabel(int whichLabel){}
        void UpdateSelectedCell(sf::Vector2i coords) {}
        void UpdateCells(std::vector<Cell> cells) {}
        void SaveToFile() {}
        void UpdateIsDrawingRoad(bool isDrawingRoad) {}
        void UpdateIsDeletingRoad(bool isDeletingRoad) {}
        void UpdateIsAddingCamera(bool isAddingCamera, int whichCamera, int row, int col);
        void UpdateIsDeletingCamera(int whichCamera) {}
	private:
		sf::FloatRect CalculateViewPort();
		void DrawButtons();
		SimulatorDataRef _data;
		std::vector<Button> _buttons;
		sf::RectangleShape _background;
		sf::View _toolsView;
        bool isSimulating, isAddingCameras;
	};

}
