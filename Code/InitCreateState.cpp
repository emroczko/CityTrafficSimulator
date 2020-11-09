#include "InitCreateState.h"
#include "Definitions.h"

namespace ZPR {
	InitCreateState::InitCreateState(SimulatorDataRef data) : _data(data) {}

	void InitCreateState::Init() {
		this->_data->assets.LoadTexture("Background", MENU_BACKGROUND_FILEPATH);
		this->_data->assets.LoadTexture("Back button", BACK_BUTTON_FILEPATH);
		this->_data->assets.LoadTexture("Create button", MENU_CREATE_BUTTON_FILEPATH);

		this->_data->assets.LoadFont("Text font", TEXT_FONT_FILEPATH);

		this->_background.setTexture(this->_data->assets.GetTexture("Background"));
		this->_createButton.setTexture(this->_data->assets.GetTexture("Create Button"));
		this->_backButton.setTexture(this->_data->assets.GetTexture("Back button"));

		this->_mapHeightText.setFont(this->_data->assets.GetFont("Text font"));
		this->_mapWidthText.setFont(this->_data->assets.GetFont("Text font"));

		this->_mapHeightText.setCharacterSize(20);
		this->_mapWidthText.setCharacterSize(20);

		this->_mapHeightText.setFillColor(sf::Color::Red);
		this->_mapWidthText.setFillColor(sf::Color::Red);

		this->_mapHeightText.setString("Height");
		this->_mapWidthText.setString("Width");

		this->_backButton.setPosition((SCREEN_WIDTH / 2) - (this->_backButton.getGlobalBounds().width/2),
			(SCREEN_HEIGHT / 2) - (this->_backButton.getGlobalBounds().height/2));

		this->_createButton.setPosition((SCREEN_WIDTH) - (this->_createButton.getGlobalBounds().width / 2),
			(SCREEN_HEIGHT / 2) - (this->_createButton.getGlobalBounds().height / 2));

		this->_mapHeightText.setPosition((SCREEN_WIDTH / 3) - (this->_mapHeightText.getGlobalBounds().width / 2),
			(SCREEN_HEIGHT / 2) - (this->_mapHeightText.getGlobalBounds().height / 3));

		this->_mapWidthText.setPosition((SCREEN_WIDTH / 3) * 2 - (this->_mapWidthText.getGlobalBounds().width / 2),
			(SCREEN_HEIGHT / 2) - (this->_mapWidthText.getGlobalBounds().height / 3));
	}

	void InitCreateState::HandleInput() {
		sf::Event event;
		while (this->_data->window.pollEvent(event)) {
			if (sf::Event::Closed == event.type)
			{
				this->_data->window.close();
			}
		}
	}

	void InitCreateState::Update(float dt) {

	}

	void InitCreateState::Draw(float dt) {
		this->_data->window.clear(sf::Color::Black);
		this->_data->window.draw(this->_background);
		this->_data->window.draw(this->_createButton);
		this->_data->window.draw(this->_backButton);
		this->_data->window.draw(this->_mapHeightText);
		this->_data->window.draw(this->_mapWidthText);
		this->_data->window.display();
	}


}