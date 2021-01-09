#pragma once
#include "SFML/Graphics.hpp"
#include <iostream>
#include <fstream>
#include "state.hpp"
#include "simulator.hpp"
#include "button.hpp"
#include "file_finder.hpp"
#include "cell.hpp"

namespace ZPR {

    class SaveState : public State{
        public:
        SaveState(SimulatorDataRef data, std::vector<Cell> cells, int gridsize);

        void Init();
        
        void HandleInput();
        void Update(float dt);
        void Draw(float dt);
        private:
        void CheckSlots();
        void ButtonsInit();
        void SaveToFile(int number);
        SimulatorDataRef _data;
        sf::Sprite _background;
        std::vector<Button> _buttons;
        std::vector<Cell> _cells;
        std::string _slots[4];
        FileFinder _fileFinder;
        int _gridsize;
    };
}
