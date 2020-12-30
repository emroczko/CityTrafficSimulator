#include "VehicleFactory.h"
namespace ZPR {
    std::shared_ptr<Vehicle> ZPR::VehicleFactory::CreateCar(int x, int y)
    {
        return std::shared_ptr<Vehicle>(new Car(x, y));
    }

    std::shared_ptr<Vehicle> VehicleFactory::CreateTruck(int x, int y)
    {
        return std::shared_ptr<Vehicle>(new Truck(x, y));
    }
}
