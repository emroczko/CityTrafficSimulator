#include "VehicleFactory.h"
namespace ZPR {
    //Zwraca shared_ptr do nowo utworzonego obiektu klasy Car
    std::shared_ptr<Vehicle> ZPR::VehicleFactory::CreateCar(int x, int y, int cellSize, std::vector<sf::RectangleShape> roads)
    {
        return std::shared_ptr<Vehicle>(new Car(x, y, cellSize, roads));
    }
    //Zwraca shared_ptr do nowo utworzonego obiektu klasy Truck
    std::shared_ptr<Vehicle> VehicleFactory::CreateTruck(int x, int y, int cellSize, std::vector<sf::RectangleShape> roads)
    {
        return std::shared_ptr<Vehicle>(new Truck(x, y, cellSize, roads));
    }
}
