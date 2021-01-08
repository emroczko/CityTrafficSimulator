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
        void DrawButtons();
        bool isClicked(sf::Vector2i &mousePosition);
        void HandleInput();
        void CamerasLabels(std::string text, int yPosition);
        void AddButtons();
        void ButtonsHandler(Button button, std::string label, int position, int labelPosition);
        void UpdateVehicles(std::vector<std::shared_ptr<Vehicle>> vehicles) {}
        void UpdateIsSimulating(bool isSimulating) {}
        
        void UpdateIsDeletingCamera(int whichCamera);
        void UpdateIsAddingCamera(bool isAddingCamera, int whichCamera);
        void UpdateSelectedCell(sf::Vector2i coords) {}
        void UpdateCells(std::vector<Cell> cells) {}
        void SaveToFile()  {}
        void UpdateIsDrawingRoad(bool isDrawingRoad) {}
        void UpdateIsDeletingRoad(bool isDeletingRoad) {}
       
    
	private:
        std::vector<Button> _buttons;
		sf::FloatRect CalculateViewPort();
		SimulatorDataRef _data;
		sf::RectangleShape _background;
		sf::View _camerasView;
        std::vector<sf::Text> _camerasLabels;
        bool _isSimulating;
        std::vector<bool> _camerasOn;
	};
};

