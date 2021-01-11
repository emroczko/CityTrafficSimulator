/**
 * car.hpp
 * Header of Car class.
 */

#pragma once
#include "SFML/Graphics.hpp"
#include "vehicle.hpp"

namespace zpr {
    
    /**
     * Class responsible for being a car in the simulation, inherited from Vehicle. 
     */
	class Car: public Vehicle
	{
	public:
		Car(int x, int y, int cell_size, std::vector<sf::RectangleShape> roads, std::string direction);
	};
}
