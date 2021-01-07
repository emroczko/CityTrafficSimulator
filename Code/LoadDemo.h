#pragma once

#include <iostream>
#include <fstream>
#include "State.h"
#include "Simulator.h"
#include "Cell.h"
#include "FileFinder.h"

namespace ZPR{

    class LoadDemo{
        public:
        LoadDemo(SimulatorDataRef data);
        void LoadFromFile();
        
        private:
        SimulatorDataRef _data;
        std::vector<Cell> _cells;
        int _gridSize;
        FileFinder _fileFinder;
        Cell _tempCell;
        std::string _slots[4];
        
    };
}
