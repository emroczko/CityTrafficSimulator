#include "SaveState.h"
#include "Definitions.h"
#include "CreatorState.h"
#include <iostream>
#include <memory>
#include <string>

namespace ZPR {
    SaveState::SaveState(SimulatorDataRef data, MapView& mapView) : _data(data), _mapView(mapView){}
    /*Metoda inicjujπca wszystkie elementy potrzebne do poprawnego dzia≥ania obiektu*/
    void SaveState::Init() {
        this->_data->assets.LoadTexture("Background", MENU_BACKGROUND_FILEPATH);
        this->_data->assets.LoadTexture("Button", BUTTON_FILEPATH);
        this->_data->assets.LoadFont("Text font", TEXT_FONT_FILEPATH);

        sf::Vector2f buttonSize(150, 66);
        int fontSize = 30;
        this->_buttons.push_back(Button(sf::Vector2f(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 - 5 * buttonSize.y), buttonSize, "Slot 1",
            this->_data->assets.GetFont("Text font"), fontSize, sf::Color::White, this->_data->assets.GetTexture("Button")));
        
        this->_buttons.push_back(Button(sf::Vector2f(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 - 3 * buttonSize.y), buttonSize, "Slot 2",
            this->_data->assets.GetFont("Text font"), fontSize, sf::Color::White, this->_data->assets.GetTexture("Button")));
        
        this->_buttons.push_back(Button(sf::Vector2f(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 - 1 * buttonSize.y), buttonSize, "Slot 3",
            this->_data->assets.GetFont("Text font"), fontSize, sf::Color::White, this->_data->assets.GetTexture("Button")));
        this->_buttons.push_back(Button(sf::Vector2f(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + 1 * buttonSize.y), buttonSize, "Slot 4",
            this->_data->assets.GetFont("Text font"), fontSize, sf::Color::White, this->_data->assets.GetTexture("Button")));
        
        this->_buttons.push_back(Button(sf::Vector2f(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + 5 * buttonSize.y), buttonSize, "Back",
            this->_data->assets.GetFont("Text font"), fontSize, sf::Color::White, this->_data->assets.GetTexture("Button")));
        
        

        this->_background.setTexture(this->_data->assets.GetTexture("Background"));
        this->_background.scale(2.35, 2);
        
        this->_data->window.setView(sf::View(sf::FloatRect(0.f, 0.f, (float)(SCREEN_WIDTH), (float)(SCREEN_HEIGHT))));
    }
    /*Obs≥uga zdarzeÒ w oknie*/
    void SaveState::HandleInput() {
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
                        this->_data->machine.AddState(StateRef(new CreatorState(this->_data, this->_mapView.getGridSize(), this->_mapView.GetCells())), false);
                    }
                    if (button.getText() == "Slot 1")
                    {
                        this->SaveToFile(1);
                    }
                    if (button.getText() == "Slot 2")
                    {
                        this->SaveToFile(2);
                    }
                    if (button.getText() == "Slot 3")
                    {
                        this->SaveToFile(3);
                    }
                    if (button.getText() == "Slot 4")
                    {
                        this->SaveToFile(4);
                    }
                }
            }
        }
    }
    
    void SaveState::SaveToFile(int number){
        std::ofstream file;
        file.open("Map"+std::to_string(number)+".txt");
        file << this->_mapView;
        file.close();
    }
    void SaveState::Update(float dt) {

    }
    /*Rysuje elementy okna*/
    void SaveState::Draw(float dt) {
        this->_data->window.clear(sf::Color::Black);
        this->_data->window.draw(this->_background);
        for (Button button : this->_buttons) {
            this->_data->window.draw(button);
        }
        this->_data->window.display();
    }

    }
