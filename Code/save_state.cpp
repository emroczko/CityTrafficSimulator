#include "save_state.hpp"
#include "definitions.hpp"
#include "creator_state.hpp"
#include <iostream>
#include <memory>
#include <string>


namespace zpr {
    SaveState::SaveState(SimulatorDataRef data, std::vector<Cell> cells, int grid_size) : data_(data), cells_(cells), gridsize_(grid_size){}
    /*Metoda inicjujπca wszystkie elementy potrzebne do poprawnego dzia≥ania obiektu*/
    void SaveState::init() {
        this->data_->assets_.loadTexture("Background", MENU_BACKGROUND_FILEPATH);
        this->data_->assets_.loadTexture("Button", BUTTON_FILEPATH);
        this->data_->assets_.loadFont("Text font", TEXT_FONT_FILEPATH);
        this->buttonsInit();
        this->background_.setTexture(this->data_->assets_.getTexture("Background"));
        this->background_.scale(2.35, 2);
        this->data_->window_.setView(sf::View(sf::FloatRect(0.f, 0.f, (float)(SCREEN_WIDTH), (float)(SCREEN_HEIGHT))));
    }
    
    /*Obs≥uga zdarzeÒ w oknie*/
    void SaveState::handleInput() {
        sf::Event event;
        while (this->data_->window_.pollEvent(event))
        {
            if (sf::Event::Closed == event.type)
            {
                this->data_->window_.close();
            }
            for (Button button : this->buttons_)
            {
                if (button.isClicked(sf::Mouse::Left, this->data_->window_))
                {
                    if (button.getText() == "Back")
                    {
                        this->data_->machine_.addState(StateRef(new CreatorState(this->data_, this->gridsize_, this->cells_)), false);
                    }
                    if (button.getText() == slots_[0])
                    {
                        this->saveToFile(1);
                    }
                    if (button.getText() == slots_[1])
                    {
                        this->saveToFile(2);
                    }
                    if (button.getText() == slots_[2])
                    {
                        this->saveToFile(3);
                    }
                    if (button.getText() == slots_[3])
                    {
                        this->saveToFile(4);
                    }
                }
            }
        }
    }
                                                      
                                                      
    void SaveState::buttonsInit(){
        this->checkSlots();
        sf::Vector2f buttonSize(150, 66);
        int fontSize = 30;
        this->buttons_.push_back(Button(sf::Vector2f(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 - 5 * buttonSize.y), buttonSize, slots_[0],
            this->data_->assets_.getFont("Text font"), fontSize, sf::Color::White, this->data_->assets_.getTexture("Button")));
        
        this->buttons_.push_back(Button(sf::Vector2f(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 - 3 * buttonSize.y), buttonSize, slots_[1],
            this->data_->assets_.getFont("Text font"), fontSize, sf::Color::White, this->data_->assets_.getTexture("Button")));
        
        this->buttons_.push_back(Button(sf::Vector2f(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 - 1 * buttonSize.y), buttonSize, slots_[2],
            this->data_->assets_.getFont("Text font"), fontSize, sf::Color::White, this->data_->assets_.getTexture("Button")));
        this->buttons_.push_back(Button(sf::Vector2f(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + 1 * buttonSize.y), buttonSize, slots_[3],
            this->data_->assets_.getFont("Text font"), fontSize, sf::Color::White, this->data_->assets_.getTexture("Button")));
        
        this->buttons_.push_back(Button(sf::Vector2f(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + 5 * buttonSize.y), buttonSize, "Back",
            this->data_->assets_.getFont("Text font"), fontSize, sf::Color::White, this->data_->assets_.getTexture("Button")));
        
    }
    void SaveState::checkSlots(){
        for (int i = 0; i < 4; i++){
            slots_[i] = fileFinder_.checkIfFileExist("Map"+std::to_string(i+1)+".txt", i+1);
        }
    }
    void SaveState::saveToFile(int number){
        std::ofstream file;
        file.open("Map"+std::to_string(number)+".txt");
        file << gridsize_ <<std::endl;
        for (Cell& cell : cells_){
            file << cell;
        }
        file.close();
        this->buttonsInit();
    }
    void SaveState::update(float dt) {

    }
    /*Rysuje elementy okna*/
    void SaveState::draw(float dt) {
        this->data_->window_.clear(sf::Color::Black);
        this->data_->window_.draw(this->background_);
        for (Button button : this->buttons_) {
            this->data_->window_.draw(button);
        }
        this->data_->window_.display();
    }
}

                                                     
