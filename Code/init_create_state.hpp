/**
 * init_create_state.hpp
 * Header of InitCreateState class.
 */

#pragma once

#include <SFML/Graphics.hpp>
#include "state.hpp"
#include "simulator.hpp"
#include "button.hpp"



namespace zpr {

    /**
     * Class responsible for state where we can choose size of map.
     */
	class InitCreateState : public State{
	public:
		InitCreateState(SimulatorDataRef data);

		void init();
		void handleInput();
		void update(float dt);
		void draw(float dt);
        

	private:
        void initializeButtons();
		int getGridSizeFromButton(Button);
		int changeTextToInt(std::string);
		SimulatorDataRef data_;
		sf::Sprite background_;
		std::vector<Button> buttons_;
	};

}

