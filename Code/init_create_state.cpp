#include "init_create_state.hpp"
#include "definitions.hpp"
#include "main_menu_state.hpp"
#include "creator_state.hpp"
#include <iostream>
#include <memory>

namespace ZPR {
	InitCreateState::InitCreateState(SimulatorDataRef data) : _data(data){}
	/*Metoda inicjuj¹ca wszystkie elementy potrzebne do poprawnego dzia³ania obiektu*/
	void InitCreateState::Init() {
		this->_data->assets.LoadTexture("Background", MENU_BACKGROUND_FILEPATH);
		this->_data->assets.LoadTexture("Button", BUTTON_FILEPATH);
		this->_data->assets.LoadFont("Text font", TEXT_FONT_FILEPATH);

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
	/*Obs³uga zdarzeñ w oknie*/
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
						int gridSize = GetGridSizeFromButton(button);
						this->_data->machine.AddState(StateRef(new CreatorState(this->_data, gridSize)), false);
					}
					else
					{
						this->_data->machine.AddState(StateRef(new MainMenuState(this->_data)), false);
					}
				}
			}
        }          
	}
	/*Zrwaca wielkoœæ siatki w zaleznoœci od wybranego przycisku*/
	int InitCreateState::GetGridSizeFromButton(Button button)
	{
		std::string buttonText = button.getText();
		std::string textTochange = buttonText.substr(0, 2);
		return ChangeTextToInt(buttonText);
	}
	/*Zwraca wartoœæ tekstu z przycisku zmienion¹ na wartoœæ liczbow¹*/
	int InitCreateState::ChangeTextToInt(std::string textToChange) 
	{
		return std::stoi(textToChange, nullptr);
	}

	void InitCreateState::Update(float dt) {

	}
	/*Rysuje elementy okna*/
	void InitCreateState::Draw(float dt) {
		this->_data->window.clear(sf::Color::Black);
		this->_data->window.draw(this->_background);
		for (Button button : this->_buttons) {
			this->_data->window.draw(button);
		}
		this->_data->window.display();
	}

	}
