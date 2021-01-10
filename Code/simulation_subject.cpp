#include "simulation_subject.hpp"

namespace zpr {
    /*Dodaje obserwatora*/
    void SimulationSubject::add(std::shared_ptr<SimulationObserver> obs)
    {
        this->_observers.push_back(obs);
    }
    void SimulationSubject::notifyVehicles(std::vector<std::shared_ptr<Vehicle>> vehicles)
    {
        for (std::shared_ptr<SimulationObserver> obs : this->_observers) {
            obs->updateVehicles(vehicles);
        }
    }
    void SimulationSubject::notifyIsSimulating(bool is_simulating)
     {
         for (std::shared_ptr<SimulationObserver> obs : this->_observers) {
             obs->updateIsSimulating(is_simulating);
         }
     }
    void SimulationSubject::notifyCarsLabel(int which_label)
     {
         for (std::shared_ptr<SimulationObserver> obs : this->_observers) {
             obs->updateCarsLabel(which_label);
         }
     }
    void SimulationSubject::notifyTrucksLabel(int which_label)
     {
         for (std::shared_ptr<SimulationObserver> obs : this->_observers) {
             obs->updateTrucksLabel(which_label);
         }
     }
}
