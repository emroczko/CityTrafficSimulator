#pragma once
#include "Simulator.h"
#include "Button.h"
#include "Definitions.h"
#include "ToolsSubject.h"

namespace ZPR {
    class ToolsView : public ToolsSubject{
	public:
		ToolsView(SimulatorDataRef data);
		void Draw();
        bool isClicked(sf::Vector2i &mousePosition);
        sf::View GetView();
        void HandleInput();
	private:
		sf::FloatRect CalculateViewPort();
		void DrawButtons();
		SimulatorDataRef _data;
		std::vector<Button> _buttons;
		sf::RectangleShape _background;
		sf::View _toolsView;
	};

}
