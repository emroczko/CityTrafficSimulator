#include "SimulationSubject.h"

namespace ZPR {
    /*Dodaje obserwatora*/
    void SimulationSubject::add(std::shared_ptr<SimulationObserver> obs)
    {
        this->_observers.push_back(obs);
    }
    void SimulationSubject::NotifyIsSimulating(bool isSimulating)
    {
        for (std::shared_ptr<SimulationObserver> obs : this->_observers) {
            obs->UpdateIsSimulating(isSimulating);
        }
    }
}
