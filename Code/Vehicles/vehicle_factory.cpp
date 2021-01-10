/**
 * vehicle_factory.cpp
 * Implementation of VehicleFactory class.
 */

#include "vehicle_factory.hpp"
namespace zpr {

    /**
     * Method responsible for creating Car objects.
     */
    std::shared_ptr<Vehicle> zpr::VehicleFactory::createCar(int x, int y, int cell_size, std::vector<sf::RectangleShape> roads)
    {
        return std::shared_ptr<Vehicle>(new Car(x, y, cell_size, roads));
    }

    /**
     * Method responsible for creating Truck objects.
     */
    std::shared_ptr<Vehicle> VehicleFactory::createTruck(int x, int y, int cell_size, std::vector<sf::RectangleShape> roads)
    {
        return std::shared_ptr<Vehicle>(new Truck(x, y, cell_size, roads));
    }
}
