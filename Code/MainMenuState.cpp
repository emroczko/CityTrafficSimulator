#include <sstream>
#include <iostream>

#include "MainMenuState.h"
#include "Definitions.h"
#include "InputManager.h"
#include "InitCreateState.h"

namespace ZPR{

    MainMenuState::MainMenuState(SimulatorDataRef data) : _data(data)
    {

    }
    void MainMenuState::Init(){
        this->_data->assets.LoadTexture("Background", MENU_BACKGROUND_FILEPATH);
        this->_data->assets.LoadTexture("Create Button", MENU_CREATE_BUTTON_FILEPATH);
        this->_data->assets.LoadTexture("Exit Button", MENU_EXIT_BUTTON_FILEPATH);
        
    
        this->_background.setTexture(this->_data->assets.GetTexture("Background"));
        this->_createButton.setTexture(this->_data->assets.GetTexture("Create Button"));
        this->_exitButton.setTexture(this->_data->assets.GetTexture("Exit Button"));
        
        this->_createButton.setPosition((SCREEN_WIDTH/3) - (this->_createButton.getGlobalBounds().width/3), (SCREEN_HEIGHT/4) - (this->_createButton.getGlobalBounds().height/4));
    
        this->_exitButton.setPosition((SCREEN_WIDTH/2) - (this->_exitButton.getGlobalBounds().width/2), (SCREEN_HEIGHT/2) - (this->_exitButton.getGlobalBounds().height/2));
}
    void MainMenuState::HandleInput(){
        sf::Event event;
    
        while ( this->_data->window.pollEvent(event))
        {
            if(sf::Event::Closed == event.type || this->_data->input.isSpriteClicked(this->_exitButton, sf::Mouse::Left, this->_data->window))
            {
                this->_data->window.close();
            }
            if(this->_data->input.isSpriteClicked(this->_createButton, sf::Mouse::Left, this->_data->window))
            {
                std::cout<<"go to main menu"<<std::endl;
                this->_data->machine.AddState(StateRef(new InitCreateState(this->_data)), true);
            }
            
        }
    }
    void MainMenuState::Update(float dt){
    
    }

    void MainMenuState::Draw(float dt){
        this->_data->window.clear();
        this->_data->window.draw(this -> _background);
        this->_data->window.draw(this -> _createButton);
        this->_data->window.draw(this -> _exitButton);
        
        this->_data->window.display();
    }
}

