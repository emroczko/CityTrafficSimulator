#pragma once
#include "SimulationObserver.h"
#include <memory>
#include <vector>

namespace ZPR {
    class SimulationSubject
    {
    public:
        void add(std::shared_ptr<SimulationObserver> obs);
        void NotifyIsSimulating(bool isSimulating);
        virtual ~SimulationSubject() {}
    private:
        std::vector<std::shared_ptr<SimulationObserver> > _observers;
    };
}

