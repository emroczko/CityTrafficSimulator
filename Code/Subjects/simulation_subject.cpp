/**
 * simulation_subject.cpp
 * Implementation of SimulatonSubject class.
 */

#include "simulation_subject.hpp"

namespace zpr {

    
    /**
     * Method which adds observers to vector.
     * @param observer - CreatorHandler class observer.
     */
    void SimulationSubject::add(std::shared_ptr<SimulationObserver> observer)
    {
        this->_observers.push_back(observer);
    }

    /**
     * Method which notifies observers when vector of vehicles has changed.
     * @param vehicles - Updated vector of vehicles.
     */
    void SimulationSubject::notifyVehicles(std::vector<std::shared_ptr<Vehicle>> vehicles)
    {
        for (std::shared_ptr<SimulationObserver> observer : this->_observers) {
            observer->updateVehicles(vehicles);
        }
    }

    /**
     * Method which notifies observers when simulation starts or ends.
     * @param is_simulating - True if simulation starts, false otherwise.
     */
    void SimulationSubject::notifyIsSimulating(bool is_simulating)
    {
        for (std::shared_ptr<SimulationObserver> observer : this->_observers) {
            observer->updateIsSimulating(is_simulating);
        }
    }

    /**
     * Method which notifies observers when label showing how many cars passed under the camera has changed.
     * @param which_label - Label to update number.
     */
    void SimulationSubject::notifyCarsLabel(int which_label)
    {
        for (std::shared_ptr<SimulationObserver> observer : this->_observers) {
            observer->updateCarsLabel(which_label);
        }
    }

    /**
     * Method which notifies observers when label showing how many trucks passed under the camera has changed.
     * @param which_label - Label to update number.
     */
    void SimulationSubject::notifyTrucksLabel(int which_label)
    {
        for (std::shared_ptr<SimulationObserver> observer : this->_observers) {
            observer->updateTrucksLabel(which_label);
        }
    }
}
