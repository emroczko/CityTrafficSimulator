#pragma once
#include "SimulationObserver.h"
#include <memory>
#include <vector>
#include "Vehicles/Vehicle.h"

namespace ZPR {
    class SimulationSubject
    {
    public:
        void add(std::shared_ptr<SimulationObserver> obs);
        void NotifyVehicles(std::vector<std::shared_ptr<Vehicle>> vehicles);
        void NotifyIsSimulating(bool isSimulating);
        void NotifyCarsLabel(int whichLabel);
        void NotifyTrucksLabel(int whichLabel);
        virtual ~SimulationSubject() {}
    private:
        std::vector<std::shared_ptr<SimulationObserver> > _observers;
    };
}

