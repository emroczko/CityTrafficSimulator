/**
 * creator_state.cpp
 * Implementation of CreatorState class.
 */

#include <sstream>
#include <iostream>
#include "creator_state.hpp"
#include "definitions.hpp"



namespace zpr {

    /**
     * Parametrized constructor of CreatorState class.
     * @param data - Struct containing data of current application. (eg. window, assets)
     * @param grid_size - Size of grid chosen by user
     */
    CreatorState::CreatorState(SimulatorDataRef data, int grid_size) : data_(data), gridSize_(grid_size) { }
    /**
     * Parametrized constructor of CreatorState class.
     * @param data - Struct containing data of current application. (eg. window, assets)
     * @param grid_size - Size of grid chosen by user
     * @param cells - Vector of cells passed from LoadState or SaveState
     */
    CreatorState::CreatorState(SimulatorDataRef data, int grid_size, std::vector<Cell> cells) : data_(data), gridSize_(grid_size), cells_(cells) {
    }
    
    /**
     * Methods which initializes all elements in the current state to display it properly.
     */
    void CreatorState::init(){
		this->mapView_ = std::make_shared<MapView>(this->data_, this->gridSize_);
		this->toolsView_ = std::make_unique<ToolsView>(this->data_);
        this->camerasView_ = std::make_unique<CamerasView>(this->data_);
        this->creatorHandler_ = std::make_unique<CreatorHandler>(this->gridSize_, this->cells_);
        this->simulationHandler_ = std::make_unique<SimulationHandler>(this->gridSize_);
        this->creatorHandler_->add(this->mapView_);
        this->creatorHandler_->add(this->camerasView_);
        this->creatorHandler_->add(this->toolsView_);
        this->creatorHandler_->add(this->simulationHandler_);
        this->creatorHandler_->init();
        this->simulationHandler_->add(this->mapView_);
        this->simulationHandler_->add(this->toolsView_);
        this->simulationHandler_->add(this->camerasView_);
        
        this->simulationHandler_->init();
        this->toolsView_->add(this->creatorHandler_);
        this->camerasView_->add(this->simulationHandler_);
        this->camerasView_->add(this->creatorHandler_);
    }

    
    /**
     Method which handles user input in the current state.
     */
    void CreatorState::handleInput() {
        sf::Event event;
        while (this->data_->window_.pollEvent(event))
        {
            if (sf::Event::Closed == event.type)
            {
                this->data_->window_.close();
            }
            sf::Vector2i mouse_position = sf::Mouse::getPosition(this->data_->window_);
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                
                if(this->mapView_->isClicked(mouse_position)){
                    sf::Vector2f mouse_position_relative_to_map_view = this->data_->window_.mapPixelToCoords(mouse_position, this->mapView_->getView());
                    this->creatorHandler_->handleInput(this->mapView_->handleInput(mouse_position_relative_to_map_view));
                }
                else if (this->toolsView_->isClicked(mouse_position)) {
                    this->toolsView_->handleInput();
                }
                else if (this->camerasView_->isClicked(mouse_position)) {
                    this->camerasView_->handleInput();
                }
            }
            if (event.type == sf::Event::MouseWheelScrolled) {
                if (event.mouseWheelScroll.delta > 0)
                    {
                        this->mapView_->zoomViewAt(-1.3f);
                }
                if (event.mouseWheelScroll.delta < 0)
                {
                    this->mapView_->zoomViewAt(1.3f);
                    
                }
            }
            
            this->handleKeyboard();
            
        }
    }

    /**
     Method which handles user input from keyboard.
     */
    void CreatorState::handleKeyboard(){
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
            this->mapView_->move(keysEnum::LEFT);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
            this->mapView_->move(keysEnum::RIGHT);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){
            this->mapView_->move(keysEnum::UP);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){
            this->mapView_->move(keysEnum::DOWN);
        }
    }
    /**
     * Method which updates the window.
     * @param dt - Frequency of updating.
     */
    void CreatorState::update(float dt){
        
    }

    /**
     * Methods which draws elements of state on the screen.
     * @param dt - Frequency of drawing.
     */
    void CreatorState::draw(float dt){
        this->data_->window_.clear();
        
        this->camerasView_->draw();
        this->mapView_->draw();
        this->toolsView_->draw();

        this->data_->window_.display();
    }

}
