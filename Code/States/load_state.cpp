/**
 * load_state.cpp
 * Implementation of LoadState class.
 */

#include "load_state.hpp"
#include "../definitions.hpp"
#include "creator_state.hpp"
#include "main_menu_state.hpp"
#include <iostream>
#include <memory>
#include <string>

namespace zpr {

    /**
     * LoadState parametrized constructor.
     * @param data - Struct containing data of current application. (eg. window, assets)
     */
    LoadState::LoadState(SimulatorDataRef data) : data_(data){}

    
    
    /**
     * Methods which initializes all elements in the current state to display it properly.
     */
    void LoadState::init() {
        this->data_->assets_.loadTexture("Background", MENU_BACKGROUND_FILEPATH);
        this->data_->assets_.loadTexture("Button", BUTTON_FILEPATH);
        this->data_->assets_.loadFont("Text font", TEXT_FONT_FILEPATH);

        this->fileFinder_.checkSlots(this->slots_);
        this->initializeButtons();
        
        this->background_.setTexture(this->data_->assets_.getTexture("Background"));
        this->background_.scale(2.35, 2);
        
        this->data_->window_.setView(sf::View(sf::FloatRect(0.f, 0.f, (float)(SCREEN_WIDTH), (float)(SCREEN_HEIGHT))));
    }
    /**
     * Method which initializes every button in the window.
     */
    void LoadState::initializeButtons(){
        sf::Vector2f button_size(150, 66);
        int font_size = 30;
        this->buttons_.push_back(Button(sf::Vector2f(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 - 5 * button_size.y), button_size, slots_[0],
            this->data_->assets_.getFont("Text font"), font_size, sf::Color::White, this->data_->assets_.getTexture("Button")));
        
        this->buttons_.push_back(Button(sf::Vector2f(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 - 3 * button_size.y), button_size, slots_[1],
            this->data_->assets_.getFont("Text font"), font_size, sf::Color::White, this->data_->assets_.getTexture("Button")));
        
        this->buttons_.push_back(Button(sf::Vector2f(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 - 1 * button_size.y), button_size, slots_[2],
            this->data_->assets_.getFont("Text font"), font_size, sf::Color::White, this->data_->assets_.getTexture("Button")));
        this->buttons_.push_back(Button(sf::Vector2f(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + 1 * button_size.y), button_size, slots_[3],
            this->data_->assets_.getFont("Text font"), font_size, sf::Color::White, this->data_->assets_.getTexture("Button")));
        
        this->buttons_.push_back(Button(sf::Vector2f(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + 5 * button_size.y), button_size, "Back",
            this->data_->assets_.getFont("Text font"), font_size, sf::Color::White, this->data_->assets_.getTexture("Button")));
    }
    
    
    /**
     Method which handles user input in the current state.
     */
    void LoadState::handleInput() {
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
                        this->data_->machine_.addState(StateRef(new MainMenuState(this->data_)), false);
                    }
                    if (button.getText() == slots_[0])
                    {
                        loadHandler(1);
                    }
                    if (button.getText() == slots_[1])
                    {
                        loadHandler(2);
                    }
                    if (button.getText() == slots_[2])
                    {
                        loadHandler(3);
                    }
                    if (button.getText() == slots_[3])
                    {
                        loadHandler(4);
                    }
                }
            }
        }
    }
    /**
     * Methods which handles user input on slots button.
     * @param number - Number of a slot.
     */
    void LoadState::loadHandler(int number){
        if (slots_[number-1] == "Slot 1"){
            std::cout<<"File doesnt exist!"<<std::endl;
        }
        else{
            loadFromFile(number);
        }
    }
    /**
     * Method which loads data from previous saved files.
     * @param number - Number of a slot.
     */
    void LoadState::loadFromFile(int number){
        std::ifstream my_file;
        if (fileFinder_.checkIfFileExist(slots_[number-1])){
        my_file.open (slots_[number-1]);
        my_file >> gridSize_;
        int how_many = 0;
        while (my_file >> tempCell_)
        {
            cells_.emplace_back(tempCell_);
            how_many++;
        }
        my_file.close();
        std::cout<<how_many<<std::endl;
        this->cells_.at(64).isStartingCell_ = true;
        this->cells_.at(4).isStartingCell_ = true;
        this->data_->machine_.addState(StateRef(new CreatorState(this->data_, this->gridSize_, this->cells_)), false);
        }
        else{
            std::cout<<"Slot "+std::to_string(number)+" doesn't exist"<<std::endl;
        }
    }
        
    /**
     * Method which updates the window.
     * @param dt - Frequency of updating. 
     */
    void LoadState::update(float dt) {

    }
    /**
     * Methods which draws elements of state on the screen.
     * @param dt - Frequency of drawing.
     */
    void LoadState::draw(float dt) {
        this->data_->window_.clear(sf::Color::Black);
        this->data_->window_.draw(this->background_);
        for (Button button : this->buttons_) {
            this->data_->window_.draw(button);
        }
        this->data_->window_.display();
    }

    
}
