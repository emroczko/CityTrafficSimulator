#pragma once

#include "SFML/Graphics.hpp"
#include <iostream>
#include <fstream>
#include "State.h"
#include "Simulator.h"
#include "Button.h"
#include "FileFinder.h"
#include "Cell.h"


namespace ZPR{

    class LoadState: public State{
        public:
    
        LoadState(SimulatorDataRef data);        
        
        void Init();
        
        void HandleInput();
        void Update(float dt);
        void Draw(float dt);
        
        void CheckSlots();
        void LoadHandler(int number);
        void LoadFromFile(int number);
        
        private:
        bool _isDemo;
        void CheckIfFileExist(int number);
        SimulatorDataRef _data;
        sf::Sprite _background;
        std::vector<Button> _buttons;
        std::vector<Cell> _cells;
        int _gridSize;
        std::string _slots[4];
        FileFinder _fileFinder;
        Cell _tempCell;
    };
}
