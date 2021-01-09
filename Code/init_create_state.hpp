#pragma once

#include <SFML/Graphics.hpp>
#include "state.hpp"
#include "simulator.hpp"
#include "button.hpp"



namespace ZPR {
	class InitCreateState : public State{
	public:
		InitCreateState(SimulatorDataRef data);

		void Init();
		void HandleInput();
		void Update(float dt);
		void Draw(float dt);
        

	private:
		int GetGridSizeFromButton(Button);
		int ChangeTextToInt(std::string);
		SimulatorDataRef _data;
		sf::Sprite _background;
		std::vector<Button> _buttons;
	};

}

