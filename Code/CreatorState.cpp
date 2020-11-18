#include <sstream>
#include <iostream>

#include "CreatorState.h"
#include "Definitions.h"
#include "InputManager.h"

namespace ZPR {
    CreatorState::CreatorState(SimulatorDataRef data, int gridSize) : _data(data), _gridSize(gridSize) { 
        
    }
    void CreatorState::Init(){
		this->_mapView = std::make_unique<MapView>(this->_data, _gridSize);
		this->_toolsView = std::make_unique<ToolsView>(this->_data);
        this->_camerasView = std::make_unique<CamerasView>(this->_data);
    }

    void CreatorState::HandleInput() {
        sf::Event event;
        while (this->_data->window.pollEvent(event))
        {
            if (sf::Event::Closed == event.type)
            {
                this->_data->window.close();
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
