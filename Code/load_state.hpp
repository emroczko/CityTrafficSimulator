/**
 * load_state.hpp
 * Header of LoadState class.
 */

#pragma once

#include "SFML/Graphics.hpp"
#include <iostream>
#include <fstream>
#include "state.hpp"
#include "simulator.hpp"
#include "button.hpp"
#include "file_finder.hpp"
#include "cell.hpp"



namespace zpr{

    /**
     *  Class responsible for loading from files state. In this state we can choose from which slot we want to load our map. 
     */
    class LoadState: public State{
    public:
        LoadState(SimulatorDataRef data);
        void init();
        void handleInput();
        void update(float dt);
        void draw(float dt);
        void loadHandler(int number);
        void loadFromFile(int number);
        
    private:
        void initializeButtons();
        bool isDemo_;
        SimulatorDataRef data_;
        sf::Sprite background_;
        std::vector<Button> buttons_;
        std::vector<Cell> cells_;
        int gridSize_;
        std::string slots_[4];
        FileFinder fileFinder_;
        Cell tempCell_;
    };
}
