#include <sstream>
#include <iostream>

#include "MainMenuState.h"
#include "Definitions.h"
#include "InputManager.h"
#include "InitCreateState.h"

namespace ZPR{

    MainMenuState::MainMenuState(SimulatorDataRef data) : _data(data){}
/**
 Metoda inicjalizująca obecny stan, załadowanie czcionek, przycisków, tekstur tła
 */
    void MainMenuState::Init(){
        this->_data->assets.LoadTexture("Background", MENU_BACKGROUND_FILEPATH);
        this->_background.setTexture(this->_data->assets.GetTexture("Background"));
        this->_data->assets.LoadFont("Text font", TEXT_FONT_FILEPATH);
        this->_data->assets.LoadTexture("Button", BUTTON_FILEPATH);

        sf::Vector2f buttonSize(150, 66);
        int fontSize = 30;
        
        
        this->_buttons.push_back(Button(sf::Vector2f(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 - 1 * buttonSize.y), buttonSize, "Create new city",
            this->_data->assets.GetFont("Text font"), fontSize, sf::Color::White, this->_data->assets.GetTexture("Button")));
        
        this->_buttons.push_back(Button(sf::Vector2f(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + 1 * buttonSize.y), buttonSize, "Load city from file",
            this->_data->assets.GetFont("Text font"), fontSize, sf::Color::White, this->_data->assets.GetTexture("Button")));
        
        this->_buttons.push_back(Button(sf::Vector2f(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + 3 * buttonSize.y), buttonSize, "Open demo project",
            this->_data->assets.GetFont("Text font"), fontSize, sf::Color::White, this->_data->assets.GetTexture("Button")));
    
        this->_buttons.push_back(Button(sf::Vector2f(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + 5 * buttonSize.y), buttonSize, "Exit",
            this->_data->assets.GetFont("Text font"), fontSize, sf::Color::White, this->_data->assets.GetTexture("Button")));

        
        this->_background.scale(2.35, 2);
       
}

/**
 Metoda odpowiadająca za obsługę użytkownika
 */
    void MainMenuState::HandleInput(){
        sf::Event event;
    
        while ( this->_data->window.pollEvent(event))
        {
            if(sf::Event::Closed == event.type)
            {
                this->_data->window.close();
            }
            
            for (Button button : this->_buttons)
            {
                if (button.isClicked(sf::Mouse::Left, this->_data->window))
                {
                    if (button.getText() == "Create new city")
                    {
                        this->_data->machine.AddState(StateRef(new InitCreateState(this->_data)), false);
                    }
                    if (button.getText() == "Exit")
                    {
                        this->_data->window.close();
                    }
                    else{
                        
                    }
                }
            }
            
        }
    }
    void MainMenuState::Update(float dt){}

    /**
    Metoda odpowiadająca za rysowanie obiektów na ekranie
    */
    void MainMenuState::Draw(float dt){
        this->_data->window.clear();
        this->_data->window.draw(this -> _background);
        for (Button button : this->_buttons) {
            this->_data->window.draw(button);
        }
        this->_data->window.display();
    }
    unsigned long MainMenuState::GetButtonsAmount(){
        return this->_buttons.size();
    }
}

