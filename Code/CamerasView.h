#pragma once
#include "Simulator.h"
#include "Definitions.h"
#include "Button.h"
#include "CamerasSubject.h"
#include "SimulationObserver.h"
#include "CreatorObserver.h"

namespace ZPR{
class CamerasView : public CamerasSubject, public SimulationObserver, public CreatorObserver{
	public:
		CamerasView(SimulatorDataRef data);
		void Draw();
        bool isClicked(sf::Vector2i &mousePosition);
        void HandleInput();
        void UpdateVehicles(std::vector<std::shared_ptr<Vehicle>> vehicles) {}
        void UpdateIsSimulating(bool isSimulating);
        void UpdateIsDeletingCamera(int whichCamera);
        void UpdateIsAddingCamera(bool isAddingCamera, int whichCamera, int row, int col);
        void UpdateSelectedCell(sf::Vector2i coords) {}
        void UpdateCells(std::vector<Cell> cells) {}
        void SaveToFile()  {}
        void UpdateIsDrawingRoad(bool isDrawingRoad) {}
        void UpdateIsDeletingRoad(bool isDeletingRoad) {}
        void UpdateCarsLabel(int whichLabel);
        void UpdateTrucksLabel(int whichLabel);
	private:
        void InitializeVehiclesCounters();
        void AddButtons();
        void CamerasLabels(std::string text, int yPosition);
        void ButtonsHandler(Button button, std::string label, int position, int labelPosition);
        void DrawButtons();
        std::vector<Button> _buttons, _removeButtons;
		sf::FloatRect CalculateViewPort();
		SimulatorDataRef _data;
		sf::RectangleShape _background;
		sf::View _camerasView;
        std::vector<sf::Text> _camerasLabels;
        bool _isSimulating, _isAddingCamera;
        std::vector<bool> _camerasOn;
        int _numberOfCars[3], _numberOfTrucks[3];
	};
};

