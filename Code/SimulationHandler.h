#pragma once
#include "SimulationSubject.h"
#include "CamerasObserver.h"
#include <memory>

namespace ZPR {
    class SimulationHandler : public SimulationSubject, public CamerasObserver{
    public:
        SimulationHandler();
        void init();
        void UpdateIsSimulating();
        void HandleInput();
    private:
        bool isSimulating;
    };
}
