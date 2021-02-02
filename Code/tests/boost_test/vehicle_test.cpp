#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>
#include <SFML/Graphics.hpp>
#include "../../vehicles/vehicle.hpp"
#include "../../vehicles/car.hpp"
#include "../../vehicles/truck.hpp"


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
			road.setPosition(sf::Vector2f(i % 4 * 51, i / 5 * 51));
			road.setSize(sf::Vector2f(51, 51));
			roads.push_back(road);
		}
	}
	~VehicleTestFixture() = default;
	std::vector<sf::RectangleShape> roads;
	std::shared_ptr<zpr::Vehicle> car_;
	std::shared_ptr<zpr::Vehicle> truck_;
};

BOOST_FIXTURE_TEST_SUITE(VehicleTest, VehicleTestFixture)

BOOST_AUTO_TEST_CASE(Vehicle_positionTest) {
	BOOST_CHECK_EQUAL(20, car_->x_);
	BOOST_CHECK_EQUAL(20, car_->y_);
	BOOST_CHECK_EQUAL(20, truck_->x_);
	BOOST_CHECK_EQUAL(20, truck_->y_);
	BOOST_CHECK_EQUAL(20, car_->shape_.getPosition().x);
	BOOST_CHECK_EQUAL(20, car_->shape_.getPosition().y);
	BOOST_CHECK_EQUAL(20, truck_->shape_.getPosition().x);
	BOOST_CHECK_EQUAL(20, truck_->shape_.getPosition().y);
}

BOOST_AUTO_TEST_CASE(Vehicle_speedTest) {
	BOOST_CHECK_EQUAL(3, car_->speed_);
	BOOST_CHECK_EQUAL(3, truck_->speed_);
}

BOOST_AUTO_TEST_CASE(Vehicle_roadsTest) {
	BOOST_CHECK_EQUAL(20, car_->roads_.size());
	BOOST_CHECK_EQUAL(20, truck_->roads_.size());
}

BOOST_AUTO_TEST_CASE(Vehicle_cellSizeTest) {
	BOOST_CHECK_EQUAL(51, car_->cellSize_);
	BOOST_CHECK_EQUAL(51, truck_->cellSize_);
}

BOOST_AUTO_TEST_CASE(Vhicle_roadSizesTest) {
	BOOST_CHECK_EQUAL(18, car_->roadSize_);
	BOOST_CHECK_EQUAL(18, truck_->roadSize_);
	BOOST_CHECK_EQUAL(3, car_->roadStripesSize_);
	BOOST_CHECK_EQUAL(3, truck_->roadStripesSize_);
	BOOST_CHECK_EQUAL(6, car_->sidewalkSize_);
	BOOST_CHECK_EQUAL(6, truck_->sidewalkSize_);
}

