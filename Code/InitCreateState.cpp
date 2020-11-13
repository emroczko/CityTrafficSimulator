#include "InitCreateState.h"
#include "Definitions.h"
#include "MainMenuState.h"
#include <iostream>
#include <memory>

namespace ZPR {
	InitCreateState::InitCreateState(SimulatorDataRef data) : _data(data){}

	void InitCreateState::Init() {
		this->_data->assets.LoadTexture("Background", MENU_BACKGROUND_FILEPATH);
		this->_data->assets.LoadTexture("Back button", BACK_BUTTON_FILEPATH);
		this->_data->assets.LoadTexture("Sixteen", SIXTEEN_BUTTON_FILEPATH);
		this->_data->assets.LoadTexture("Thirtytwo", THIRTYTWO_BUTTON_FILEPATH);
		this->_data->assets.LoadTexture("Sixtyfour", SIXTYFOUR_BUTTON_FILEPATH);

		this->_data->assets.LoadFont("Text font", TEXT_FONT_FILEPATH);

		this->_background.setTexture(this->_data->assets.GetTexture("Background"));
		this->_backButton.setTexture(this->_data->assets.GetTexture("Back button"));	
		this->_sixteenButton.setTexture(this->_data->assets.GetTexture("Sixteen"));
		this->_thirtytwoButton.setTexture(this->_data->assets.GetTexture("Thirtytwo"));
		this->_sixtyfourButton.setTexture(this->_data->assets.GetTexture("Sixtyfour"));
        this->_background.scale(2.35, 2);

		

		this->_sixteenButton.setPosition((SCREEN_WIDTH / 2) + (this->_sixteenButton.getGlobalBounds().width/2),
			(SCREEN_HEIGHT / 6) - (this->_backButton.getGlobalBounds().height / 2));

		this->_thirtytwoButton.setPosition((SCREEN_WIDTH / 2 + (this->_thirtytwoButton.getGlobalBounds().width/2)),
			(SCREEN_HEIGHT * 1.5 / 6) - (this->_thirtytwoButton.getGlobalBounds().height / 2));

		this->_sixtyfourButton.setPosition((SCREEN_WIDTH / 2) + (this->_sixtyfourButton.getGlobalBounds().width/2),
			(SCREEN_HEIGHT * 2 / 6) - (this->_sixtyfourButton.getGlobalBounds().height / 2));
		
		this->_backButton.setPosition((SCREEN_WIDTH *1.04/ 2) + (this->_backButton.getGlobalBounds().width/2),
			(SCREEN_HEIGHT * 3 / 6) - (this->_backButton.getGlobalBounds().height / 2));
	}

	void InitCreateState::HandleInput() {
		sf::Event event;
		while (this->_data->window.pollEvent(event)) {
			if (sf::Event::Closed == event.type)
			{
				this->_data->window.close();
			}
			if (this->_data->input.isSpriteClicked(this->_backButton, sf::Mouse::Left, this->_data->window)) {
				this->_data->machine.AddState(StateRef(new MainMenuState(this->_data)), false);
			}


			if (this->_data->input.isSpriteClicked(this->_sixteenButton, sf::Mouse::Left, this->_data->window)) {
				// Bêdzie siê powtarza³o wiêc trzeba chyba coœ z tym zrobiæ 
				//Go to game
				//Save chosen 
			}
			if (this->_data->input.isSpriteClicked(this->_thirtytwoButton, sf::Mouse::Left, this->_data->window)) {
				//Go to game
				//Save chosen 
			}
			if (this->_data->input.isSpriteClicked(this->_sixtyfourButton, sf::Mouse::Left, this->_data->window)) {
				//Go to game
				//Save chosen 

			}
		}
	}

	void InitCreateState::Update(float dt) {

	}

	void InitCreateState::Draw(float dt) {
		this->_data->window.clear(sf::Color::Black);
		this->_data->window.draw(this->_background);
		this->_data->window.draw(this->_backButton);
		this->_data->window.draw(this->_sixteenButton);
		this->_data->window.draw(this->_thirtytwoButton);
		this->_data->window.draw(this->_sixtyfourButton);
		this->_data->window.display();
	}


}
