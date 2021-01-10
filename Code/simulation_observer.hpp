/**
 * simulation_observer.hpp
 * Header of SimulatonObserver virtual class.
 */

#pragma once
#include "Vehicles/vehicle.hpp"

namespace zpr {

    /**
     * Virtual class responsible for being an observer for SimulationHandler class.
     */
    class SimulationObserver
    {
    public:
        virtual void updateVehicles(std::vector<std::shared_ptr<Vehicle>> vehicles) = 0;
        virtual void updateIsSimulating(bool is_simulating) = 0;
        virtual void updateCarsLabel(int which_label) = 0;
        virtual void updateTrucksLabel(int which_label) = 0;
        virtual ~SimulationObserver() {}
    };
}

