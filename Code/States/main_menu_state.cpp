/**
 * main_menu_state.cpp
 * Implementation of MainMenuState class.
 */


#include <sstream>
#include <iostream>
#include "main_menu_state.hpp"
#include "../definitions.hpp"
#include "init_create_state.hpp"
#include "load_state.hpp"
#include "creator_state.hpp"

namespace zpr{

    /**
     * Parametrized constructor of MainMenuState.
     * @param data - Struct containing data of current application. (eg. window, assets)
     */
    MainMenuState::MainMenuState(SimulatorDataRef data) : data_(data){
    }
    /**
     * Methods which initializes all elements in the current state to display it properly.
     */
    void MainMenuState::init(){
        this->data_->assets_.loadTexture("Background", MENU_BACKGROUND_FILEPATH);
        this->background_.setTexture(this->data_->assets_.getTexture("Background"));
        this->data_->assets_.loadFont("Text font", TEXT_FONT_FILEPATH);
        this->data_->assets_.loadTexture("Button", BUTTON_FILEPATH);

        this->initializeButtons();
        this->background_.scale(2.35, 2);
       
    }
    /**
     * Method which initializes every button in the window.
     */
    void MainMenuState::initializeButtons(){
        sf::Vector2f button_size(200, 66);
        int font_size = 30;
        
        this->buttons_.push_back(Button(sf::Vector2f(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 - 1 * button_size.y), button_size, "Create new city",
            this->data_->assets_.getFont("Text font"), font_size, sf::Color::White, this->data_->assets_.getTexture("Button")));
        
        this->buttons_.push_back(Button(sf::Vector2f(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + 1 * button_size.y), button_size, "Load city from file",
            this->data_->assets_.getFont("Text font"), font_size, sf::Color::White, this->data_->assets_.getTexture("Button")));
        
        this->buttons_.push_back(Button(sf::Vector2f(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + 3 * button_size.y), button_size, "Open demo project",
            this->data_->assets_.getFont("Text font"), font_size, sf::Color::White, this->data_->assets_.getTexture("Button")));
    
        this->buttons_.push_back(Button(sf::Vector2f(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + 5 * button_size.y), button_size, "Exit",
            this->data_->assets_.getFont("Text font"), font_size, sf::Color::White, this->data_->assets_.getTexture("Button")));
        
    }
    /**
     Method which handles user input in the current state.
     */
    void MainMenuState::handleInput(){
        sf::Event event;
    
        while ( this->data_->window_.pollEvent(event))
        {
            if(sf::Event::Closed == event.type)
            {
                this->data_->window_.close();
            }
            
            for (Button button : this->buttons_)
            {
                if (button.isClicked(sf::Mouse::Left, this->data_->window_))
                {
                    if (button.getText() == "Create new city")
                    {
                        this->data_->machine_.addState(StateRef(new InitCreateState(this->data_)), false);
                    }
                    if (button.getText() == "Load city from file")
                    {
                        this->data_->machine_.addState(StateRef(new LoadState(this->data_)), false);
                    }
                    if (button.getText() == "Open demo project")
                    {
                        this->loadDemo();
                    }
                    if (button.getText() == "Exit")
                    {
                        this->data_->window_.close();
                    }
                }
            }
            
        }
    }
    /**
     * Method which updates the window.
     * @param dt - Frequency of updating.
     */
    void MainMenuState::update(float dt){}

    /**
     * Methods which draws elements of state on the screen.
     * @param dt - Frequency of drawing.
     */
    void MainMenuState::draw(float dt){
        this->data_->window_.clear();
        this->data_->window_.draw(this -> background_);
        for (Button button : this->buttons_) {
            this->data_->window_.draw(button);
        }
        this->data_->window_.display();
    }
    
    /**
     * Method which returns amount of buttons.
     * @return - Amount of buttons.
     */
    unsigned long MainMenuState::getButtonsAmount(){
        return this->buttons_.size();
    }
    /**
     * Method which loads demo project from disk.
     */
    void MainMenuState::loadDemo(){
        std::string file_name = "SavedMaps/Demo.txt";
        std::ifstream my_file;
        if (fileFinder_.checkIfFileExist(file_name)){
        my_file.open ("SavedMaps/Demo.txt");
        my_file >> gridSize_;
        int how_many = 0;
        while (my_file >> this->tempCell_)
        {
            cells_.emplace_back(tempCell_);
            how_many++;
        }
        my_file.close();
        //std::cout<<how_many<<std::endl;
        this->cells_.at(4).isStartingCell_ = true;
        this->data_->machine_.addState(StateRef(new CreatorState(this->data_, this->gridSize_, this->cells_)), false);
        }
        else{
            std::cout<<"Can't open demo file"<<std::endl;
        }
    }
}

