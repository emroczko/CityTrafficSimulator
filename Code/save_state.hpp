#pragma once
#include "SFML/Graphics.hpp"
#include <iostream>
#include <fstream>
#include "state.hpp"
#include "simulator.hpp"
#include "button.hpp"
#include "file_finder.hpp"
#include "cell.hpp"

namespace zpr {

    class SaveState : public State{
    public:
        SaveState(SimulatorDataRef data, std::vector<Cell> cells, int grid_size);

        void init();
        void handleInput();
        void update(float dt);
        void draw(float dt);
        
    private:
        void checkSlots();
        void buttonsInit();
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
