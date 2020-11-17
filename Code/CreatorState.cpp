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

        

    
        this->_manageCamerasView = sf::View(sf::FloatRect(0.f, 0.f, static_cast<float>((this->_data->window.getSize().x - this->_data->window.getSize().y)/2), static_cast<float>(this->_data->window.getSize().y)));
        this->_manageCamerasView.setViewport(sf::FloatRect(0, 0.f, 0.21875, 1.f));
        
        this->_creatorView = sf::View(sf::FloatRect(0.f, 0.f, static_cast<float>(this->_data->window.getSize().y), static_cast<float>(this->_data->window.getSize().y)));
        this->_creatorView.setViewport(sf::FloatRect(0.21875, 0.f, 0.5625, 1.f));
        
        this->_creatorToolsView = sf::View(sf::FloatRect(0.f, 0.f, static_cast<float>(this->_data->window.getSize().x/4), static_cast<float>(this->_data->window.getSize().y)));
        this->_creatorToolsView.setViewport(sf::FloatRect(0.78125, 0.f, 0.21875, 1.f));
        
        this->_leftBackground.setPosition(_manageCamerasView.getViewport().left*this->_data->window.getSize().x-5, _manageCamerasView.getViewport().top*this->_data->window.getSize().y-5);
        this->_leftBackground.setSize(sf::Vector2f(_manageCamerasView.getViewport().width*this->_data->window.getSize().x+10, _manageCamerasView.getViewport().height*this->_data->window.getSize().y+10));
        
        this->_rightBackground.setPosition(_creatorToolsView.getViewport().left*this->_data->window.getSize().x-5, _creatorToolsView.getViewport().top*this->_data->window.getSize().y-5);
        this->_rightBackground.setSize(sf::Vector2f(_creatorToolsView.getViewport().width*this->_data->window.getSize().x+10, _creatorToolsView.getViewport().height*this->_data->window.getSize().y+10));
        
        _leftBackground.setFillColor(sf::Color(80, 80, 80));
        _rightBackground.setFillColor(sf::Color(80, 80, 80));

        
        sf::Vector2f buttonSize(150, 66);
        int fontSize = 30;
        
        this->_buttons.push_back(Button(sf::Vector2f(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 - 3 * buttonSize.y), buttonSize, "Add Camera",
            this->_data->assets.GetFont("Text font"), fontSize, sf::Color::White, this->_data->assets.GetTexture("Button")));
        
        


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
        
        
        this->_data->window.draw(_leftBackground);

        this->_data->window.setView(_creatorView);
        
        
        this->_data->window.draw(_backgroundTexture);

        this->_data->window.setView(_creatorToolsView);
        this->_data->window.draw(_rightBackground);
        
        this->_data->window.display();
    }
}
