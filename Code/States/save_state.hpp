/**
 * save_state.hpp
 * Header of SaveState class.
 */


#pragma once
#include "SFML/Graphics.hpp"
#include <iostream>
#include <fstream>
#include "state.hpp"
#include "../simulator.hpp"
#include "../components/button.hpp"
#include "../components/cell.hpp"
#include "../helpers/file_finder.hpp"


namespace zpr {

    /**
     *  Class responsible for saving to file state. In this state we can save our map to file.
     */
    class SaveState : public State{
    public:
        SaveState(SimulatorDataRef data, std::vector<Cell> cells, int grid_size);

        void init();
        void handleInput();
        void update(float dt);
        void draw(float dt);
        
    private:
        
        void buttonsInitializer();
        void saveToFile(int number);
        SimulatorDataRef data_;
        sf::Sprite background_;
        std::vector<Button> buttons_;
        std::vector<Cell> cells_;
        std::string slots_[4];
        FileFinder fileFinder_;
        int gridsize_;
    
    };
}
