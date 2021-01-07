#include "LoadState.h"
#include "Definitions.h"
#include "CreatorState.h"
#include "MainMenuState.h"
#include <iostream>
#include <memory>
#include <string>

namespace ZPR {
    LoadState::LoadState(SimulatorDataRef data) : _data(data){}

    
    /*Metoda inicjujπca wszystkie elementy potrzebne do poprawnego dzia≥ania obiektu*/
    void LoadState::Init() {
        this->_data->assets.LoadTexture("Background", MENU_BACKGROUND_FILEPATH);
        this->_data->assets.LoadTexture("Button", BUTTON_FILEPATH);
        this->_data->assets.LoadFont("Text font", TEXT_FONT_FILEPATH);

        this->CheckSlots();
        sf::Vector2f buttonSize(150, 66);
        int fontSize = 30;
        this->_buttons.push_back(Button(sf::Vector2f(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 - 5 * buttonSize.y), buttonSize, _slots[0],
            this->_data->assets.GetFont("Text font"), fontSize, sf::Color::White, this->_data->assets.GetTexture("Button")));
        
        this->_buttons.push_back(Button(sf::Vector2f(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 - 3 * buttonSize.y), buttonSize, _slots[1],
            this->_data->assets.GetFont("Text font"), fontSize, sf::Color::White, this->_data->assets.GetTexture("Button")));
        
        this->_buttons.push_back(Button(sf::Vector2f(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 - 1 * buttonSize.y), buttonSize, _slots[2],
            this->_data->assets.GetFont("Text font"), fontSize, sf::Color::White, this->_data->assets.GetTexture("Button")));
        this->_buttons.push_back(Button(sf::Vector2f(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + 1 * buttonSize.y), buttonSize, _slots[3],
            this->_data->assets.GetFont("Text font"), fontSize, sf::Color::White, this->_data->assets.GetTexture("Button")));
        
        this->_buttons.push_back(Button(sf::Vector2f(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + 5 * buttonSize.y), buttonSize, "Back",
            this->_data->assets.GetFont("Text font"), fontSize, sf::Color::White, this->_data->assets.GetTexture("Button")));
        
        

        this->_background.setTexture(this->_data->assets.GetTexture("Background"));
        this->_background.scale(2.35, 2);
        
        this->_data->window.setView(sf::View(sf::FloatRect(0.f, 0.f, (float)(SCREEN_WIDTH), (float)(SCREEN_HEIGHT))));
    }

    void LoadState::CheckSlots(){
        for (int i = 0; i < 4; i++){
            _slots[i] = _fileFinder.CheckIfFileExist("Map"+std::to_string(i+1)+".txt", i+1);
        }
    }
    /*Obs≥uga zdarzeÒ w oknie*/
    void LoadState::HandleInput() {
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
                    if (button.getText() == "Back")
                    {
                        this->_data->machine.AddState(StateRef(new MainMenuState(this->_data)), false);
                    }
                    if (button.getText() == _slots[0])
                    {
                        LoadHandler(1);
                    }
                    if (button.getText() == _slots[1])
                    {
                        LoadHandler(2);
                    }
                    if (button.getText() == _slots[2])
                    {
                        LoadHandler(3);
                    }
                    if (button.getText() == _slots[3])
                    {
                        LoadHandler(4);
                    }
                }
            }
        }
    }
    void LoadState::LoadHandler(int number){
        if (_slots[number-1] == "Slot 1"){
            std::cout<<"File doesnt exist!"<<std::endl;
        }
        else{
            LoadFromFile(number);
        }
    }
    void LoadState::LoadFromFile(int number){
        std::ifstream myfile;
        myfile.open (_slots[number-1]);
        myfile >> _gridSize;
        int howMany = 0;
        while (myfile >> _tempCell)
        {
            _cells.emplace_back(_tempCell);
            howMany++;
        }
        myfile.close();
        std::cout<<howMany<<std::endl;
        this->_data->machine.AddState(StateRef(new CreatorState(this->_data, this->_gridSize, this->_cells)), false);
    }
    void LoadState::Update(float dt) {

    }
    /*Rysuje elementy okna*/
    void LoadState::Draw(float dt) {
        this->_data->window.clear(sf::Color::Black);
        this->_data->window.draw(this->_background);
        for (Button button : this->_buttons) {
            this->_data->window.draw(button);
        }
        this->_data->window.display();
    }

    
}
