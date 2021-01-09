#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>
#include <SFML/Graphics.hpp>
#include "../../Vehicles/Vehicle.h"
#include "../../Vehicles/Car.h"
#include "../../Vehicles/Truck.h"


struct VehicleTestFixture {
	VehicleTestFixture()
	{
		initRoads();
		Car = std::make_unique <ZPR::Car>(20, 20, 51, roads);
		Truck = std::make_unique <ZPR::Truck>(20, 20, 51, roads);
	}
	void initRoads() {
		for (int i = 0; i < 20; i++) {
			sf::RectangleShape road;
			road.setPosition(sf::Vector2f(i % 4 * 51, i / 4 * 51));
			road.setSize(sf::Vector2f(51, 51));
			roads.push_back(road);
		}
	}
	~VehicleTestFixture() = default;
	std::vector<sf::RectangleShape> roads;
	std::unique_ptr<ZPR::Vehicle> Car;
	std::unique_ptr<ZPR::Vehicle> Truck;
};

BOOST_FIXTURE_TEST_SUITE(VehicleTest, VehicleTestFixture)

BOOST_AUTO_TEST_CASE(Vehicle_PositionTest) {
	BOOST_CHECK_EQUAL(20, Car->_x);
	BOOST_CHECK_EQUAL(20, Car->_y);
	BOOST_CHECK_EQUAL(20, Truck->_x);
	BOOST_CHECK_EQUAL(20, Truck->_y);
	BOOST_CHECK_EQUAL(20, Car->_shape.getPosition().x);
	BOOST_CHECK_EQUAL(20, Car->_shape.getPosition().y);
	BOOST_CHECK_EQUAL(20, Truck->_shape.getPosition().x);
	BOOST_CHECK_EQUAL(20, Truck->_shape.getPosition().y);
}

BOOST_AUTO_TEST_CASE(Vehicle_SpeedTest) {
	BOOST_CHECK_EQUAL(3, Car->_speed);
	BOOST_CHECK_EQUAL(3, Truck->_speed);
}

BOOST_AUTO_TEST_CASE(Vehicle_RoadsTest) {
	BOOST_CHECK_EQUAL(20, Car->_roads.size());
	BOOST_CHECK_EQUAL(20, Truck->_roads.size());
}

BOOST_AUTO_TEST_CASE(Vehicle_CellSizeTest) {
	BOOST_CHECK_EQUAL(51, Car->_cellSize);
	BOOST_CHECK_EQUAL(51, Truck->_cellSize);
}

BOOST_AUTO_TEST_CASE(Vhicle_RoadSizesTest) {
	BOOST_CHECK_EQUAL(18, Car->_roadSize);
	BOOST_CHECK_EQUAL(18, Truck->_roadSize);
	BOOST_CHECK_EQUAL(3, Car->_roadStripesSize);
	BOOST_CHECK_EQUAL(3, Truck->_roadStripesSize);
	BOOST_CHECK_EQUAL(6, Car->_sidewalkSize);
	BOOST_CHECK_EQUAL(6, Truck->_sidewalkSize);
}

BOOST_AUTO_TEST_CASE(Vhicle_DirectionTest) {
	BOOST_CHECK_EQUAL("South", Car->_direction);
	BOOST_CHECK_EQUAL("South", Truck->_direction);
}

BOOST_AUTO_TEST_CASE(Vehicle_SizeTest) {
	BOOST_CHECK_EQUAL(14, Car->_shape.getSize().x);
	BOOST_CHECK_EQUAL(14, Car->_shape.getSize().y);
	BOOST_CHECK_EQUAL(14, Truck->_shape.getSize().x);
	BOOST_CHECK_EQUAL(20, Truck->_shape.getSize().y);
}

BOOST_AUTO_TEST_CASE(Vehicle_ColisionBoxTest) {
	BOOST_CHECK_EQUAL(14, Car->_colisionBox.getSize().x);
	BOOST_CHECK_EQUAL(14, Car->_colisionBox.getSize().y);
	BOOST_CHECK_EQUAL(14, Truck->_colisionBox.getSize().x);
	BOOST_CHECK_EQUAL(14, Truck->_colisionBox.getSize().y);
}

BOOST_AUTO_TEST_CASE(Vhicle_StopTest) {
	BOOST_CHECK_EQUAL(3, Car->_speed);
	BOOST_CHECK_EQUAL(3, Truck->_speed);
	Car->StopVehicle();
	Truck->StopVehicle();
	BOOST_CHECK_EQUAL(0, Car->_speed);
	BOOST_CHECK_EQUAL(0, Truck->_speed);
}

BOOST_AUTO_TEST_CASE(Vehicle_GoFromStopTest) {
	Car->StopVehicle();
	Truck->StopVehicle();
	BOOST_CHECK_EQUAL(0, Car->_speed);
	BOOST_CHECK_EQUAL(0, Truck->_speed);
	Car->NoColision();
	Truck->NoColision();
	BOOST_CHECK_EQUAL(3, Car->_speed);
	BOOST_CHECK_EQUAL(3, Truck->_speed);
}

/*BOOST_AUTO_TEST_CASE(Vhicle_MoveTest) {
	BOOST_CHECK_EQUAL(20, Car->_x);
	BOOST_CHECK_EQUAL(20, Car->_y);
	BOOST_CHECK_EQUAL(20, Truck->_x);
	BOOST_CHECK_EQUAL(20, Truck->_y);
	Car->move();
	Truck->move();
	BOOST_CHECK_EQUAL(23, Car->_x);
	BOOST_CHECK_EQUAL(20, Car->_y);
	BOOST_CHECK_EQUAL(23, Truck->_x);
	BOOST_CHECK_EQUAL(20, Truck->_y);
	Car->StopVehicle();
	Car->move();
	BOOST_CHECK_EQUAL(23, Car->_x);
	BOOST_CHECK_EQUAL(20, Car->_y);
}*/
BOOST_AUTO_TEST_SUITE_END()