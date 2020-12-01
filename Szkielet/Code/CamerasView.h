#pragma once
#include "Simulator.h"
#include "Definitions.h"
#include "Button.h"

namespace ZPR{
	class CamerasView
	{
	public:
		CamerasView(SimulatorDataRef data);
		void Draw();
        void DrawButtons();
	private:
        std::vector<Button> _buttons;
		sf::FloatRect CalculateViewPort();
		SimulatorDataRef _data;
		sf::RectangleShape _background;
		sf::View _camerasView;
	};
};

