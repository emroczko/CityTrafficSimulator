#include "vehicle_factory.hpp"
namespace zpr {
    std::shared_ptr<Vehicle> zpr::VehicleFactory::createCar(int x, int y, int cell_size, std::vector<sf::RectangleShape> roads)
    {
        return std::shared_ptr<Vehicle>(new Car(x, y, cell_size, roads));
    }

    std::shared_ptr<Vehicle> VehicleFactory::createTruck(int x, int y, int cell_size, std::vector<sf::RectangleShape> roads)
    {
        return std::shared_ptr<Vehicle>(new Truck(x, y, cell_size, roads));
    }
}
