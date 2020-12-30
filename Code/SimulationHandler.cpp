#include "SimulationHandler.h"

namespace ZPR {
    SimulationHandler::SimulationHandler(): isSimulating(false){}

    void SimulationHandler::init()
    {
        this->NotifyIsSimulating(this->isSimulating);
    }


/**
Ustawia tryb symulacji
*/
    void SimulationHandler::UpdateIsSimulating()
    {
        this->isSimulating = !this->isSimulating;
        this->NotifyIsSimulating(this->isSimulating);
    }
/*Zajmuje sie obs≥ugπ zdarzeÒ (zmiana obecnie zanzczonego pola, dodawanie i usuwanie drÛg)*/
    void SimulationHandler::HandleInput()
    {
    
    }
    
}
