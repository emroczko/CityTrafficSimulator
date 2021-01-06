#pragma once

#include "SFML/Graphics.hpp"
#include <iostream>
#include <fstream>
#include "State.h"
#include "Simulator.h"
#include "Button.h"
#include "MapView.h"





namespace ZPR {

    

    class SaveState : public State{
        public:
        SaveState(SimulatorDataRef data, MapView& mapView);
        
        
        void Init();
        
        void HandleInput();
        void Update(float dt);
        void Draw(float dt);
        private:
        void SaveToFile(int number);
        SimulatorDataRef _data;
        sf::Sprite _background;
        std::vector<Button> _buttons;
        MapView _mapView;
    
};
}
