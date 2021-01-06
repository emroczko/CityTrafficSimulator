#pragma once

#include "SFML/Graphics.hpp"
#include <iostream>
#include <fstream>
#include "State.h"
#include "Simulator.h"
#include "Button.h"


namespace ZPR{

    class LoadState: public State{
        public:
    
        LoadState(SimulatorDataRef data);
        
        
        void Init();
        
        void HandleInput();
        void Update(float dt);
        void Draw(float dt);
        private:
        void CheckIfFileExist(int number);
        SimulatorDataRef _data;
        sf::Sprite _background;
        std::vector<Button> _buttons;
        
    };
}
