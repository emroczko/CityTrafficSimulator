#pragma once

#include "SFML/Graphics.hpp"
#include "State.h"
#include "Simulator.h"


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
		sf::Sprite _createButton;
		sf::Sprite _backButton;
		sf::Sprite _sixteenButton;
		sf::Sprite _thirtytwoButton;
		sf::Sprite _sixtyfourButton;
	};

}

