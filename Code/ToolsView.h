#pragma once
#include "Simulator.h"
#include "Button.h"
#include "Definitions.h"

namespace ZPR {
	class ToolsView {
	public:
		ToolsView(SimulatorDataRef data);
		void Draw();
	private:
		sf::FloatRect CalculateViewPort();
		void DrawButtons();
		SimulatorDataRef _data;
		std::vector<Button> _buttons;
		sf::RectangleShape _background;
		sf::View _toolsView;
	};

}