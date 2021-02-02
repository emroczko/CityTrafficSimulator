/**
 * simulation_observer.hpp
 * Header of SimulatonObserver virtual class.
 */

#pragma once
#include "../vehicles/vehicle.hpp"

namespace zpr {

    /**
     * Virtual class responsible for being an observer for SimulationHandler class.
     */
    class SimulationObserver
    {
    public:
        virtual void updateVehicles(std::vector<std::shared_ptr<Vehicle>> vehicles) {}
        virtual void updateIsSimulating(bool is_simulating) {}
        virtual void updateCarsLabel(int which_label) {}
        virtual void updateTrucksLabel(int which_label) {}
        virtual ~SimulationObserver() {}
    };
}

