#pragma once
#include "simulation_observer.hpp"
#include <memory>
#include <vector>
#include "Vehicles/vehicle.hpp"

namespace zpr {
    class SimulationSubject
    {
    public:
        void add(std::shared_ptr<SimulationObserver> obs);
        void notifyVehicles(std::vector<std::shared_ptr<Vehicle>> vehicles);
        void notifyIsSimulating(bool is_simulating);
        void notifyCarsLabel(int which_label);
        void notifyTrucksLabel(int which_label);
        virtual ~SimulationSubject() {}
    private:
        std::vector<std::shared_ptr<SimulationObserver> > _observers;
    };
}

