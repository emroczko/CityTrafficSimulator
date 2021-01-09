#pragma once

#include <iostream>
#include <fstream>
#include "state.hpp"
#include "simulator.hpp"
#include "cell.hpp"
#include "file_finder.hpp"

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
