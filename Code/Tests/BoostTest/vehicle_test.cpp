#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>
#include <SFML/Graphics.hpp>
#include "../../Vehicles/vehicle.hpp"
#include "../../Vehicles/Car.hpp"
#include "../../Vehicles/Truck.hpp"


struct VehicleTestFixture {
	VehicleTestFixture()
	{
		initRoads();
		car_ = std::make_unique <zpr::Car>(20, 20, 51, roads, "South");
		truck_ = std::make_unique <zpr::Truck>(20, 20, 51, roads, "South");
		car_->currentRoad_ = std::make_shared<sf::RectangleShape>(roads.at(0));
		truck_->currentRoad_ = std::make_shared<sf::RectangleShape>(roads.at(0));
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
	std::unique_ptr<zpr::Vehicle> car_;
	std::unique_ptr<zpr::Vehicle> truck_;
};

BOOST_FIXTURE_TEST_SUITE(VehicleTest, VehicleTestFixture)

BOOST_AUTO_TEST_CASE(Vehicle_PositionTest) {
	BOOST_CHECK_EQUAL(20, car_->x_);
	BOOST_CHECK_EQUAL(20, car_->y_);
	BOOST_CHECK_EQUAL(20, truck_->x_);
	BOOST_CHECK_EQUAL(20, truck_->y_);
	BOOST_CHECK_EQUAL(20, car_->shape_.getPosition().x);
	BOOST_CHECK_EQUAL(20, car_->shape_.getPosition().y);
	BOOST_CHECK_EQUAL(20, truck_->shape_.getPosition().x);
	BOOST_CHECK_EQUAL(20, truck_->shape_.getPosition().y);
}

BOOST_AUTO_TEST_CASE(Vehicle_SpeedTest) {
	BOOST_CHECK_EQUAL(3, car_->speed_);
	BOOST_CHECK_EQUAL(3, truck_->speed_);
}

BOOST_AUTO_TEST_CASE(Vehicle_RoadsTest) {
	BOOST_CHECK_EQUAL(20, car_->roads_.size());
	BOOST_CHECK_EQUAL(20, truck_->roads_.size());
}

BOOST_AUTO_TEST_CASE(Vehicle_CellSizeTest) {
	BOOST_CHECK_EQUAL(51, car_->cellSize_);
	BOOST_CHECK_EQUAL(51, truck_->cellSize_);
}

BOOST_AUTO_TEST_CASE(Vhicle_RoadSizesTest) {
	BOOST_CHECK_EQUAL(18, car_->roadSize_);
	BOOST_CHECK_EQUAL(18, truck_->roadSize_);
	BOOST_CHECK_EQUAL(3, car_->roadStripesSize_);
	BOOST_CHECK_EQUAL(3, truck_->roadStripesSize_);
	BOOST_CHECK_EQUAL(6, car_->sidewalkSize_);
	BOOST_CHECK_EQUAL(6, truck_->sidewalkSize_);
}

BOOST_AUTO_TEST_CASE(Vhicle_DirectionTest) {
	BOOST_CHECK_EQUAL("South", car_->direction_);
	BOOST_CHECK_EQUAL("South", truck_->direction_);
	BOOST_CHECK_EQUAL("", car_->previousDirection_);
	BOOST_CHECK_EQUAL("", truck_->previousDirection_);
}

BOOST_AUTO_TEST_CASE(Vehicle_SizeTest) {
	BOOST_CHECK_EQUAL(14, car_->shape_.getSize().x);
	BOOST_CHECK_EQUAL(14, car_->shape_.getSize().y);
	BOOST_CHECK_EQUAL(14, truck_->shape_.getSize().x);
	BOOST_CHECK_EQUAL(20, truck_->shape_.getSize().y);
}

BOOST_AUTO_TEST_CASE(Vehicle_ColisionBoxTest) {
	BOOST_CHECK_EQUAL(14, car_->colisionBox_.getSize().x);
	BOOST_CHECK_EQUAL(14, car_->colisionBox_.getSize().y);
	BOOST_CHECK_EQUAL(14, truck_->colisionBox_.getSize().x);
	BOOST_CHECK_EQUAL(14, truck_->colisionBox_.getSize().y);
}

BOOST_AUTO_TEST_CASE(Vhicle_StopTest) {
	BOOST_CHECK_EQUAL(3, car_->speed_);
	BOOST_CHECK_EQUAL(3, truck_->speed_);
	car_->stopVehicle();
	truck_->stopVehicle();
	BOOST_CHECK_EQUAL(0, car_->speed_);
	BOOST_CHECK_EQUAL(0, truck_->speed_);
}

BOOST_AUTO_TEST_CASE(Vehicle_GoFromStopTest) {
	car_->stopVehicle();
	truck_->stopVehicle();
	BOOST_CHECK_EQUAL(0, car_->speed_);
	BOOST_CHECK_EQUAL(0, truck_->speed_);
	car_->noColision();
	truck_->noColision();
	BOOST_CHECK_EQUAL(3, car_->speed_);
	BOOST_CHECK_EQUAL(3, truck_->speed_);
}

BOOST_AUTO_TEST_CASE(Vehicle_ConstructorCurrntPreviousRoad) {
	BOOST_CHECK_EQUAL(nullptr, car_->currentRoad_);
	BOOST_CHECK_EQUAL(nullptr, car_->previousRoad_);
	BOOST_CHECK_EQUAL(nullptr, truck_->currentRoad_);
	BOOST_CHECK_EQUAL(nullptr, truck_->previousRoad_);
}

BOOST_AUTO_TEST_SUITE(Vehicle_MoveTest)

BOOST_AUTO_TEST_CASE(Vhicle_MoveSouthTest) {
	car_->move();
	truck_->move();
	BOOST_CHECK_EQUAL(car_->currentRoad_->getPosition().x - car_->roadSize_ / 2 - car_->roadStripesSize_, car_->x_);
	BOOST_CHECK_EQUAL(23, car_->y_);
	BOOST_CHECK_EQUAL(truck_->currentRoad_->getPosition().x - truck_->roadSize_ / 2 - truck_->roadStripesSize_, truck_->x_);
	BOOST_CHECK_EQUAL(23, truck_->y_);
	
}

BOOST_AUTO

BOOST_AUTO_TEST_CASE(Vehicle_DontMoveWhenStopped) {
	car_->stopVehicle();
	car_->move();
	BOOST_CHECK_EQUAL(car_->currentRoad_->getPosition().x - car_->roadSize_ / 2 - car_->roadStripesSize_, car_->x_);
	BOOST_CHECK_EQUAL(20, car_->y_);
}



BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE_END()
