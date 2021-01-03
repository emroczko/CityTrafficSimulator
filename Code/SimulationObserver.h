#pragma once
#include "Vehicles/Vehicle.h"
namespace ZPR {
    class SimulationObserver
    {
    public:
        virtual void UpdateVehicles(std::vector<std::shared_ptr<Vehicle>> vehicles) = 0;
        virtual ~SimulationObserver() {}
    };
}

