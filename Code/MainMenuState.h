#pragma once

#include <SFML/Graphics.hpp>
#include "State.h"
#include "Simulator.h"

namespace ZPR{

    class MainMenuState : public State{
        
    public:
        MainMenuState (SimulatorDataRef data);
        
        void Init();
        
        void HandleInput();
        void Update(float dt);
        void Draw(float dt);
        
    private:
        SimulatorDataRef _data;
        sf::Sprite _background;
        sf::Sprite _createButton;
        sf::Sprite _exitButton;
        sf::Sprite _loadButton;
        sf::Sprite _demoButton;
        
    };

}
