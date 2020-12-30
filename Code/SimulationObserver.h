#pragma once

namespace ZPR {
    class SimulationObserver
    {
    public:
        virtual void UpdateIsSimulating(bool isSimulating) = 0;
        virtual ~SimulationObserver() {}
    };
}

