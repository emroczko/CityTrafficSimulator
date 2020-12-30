#pragma once
#include "Simulator.h"
#include "Definitions.h"
#include "Button.h"
#include "CamerasSubject.h"

namespace ZPR{
class CamerasView : public CamerasSubject{
	public:
		CamerasView(SimulatorDataRef data);
		void Draw();
        void DrawButtons();
        bool isClicked(sf::Vector2i &mousePosition);
        void HandleInput();
	private:
        std::vector<Button> _buttons;
		sf::FloatRect CalculateViewPort();
		SimulatorDataRef _data;
		sf::RectangleShape _background;
		sf::View _camerasView;
        bool _isSimulating;
	};
};

