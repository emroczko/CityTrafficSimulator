/**
 * simulator.hpp
 * Header of Simulator class and SimulatorData structure.
 */

#pragma once

#include <memory>
#include <string>
#include <SFML/Graphics.hpp>

#include "States/state_machine.hpp"
#include "asset_manager.hpp"

namespace zpr{

    /**
     * Structure containing data responsible for an application state.
     */
    struct SimulatorData {
        StateMachine machine_;
        sf::RenderWindow window_;
        AssetManager assets_;
    };
    /**
     * Assigning SimulatorDataRef as a name to std::shared_ptr<SimulatorData> type.
     */
    typedef std::shared_ptr<SimulatorData> SimulatorDataRef;

    /**
     * Class responsible for launching the window and application loop.
     */
    class Simulator{
    public:
        Simulator(int width, int height, std::string title);
    private:
        const float dt_ = 1.0f / 60.0f;
        sf::Clock clock_;
        SimulatorDataRef data_ = std::make_shared<SimulatorData>();
        void run();
    };
 
}
