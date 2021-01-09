#include <sstream>
#include <iostream>

#include "main_menu_state.hpp"
#include "Definitions.hpp"
#include "input_manager.hpp"
#include "init_create_state.hpp"
#include "load_state.hpp"
#include "creator_state.hpp"

namespace ZPR{

    MainMenuState::MainMenuState(SimulatorDataRef data) : _data(data){
    }
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
                    if (button.getText() == "Load city from file")
                    {
                        this->_data->machine.AddState(StateRef(new LoadState(this->_data)), false);
                    }
                    if (button.getText() == "Open demo project")
                    {
                        LoadDemo();
                        
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

    void MainMenuState::LoadDemo(){
        std::string fileName = "Demo.txt";
        std::ifstream myfile;
        if (_fileFinder.CheckIfFileExist(fileName)){
        myfile.open ("Demo.txt");
        myfile >> _gridSize;
        int howMany = 0;
        while (myfile >> this->_tempCell)
        {
            _cells.emplace_back(_tempCell);
            howMany++;
        }
        myfile.close();
        std::cout<<howMany<<std::endl;
        this->_data->machine.AddState(StateRef(new CreatorState(this->_data, this->_gridSize, this->_cells)), false);
        }
        else{
            std::cout<<"Can't open demo file"<<std::endl;
        }
    }
}

