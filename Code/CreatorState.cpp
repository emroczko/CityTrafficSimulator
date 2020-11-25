#include <sstream>
#include <iostream>

#include "CreatorState.h"
#include "Definitions.h"
#include "InputManager.h"

namespace ZPR {
    CreatorState::CreatorState(SimulatorDataRef data, int gridSize) : _data(data), _gridSize(gridSize) { }
    void CreatorState::Init(){
		this->_mapView = std::make_shared<MapView>(this->_data, _gridSize);
		this->_toolsView = std::make_unique<ToolsView>(this->_data);
        this->_camerasView = std::make_unique<CamerasView>(this->_data);
        this->_creatorHandler = std::make_unique<CreatorHandler>(this->_gridSize);
        this->_creatorHandler->add(this->_mapView);
        this->_creatorHandler->init();
    }

    void CreatorState::HandleInput() {
        sf::Event event;
        while (this->_data->window.pollEvent(event))
        {
            if (sf::Event::Closed == event.type)
            {
                this->_data->window.close();
            }
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                sf::Vector2i mousePosition = sf::Mouse::getPosition(this->_data->window);
                sf::Vector2f mousePositionRelativeToView = this->_data->window.mapPixelToCoords(mousePosition, this->_mapView->GetView());
                this->_creatorHandler->HandleInput(this->_mapView->HandleInput(mousePositionRelativeToView));
            }
        }
    }

    void CreatorState::Update(float dt){

    }

    void CreatorState::Draw(float dt){
        this->_data->window.clear();
        
        this->_camerasView->Draw();
        this->_mapView->Draw();
        this->_toolsView->Draw();

        this->_data->window.display();
    }

}
