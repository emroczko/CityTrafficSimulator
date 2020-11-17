#pragma once

#include "SFML/Graphics.hpp"
#include "State.h"
#include "Simulator.h"
#include "Button.h"


namespace ZPR {
	class InitCreateState : public State{
	public:
		InitCreateState(SimulatorDataRef data);

		void Init();
		void HandleInput();
		void Update(float dt);
		void Draw(float dt);
        

	private:
		SimulatorDataRef _data;
		sf::Sprite _background;
		std::vector<Button> _buttons;
	};

}

