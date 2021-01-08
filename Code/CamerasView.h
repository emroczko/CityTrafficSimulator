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
        void CamerasLabels(std::string text, int yPosition);
        void AddButtons();
        void ButtonsHandler(Button button, std::string label, int position, int labelPosition);
	private:
        std::vector<Button> _buttons;
		sf::FloatRect CalculateViewPort();
		SimulatorDataRef _data;
		sf::RectangleShape _background;
		sf::View _camerasView;
        std::vector<sf::Text> _camerasLabels;
        bool _isSimulating;
	};
};

