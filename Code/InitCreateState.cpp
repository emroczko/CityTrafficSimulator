#include "InitCreateState.h"
#include "Definitions.h"
#include "MainMenuState.h"
#include "CreatorState.h"
#include <iostream>
#include <memory>

namespace ZPR {
	InitCreateState::InitCreateState(SimulatorDataRef data) : _data(data){}

	void InitCreateState::Init() {
		this->_data->assets.LoadTexture("Background", MENU_BACKGROUND_FILEPATH);
		this->_data->assets.LoadTexture("Back button", BACK_BUTTON_FILEPATH);
		this->_data->assets.LoadTexture("Button", BUTTON_FILEPATH);

		this->_data->assets.LoadFont("Text font", TEXT_FONT_FILEPATH);


		/*_size16Button.setPosition(sf::Vector2f(SCREEN_HEIGHT/2-(100), SCREEN_WIDTH/2-(400)));
        
        _size16Button.ButtonQuickMaker("16 x 16", sf::Vector2f(200, 100), sf::Color::Black, this->_data->assets.GetFont("Text font"), 50, sf::Color::White);

        _size32Button.setPosition(sf::Vector2f(SCREEN_HEIGHT/2-(100), SCREEN_WIDTH/2-(200)));
        
        _size32Button.ButtonQuickMaker("32 x 32", sf::Vector2f(200, 100), sf::Color::Black, this->_data->assets.GetFont("Text font"), 50, sf::Color::White);

        _size64Button.setPosition(sf::Vector2f(SCREEN_HEIGHT/2-(100), SCREEN_WIDTH/2));
        
        _size64Button.ButtonQuickMaker("64 x 64", sf::Vector2f(200, 100), sf::Color::Black, this->_data->assets.GetFont("Text font"), 50, sf::Color::White);

        _backButton.setPosition(sf::Vector2f(SCREEN_HEIGHT/2-(100), SCREEN_WIDTH/2+(400)));
        
        _backButton.ButtonQuickMaker("BACK", sf::Vector2f(200, 100), sf::Color::Black, this->_data->assets.GetFont("Text font"), 50, sf::Color::White);
		*/

		sf::Vector2f buttonSize(150, 66);
		int fontSize = 30;
		this->_buttons.push_back(Button(sf::Vector2f(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 - 3 * buttonSize.y), buttonSize, "16x16",
			this->_data->assets.GetFont("Text font"), fontSize, sf::Color::White, this->_data->assets.GetTexture("Button")));
		
		this->_buttons.push_back(Button(sf::Vector2f(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 - 1 * buttonSize.y), buttonSize, "32x32",
			this->_data->assets.GetFont("Text font"), fontSize, sf::Color::White, this->_data->assets.GetTexture("Button")));
		
		this->_buttons.push_back(Button(sf::Vector2f(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + 1 * buttonSize.y), buttonSize, "64x64",
			this->_data->assets.GetFont("Text font"), fontSize, sf::Color::White, this->_data->assets.GetTexture("Button")));
		
		this->_buttons.push_back(Button(sf::Vector2f(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + 5 * buttonSize.y), buttonSize, "Back",
			this->_data->assets.GetFont("Text font"), fontSize, sf::Color::White, this->_data->assets.GetTexture("Button")));

		this->_background.setTexture(this->_data->assets.GetTexture("Background"));
        this->_background.scale(2.35, 2);
	}

	void InitCreateState::HandleInput() {
		sf::Event event;
		while (this->_data->window.pollEvent(event)) 
		{
			if (sf::Event::Closed == event.type)
			{
				this->_data->window.close();
			}
			for (Button button : this->_buttons)
			{
				if (button.isClicked(sf::Mouse::Left, this->_data->window))
				{
					if (button.getText() != "Back")
					{
						this->_data->machine.AddState(StateRef(new CreatorState(this->_data)), false);
					}
					else
					{
						this->_data->machine.AddState(StateRef(new MainMenuState(this->_data)), false);
					}
				}
			}
        }          
	}

	void InitCreateState::Update(float dt) {

	}

	void InitCreateState::Draw(float dt) {
		this->_data->window.clear(sf::Color::Black);
		this->_data->window.draw(this->_background);
		for (Button button : this->_buttons) {
			this->_data->window.draw(button);
		}
		this->_data->window.display();
	}

}
