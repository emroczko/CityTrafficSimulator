/**
 * init_create_state.hpp
 * Header of InitCreateState class.
 */

#pragma once
#include <SFML/Graphics.hpp>
#include "state.hpp"
#include "../simulator.hpp"
#include "../Components/button.hpp"
#include "../Helpers/init_create_state_helper.hpp"

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
		SimulatorDataRef data_;
		sf::Sprite background_;
		std::vector<Button> buttons_;
        InitCreateStateHelper helper_;
	};

}

