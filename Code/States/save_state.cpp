/**
 * save_state.cpp
 * Implementation of SaveState class.
 */

#include "save_state.hpp"
#include "../definitions.hpp"
#include "creator_state.hpp"
#include <iostream>
#include <memory>
#include <string>


namespace zpr {

    /**
     * Parametrized constructor of SaveState class.
     * @param data - Struct containing data of current application. (eg. window, assets)
     * @param cells - Vector of cells containing roads.
     * @param grid_size - Size of the grid to save.
     */
    SaveState::SaveState(SimulatorDataRef data, std::vector<Cell> cells, int grid_size) : data_(data), cells_(cells), gridsize_(grid_size){}

    /**
     * Methods which initializes all elements in the current state to display it properly.
     */
    void SaveState::init() {
        this->data_->assets_.loadTexture("Background", MENU_BACKGROUND_FILEPATH);
        this->data_->assets_.loadTexture("Button", BUTTON_FILEPATH);
        this->data_->assets_.loadFont("Text font", TEXT_FONT_FILEPATH);
        this->buttonsInitializer();
        this->background_.setTexture(this->data_->assets_.getTexture("Background"));
        this->background_.scale(2.35, 2);
        this->data_->window_.setView(sf::View(sf::FloatRect(0.f, 0.f, (float)(SCREEN_WIDTH), (float)(SCREEN_HEIGHT))));
    }
    
    /**
     Method which handles user input in the current state.
     */
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
                                                      
    /**
     * Method which initializes every button in the window.
     */
    void SaveState::buttonsInitializer(){
        this->fileFinder_.checkSlots(this->slots_);
        sf::Vector2f buttons_size(150, 66);
        int font_size = 30;
        this->buttons_.push_back(Button(sf::Vector2f(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 - 5 * buttons_size.y), buttons_size, slots_[0],
            this->data_->assets_.getFont("Text font"), font_size, sf::Color::White, this->data_->assets_.getTexture("Button")));
        
        this->buttons_.push_back(Button(sf::Vector2f(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 - 3 * buttons_size.y), buttons_size, slots_[1],
            this->data_->assets_.getFont("Text font"), font_size, sf::Color::White, this->data_->assets_.getTexture("Button")));
        
        this->buttons_.push_back(Button(sf::Vector2f(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 - 1 * buttons_size.y), buttons_size, slots_[2],
            this->data_->assets_.getFont("Text font"), font_size, sf::Color::White, this->data_->assets_.getTexture("Button")));
        this->buttons_.push_back(Button(sf::Vector2f(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + 1 * buttons_size.y), buttons_size, slots_[3],
            this->data_->assets_.getFont("Text font"), font_size, sf::Color::White, this->data_->assets_.getTexture("Button")));
        
        this->buttons_.push_back(Button(sf::Vector2f(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + 5 * buttons_size.y), buttons_size, "Back",
            this->data_->assets_.getFont("Text font"), font_size, sf::Color::White, this->data_->assets_.getTexture("Button")));
        
    }

   

    /**
     * Method which saves data to specified file.
     * @param number - Number of slot to save.
     */
    void SaveState::saveToFile(int number){
        std::ofstream file;
        file.open("Map"+std::to_string(number)+".txt");
        file << gridsize_ <<std::endl;
        for (Cell& cell : cells_){
            file << cell;
        }
        file.close();
        this->buttonsInitializer();
    }

    /**
     * Method which updates the window.
     * @param dt - Frequency of updating.
     */
    void SaveState::update(float dt) {

    }

    /**
     * Methods which draws elements of state on the screen.
     * @param dt - Frequency of drawing.
     */
    void SaveState::draw(float dt) {
        this->data_->window_.clear(sf::Color::Black);
        this->data_->window_.draw(this->background_);
        for (Button button : this->buttons_) {
            this->data_->window_.draw(button);
        }
        this->data_->window_.display();
    }
}

                                                     
