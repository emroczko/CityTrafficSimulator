#pragma once

#include <SFML/Graphics.hpp>
#include "State.h"
#include "Simulator.h"
#include "Button.h"

#include <vector>

#include "Button.h"


namespace ZPR{
    
    class CreatorState: public State{
    
    public:
        CreatorState (SimulatorDataRef data);
        
        void Init();
        
        void HandleInput();
        void Update(float dt);
        void Draw(float dt);
    private:
        SimulatorDataRef _data;
        sf::View _manageCamerasView, _creatorView, _creatorToolsView;
        sf::RectangleShape _leftBackground, _rightBackground;
        sf::Sprite _grid;
        sf::Sprite _backgroundTexture;
        std::vector<Button> _buttons;
    };
}
