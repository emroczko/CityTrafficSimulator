#include "SimulationHandler.h"

namespace ZPR {
    SimulationHandler::SimulationHandler(): isSimulating(false){}

    void SimulationHandler::init()
    {
    }
    /**
    Ustawia tryb symulacji
    */
    void SimulationHandler::UpdateIsSimulating()
    {
        this->isSimulating = !this->isSimulating;
    }
    void SimulationHandler::UpdateCells(std::vector<Cell> cells)
    {
        this->_cells = cells;
        for (Cell cell : _cells) {
            if (cell._containsRoad) {
                _roads.push_back(cell);
            }
        }
    }
    void SimulationHandler::Run()
    {

    }
    /*Zajmuje sie obs≥ugπ zdarzeÒ (zmiana obecnie zanzczonego pola, dodawanie i usuwanie drÛg)*/
    void SimulationHandler::HandleInput()
    {
    
    }
}
