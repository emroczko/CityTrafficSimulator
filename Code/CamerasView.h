#pragma once
#include "Simulator.h"
#include "Definitions.h"

namespace ZPR{
	class CamerasView
	{
	public:
		CamerasView(SimulatorDataRef data);
		void Draw();
	private:
		sf::FloatRect CalculateViewPort();
		void DrawButtons();
		SimulatorDataRef _data;
		sf::RectangleShape _background;
		sf::View _camerasView;
	};
};

