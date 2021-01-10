/**
 * splash_state.hpp
 * Header of SplashState class.
 */

#pragma once

#include <SFML/Graphics.hpp>
#include "state.hpp"
#include "simulator.hpp"

namespace zpr {

    /**
     * Class responsible for launch screen of application.
     */
    class SplashState : public State{
    public:
        SplashState(SimulatorDataRef data);
        void init();
        void handleInput();
        void update(float dt);
        void draw(float dt);
    private:
        SimulatorDataRef data_;
        sf::Clock clock_;
        sf::Sprite background_;
    };
}
