#pragma once
#include "Simulator.h"
#include "Button.h"
#include "Definitions.h"
#include "ToolsSubject.h"
#include "SimulationObserver.h"

namespace ZPR {
    class ToolsView : public ToolsSubject, public SimulationObserver{
	public:
		ToolsView(SimulatorDataRef data);
		void Draw();
        bool isClicked(sf::Vector2i mousePosition);
        sf::View GetView();
        void HandleInput();
        void UpdateIsSimulating(bool isSimulating);
		void UpdateVehicles(std::vector<std::shared_ptr<Vehicle>> vehicles) {};
        
	private:
		sf::FloatRect CalculateViewPort();
		void DrawButtons();
		SimulatorDataRef _data;
		std::vector<Button> _buttons;
		sf::RectangleShape _background;
		sf::View _toolsView;
        bool isSimulating;
	};

}
