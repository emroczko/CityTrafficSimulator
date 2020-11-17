#include <sstream>
#include <iostream>

#include "CreatorState.h"
#include "Definitions.h"
#include "InputManager.h"

namespace ZPR {
    CreatorState::CreatorState(SimulatorDataRef data) : _data(data) { }
    void CreatorState::Init(){
        this->_data->assets.LoadTexture("Grass Texture", BACKGROUND_TEXTURE_FILEPATH);
        this->_backgroundTexture.setTexture(this->_data->assets.GetTexture("Grass Texture"));
        this->_data->assets.LoadTexture("Button", BUTTON_FILEPATH);

        this->_data->assets.LoadFont("Text font", TEXT_FONT_FILEPATH);

        this->_data->assets.LoadFont("Text font", TEXT_FONT_FILEPATH);

        


    
        this->_manageCamerasView = sf::View(sf::FloatRect(0.f, 0.f, static_cast<float>((this->_data->window.getSize().x - this->_data->window.getSize().y)/2), static_cast<float>(this->_data->window.getSize().y)));
        this->_manageCamerasView.setViewport(sf::FloatRect(0, 0.f, 0.21875, 1.f));
        
        this->_creatorView = sf::View(sf::FloatRect(0.f, 0.f, static_cast<float>(this->_data->window.getSize().y), static_cast<float>(this->_data->window.getSize().y)));
        this->_creatorView.setViewport(sf::FloatRect(0.21875, 0.f, 0.5625, 1.f));
        
        this->_creatorToolsView = sf::View(sf::FloatRect(0.f, 0.f, static_cast<float>((this->_data->window.getSize().x - this->_data->window.getSize().y) / 2), static_cast<float>(this->_data->window.getSize().y)));
        this->_creatorToolsView.setViewport(sf::FloatRect(0.78125, 0.f, 0.21875, 1.f));
        
        this->_backgroundColor.setPosition(0, 0);
        this->_backgroundColor.setSize(sf::Vector2f(_manageCamerasView.getViewport().width*this->_data->window.getSize().x, _manageCamerasView.getViewport().height*this->_data->window.getSize().y));
        
        _backgroundColor.setFillColor(sf::Color(80, 80, 80));

        _toolsButtons.push_back(Button(sf::Vector2f(50, 50), sf::Vector2f(50, 50), this->_data->assets.GetTexture("Button")));
    }

    void CreatorState::HandleInput() {
        sf::Event event;
        while (this->_data->window.pollEvent(event))
        {
            if (sf::Event::Closed == event.type)
            {
                this->_data->window.close();
            }
        }
    }

    void CreatorState::Update(float dt){

    }

    void CreatorState::Draw(float dt){
        this->_data->window.clear();
        
        this->_data->window.setView(_manageCamerasView);
        this->_data->window.draw(_backgroundColor);
		
        this->_data->window.setView(_creatorView);
        this->_data->window.draw(_backgroundTexture);

        this->_data->window.setView(_creatorToolsView);
        this->_data->window.draw(_backgroundColor);
        for (Button button : this->_toolsButtons)
        {
            this->_data->window.draw(button);
        }

        this->_data->window.display();
    }
}
