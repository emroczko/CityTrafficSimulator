#pragma once

#include <SFML/Graphics.hpp>
#include "state.hpp"
#include "simulator.hpp"

namespace ZPR {

/**
 Klasa odpowiadająca za ekran startowy (launch screen)
 */
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
