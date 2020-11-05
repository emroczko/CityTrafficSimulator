#pragma once

#include <SFML/Graphics.hpp>
#include "State.h"
#include "Simulator.h"

namespace ZPR {

    class SplashState : public State{
    public:
        SplashState(SimulatorDataRef data);
        
        void Init();
        
        void HandleInput();
        void Update(float dt);
        void Draw(float dt);
        
    private:
        SimulatorDataRef _data;
        
        sf::Clock _clock;
        
        sf::Sprite _background;
    };
}