BOOST_AUTO_TEST_CASE(Vhicle_directionTest) {
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

BOOST_AUTO_TEST_CASE(Vhicle_stopTest) {
	BOOST_CHECK_EQUAL(3, car_->speed_);
	BOOST_CHECK_EQUAL(3, truck_->speed_);
	car_->stopVehicle();
	truck_->stopVehicle();
	BOOST_CHECK_EQUAL(0, car_->speed_);
	BOOST_CHECK_EQUAL(0, truck_->speed_);
}

BOOST_AUTO_TEST_CASE(Vehicle_goFromStopTest) {
	car_->stopVehicle();
	truck_->stopVehicle();
	BOOST_CHECK_EQUAL(0, car_->speed_);
	BOOST_CHECK_EQUAL(0, truck_->speed_);
	car_->noColision();
	truck_->noColision();
	BOOST_CHECK_EQUAL(3, car_->speed_);
	BOOST_CHECK_EQUAL(3, truck_->speed_);
}


BOOST_AUTO_TEST_CASE(Vehicle_constructorCurrntPreviousRoad) {
	BOOST_TEST(car_->currentRoad_);
	BOOST_TEST(!car_->previousRoad_);
	BOOST_TEST(truck_->currentRoad_);
	BOOST_TEST(!truck_->previousRoad_);
}

BOOST_AUTO_TEST_SUITE(Vehicle_moveTest)

BOOST_AUTO_TEST_CASE(Vhicle_moveSouthTest) {
	car_->move();
	truck_->move();
	BOOST_CHECK_EQUAL(car_->currentRoad_->getPosition().x - car_->roadSize_ / 2 - car_->roadStripesSize_, car_->x_);
	BOOST_CHECK_EQUAL(23, car_->y_);
	BOOST_CHECK_EQUAL(truck_->currentRoad_->getPosition().x - truck_->roadSize_ / 2 - truck_->roadStripesSize_, truck_->x_);
	BOOST_CHECK_EQUAL(23, truck_->y_);
	
}

BOOST_AUTO_TEST_CASE(Vehicle_moveNorthTest) {
	car_->direction_ = "North";
	truck_->direction_ = "North";
	car_->move();
	truck_->move();
	BOOST_CHECK_EQUAL(car_->currentRoad_->getPosition().x + car_->roadSize_ / 2 + car_->roadStripesSize_, car_->x_);
	BOOST_CHECK_EQUAL(17, car_->y_);
	BOOST_CHECK_EQUAL(truck_->currentRoad_->getPosition().x + truck_->roadSize_ / 2 + truck_->roadStripesSize_, truck_->x_);
	BOOST_CHECK_EQUAL(17, truck_->y_);
}

BOOST_AUTO_TEST_CASE(Vehicle_moveEastTest) {
	car_->direction_ = "East";
	truck_->direction_ = "East";
	car_->move();
	truck_->move();
	BOOST_CHECK_EQUAL(23, car_->x_);
	BOOST_CHECK_EQUAL(car_->currentRoad_->getPosition().y + car_->roadSize_ / 2 + car_->roadStripesSize_, car_->y_);
	BOOST_CHECK_EQUAL(23, truck_->x_);
	BOOST_CHECK_EQUAL(truck_->currentRoad_->getPosition().y + truck_->roadSize_ / 2 + truck_->roadStripesSize_, truck_->y_);
}

BOOST_AUTO_TEST_CASE(Vehicle_moveWestTest) {
	car_->direction_ = "West";
	truck_->direction_ = "West";
	car_->move();
	truck_->move();
	BOOST_CHECK_EQUAL(17, car_->x_);
	BOOST_CHECK_EQUAL(car_->currentRoad_->getPosition().y - car_->roadSize_ / 2 - car_->roadStripesSize_, car_->y_);
	BOOST_CHECK_EQUAL(17, truck_->x_);
	BOOST_CHECK_EQUAL(truck_->currentRoad_->getPosition().y - truck_->roadSize_ / 2 - truck_->roadStripesSize_, truck_->y_);
}

BOOST_AUTO_TEST_CASE(Vehicle_dontMoveWhenStopped) {
	car_->stopVehicle();
	car_->move();
	BOOST_CHECK_EQUAL(car_->currentRoad_->getPosition().x - car_->roadSize_ / 2 - car_->roadStripesSize_, car_->x_);
	BOOST_CHECK_EQUAL(20, car_->y_);
}
BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_CASE(Vehicle_checkVehicleStoppedTest) {
	BOOST_CHECK_EQUAL(0, car_->stopCounter_);
	car_->checkVehicleStopped();
	BOOST_CHECK_EQUAL(0, car_->stopCounter_);
	car_->stopVehicle();
	car_->checkVehicleStopped();
	BOOST_CHECK_EQUAL(1, car_->stopCounter_);
}

BOOST_AUTO_TEST_CASE(Vehicle_colisionTest) {
	truck_->shape_.setPosition(20, 40);
	BOOST_CHECK_EQUAL(true, car_->checkColision(truck_));
	truck_->shape_.setPosition(100, 100);
	BOOST_CHECK_EQUAL(false, car_->checkColision(truck_));
}

BOOST_AUTO_TEST_CASE(Vehicle_noColisionTest) {
	car_->stopVehicle();
	BOOST_CHECK_EQUAL(0, car_->speed_);
	car_->noColision();
	BOOST_CHECK_EQUAL(3, car_->speed_);
}

BOOST_AUTO_TEST_CASE(Vehicle_unblockVehicleTest) {
	car_->currentRoad_ = std::make_shared<sf::RectangleShape>(roads.at(6));
	car_->stopCounter_ = 200;
	car_->speed_ = 0;
	BOOST_CHECK_EQUAL("South", car_->direction_);
	car_->unblockVehicle();
	BOOST_CHECK_EQUAL("North", car_->direction_);
	BOOST_CHECK_EQUAL(0, car_->stopCounter_);
}

BOOST_AUTO_TEST_SUITE_END()
