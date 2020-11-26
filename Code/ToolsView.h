#pragma once
#include "Simulator.h"
#include "Button.h"
#include "Definitions.h"
#include "ButtonsCreatorObserver.h"
//observe subject
namespace ZPR {
    class ToolsView {
	public:
		ToolsView(SimulatorDataRef data);
		void Draw();
        void add(std::shared_ptr<ButtonsCreatorObserver> obs);
        void NotifyCreateHandler();
        void HandleInput();
	private:
		sf::FloatRect CalculateViewPort();
		void DrawButtons();
		SimulatorDataRef _data;
		std::vector<Button> _buttons;
		sf::RectangleShape _background;
		sf::View _toolsView;
        std::vector<std::shared_ptr<ButtonsCreatorObserver> > _observers;
	};

}
