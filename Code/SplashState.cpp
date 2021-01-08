#include <sstream>
#include <iostream>

#include "Definitions.h"
#include "SplashState.h"
#include "MainMenuState.h"

namespace ZPR{

    SplashState::SplashState(SimulatorDataRef data) : _data(data) {}

/**
 Metoda odpowiadająca za załadowanie tekstury tła
 */
    void SplashState::Init(){
        this->_data->assets.LoadTexture("Splash State Background", SPLASH_SCENE_BACKGROUND_FILEPATH);
        _background.setTexture(this -> _data->assets.GetTexture("Splash State Background"));
    }

/**
 Metoda odpowiadająca za obsługę użytkownika
 */
    void SplashState::HandleInput(){
        sf::Event event;
        while (this->_data->window.pollEvent(event)){
            if(sf::Event::Closed ==event.type)
            {
                this->_data->window.close();
            }
        }
    }
    
    void SplashState::Update(float dt){
        if (this->_clock.getElapsedTime().asSeconds() > SPLASH_STATE_SHOW_TIME){
            this->_data->machine.AddState(StateRef(new MainMenuState(_data)), true);
        }
    }

/**
 Metoda rysująca obiekty na ekranie
 */
    void SplashState::Draw(float dt){
        this->_data->window.clear(sf::Color::Red);
        this->_data->window.draw(this->_background);
        this->_data->window.display();
    }



}


