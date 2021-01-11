/**
 * splash_state.cpp
 * Implementation of SplashState class.
 */

#include <sstream>
#include <iostream>
#include "definitions.hpp"
#include "splash_state.hpp"
#include "main_menu_state.hpp"

namespace zpr{

    /**
     * Parametrized constructor of SplashState class.
     * @param data - Struct containing data of current application. (eg. window, assets)
     */
    SplashState::SplashState(SimulatorDataRef data) : data_(data) {}

    /**
     * Methods which initializes all elements in the current state to display it properly.
     */
    void SplashState::init(){
        this->data_->assets_.loadTexture("Splash State Background", SPLASH_SCENE_BACKGROUND_FILEPATH);
        this->background_.setTexture(this -> data_->assets_.getTexture("Splash State Background"));
    }

    /**
     Method which handles user input in the current state.
     */
    void SplashState::handleInput(){
        sf::Event event;
        while (this->data_->window_.pollEvent(event)){
            if(sf::Event::Closed ==event.type)
            {
                this->data_->window_.close();
            }
        }
    }
    /**
     * Method which updates the window.
     * @param dt - Frequency of updating.
     */
    void SplashState::update(float dt){
        if (this->clock_.getElapsedTime().asSeconds() > SPLASH_STATE_SHOW_TIME){
            this->data_->machine_.addState(StateRef(new MainMenuState(data_)), true);
        }
    }

    /**
     * Methods which draws elements of state on the screen.
     * @param dt - Frequency of drawing.
     */
    void SplashState::draw(float dt){
        this->data_->window_.clear(sf::Color::Red);
        this->data_->window_.draw(this->background_);
        this->data_->window_.display();
    }



}


