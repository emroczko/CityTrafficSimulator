//#define BOOST_TEST_DYN_LINK
//#include <boost/test/unit_test.hpp>
//#include <SFML/Graphics.hpp>
//#include "../../Vehicles/vehicle.hpp"
//#include "../../Vehicles/car.hpp"
//#include "../../Vehicles/truck.hpp"
//
//
//struct VehicleTestFixture {
//	VehicleTestFixture()
//	{
//		initRoads();
//		Car = std::make_unique <zpr::Car>(20, 20, 51, roads);
//		Truck = std::make_unique <zpr::Truck>(20, 20, 51, roads);
//	}
//	void initRoads() {
//		for (int i = 0; i < 20; i++) {
//			sf::RectangleShape road;
//			road.setPosition(sf::Vector2f(i % 4 * 51, i / 4 * 51));
//			road.setSize(sf::Vector2f(51, 51));
//			roads.push_back(road);
//		}
//	}
//	~VehicleTestFixture() = default;
//	std::vector<sf::RectangleShape> roads;
//	std::unique_ptr<zpr::Vehicle> Car;
//	std::unique_ptr<zpr::Vehicle> Truck;
//};
//
//BOOST_FIXTURE_TEST_SUITE(VehicleTest, VehicleTestFixture)
//
//BOOST_AUTO_TEST_CASE(Vehicle_PositionTest) {
//	BOOST_CHECK_EQUAL(20, Car->x_);
//	BOOST_CHECK_EQUAL(20, Car->y_);
//	BOOST_CHECK_EQUAL(20, Truck->x_);
//	BOOST_CHECK_EQUAL(20, Truck->y_);
//	BOOST_CHECK_EQUAL(20, Car->shape_.getPosition().x);
//	BOOST_CHECK_EQUAL(20, Car->shape_.getPosition().y);
//	BOOST_CHECK_EQUAL(20, Truck->shape_.getPosition().x);
//	BOOST_CHECK_EQUAL(20, Truck->shape_.getPosition().y);
//}
//
//BOOST_AUTO_TEST_CASE(Vehicle_SpeedTest) {
//	BOOST_CHECK_EQUAL(3, Car->speed_);
//	BOOST_CHECK_EQUAL(3, Truck->speed_);
//}
//
//BOOST_AUTO_TEST_CASE(Vehicle_RoadsTest) {
//	BOOST_CHECK_EQUAL(20, Car->roads_.size());
//	BOOST_CHECK_EQUAL(20, Truck->roads_.size());
//}
//
//BOOST_AUTO_TEST_CASE(Vehicle_CellSizeTest) {
//	BOOST_CHECK_EQUAL(51, Car->cellSize_);
//	BOOST_CHECK_EQUAL(51, Truck->cellSize_);
//}
//
//BOOST_AUTO_TEST_CASE(Vhicle_RoadSizesTest) {
//	BOOST_CHECK_EQUAL(18, Car->roadSize_);
//	BOOST_CHECK_EQUAL(18, Truck->roadSize_);
//	BOOST_CHECK_EQUAL(3, Car->roadStripesSize_);
//	BOOST_CHECK_EQUAL(3, Truck->roadStripesSize_);
//	BOOST_CHECK_EQUAL(6, Car->sidewalkSize_);
//	BOOST_CHECK_EQUAL(6, Truck->sidewalkSize_);
//}
//
//BOOST_AUTO_TEST_CASE(Vhicle_DirectionTest) {
//	BOOST_CHECK_EQUAL("South", Car->direction_);
//	BOOST_CHECK_EQUAL("South", Truck->direction_);
//	BOOST_CHECK_EQUAL("", Car->previousDirection_);
//	BOOST_CHECK_EQUAL("", Truck->previousDirection_);
//}
//
//BOOST_AUTO_TEST_CASE(Vehicle_SizeTest) {
//	BOOST_CHECK_EQUAL(14, Car->shape_.getSize().x);
//	BOOST_CHECK_EQUAL(14, Car->shape_.getSize().y);
//	BOOST_CHECK_EQUAL(14, Truck->shape_.getSize().x);
//	BOOST_CHECK_EQUAL(20, Truck->shape_.getSize().y);
//}
//
//BOOST_AUTO_TEST_CASE(Vehicle_ColisionBoxTest) {
//	BOOST_CHECK_EQUAL(14, Car->colisionBox_.getSize().x);
//	BOOST_CHECK_EQUAL(14, Car->colisionBox_.getSize().y);
//	BOOST_CHECK_EQUAL(14, Truck->colisionBox_.getSize().x);
//	BOOST_CHECK_EQUAL(14, Truck->colisionBox_.getSize().y);
//}
//
//BOOST_AUTO_TEST_CASE(Vhicle_StopTest) {
//	BOOST_CHECK_EQUAL(3, Car->speed_);
//	BOOST_CHECK_EQUAL(3, Truck->speed_);
//	Car->stopVehicle();
//	Truck->stopVehicle();
//	BOOST_CHECK_EQUAL(0, Car->speed_);
//	BOOST_CHECK_EQUAL(0, Truck->speed_);
//}
//
//BOOST_AUTO_TEST_CASE(Vehicle_GoFromStopTest) {
//	Car->stopVehicle();
//	Truck->stopVehicle();
//	BOOST_CHECK_EQUAL(0, Car->speed_);
//	BOOST_CHECK_EQUAL(0, Truck->speed_);
//	Car->noColision();
//	Truck->noColision();
//	BOOST_CHECK_EQUAL(3, Car->speed_);
//	BOOST_CHECK_EQUAL(3, Truck->speed_);
//}
//
//BOOST_AUTO_TEST_CASE(Vehicle_ConstructorCurrntPreviousRoad) {
//	BOOST_CHECK_EQUAL(nullptr, Car->currentRoad_);
//	BOOST_CHECK_EQUAL(nullptr, Car->previousRoad_);
//	BOOST_CHECK_EQUAL(nullptr, Truck->currentRoad_);
//	BOOST_CHECK_EQUAL(nullptr, Truck->previousRoad_);
//}
//
//BOOST_AUTO_TEST_CASE(Vhicle_MoveTest) {
//	Car->currentRoad_ = std::make_shared<sf::RectangleShape>(roads.at(0));
//	Truck->currentRoad_ = std::make_shared<sf::RectangleShape>(roads.at(0));
//	BOOST_CHECK_EQUAL(20, Car->x_);
//	BOOST_CHECK_EQUAL(20, Car->y_);
//	BOOST_CHECK_EQUAL(20, Truck->x_);
//	BOOST_CHECK_EQUAL(20, Truck->y_);
//	Car->move();
//	Truck->move();
//	BOOST_CHECK_EQUAL(23, Car->x_);
//	BOOST_CHECK_EQUAL(20, Car->y_);
//	BOOST_CHECK_EQUAL(23, Truck->x_);
//	BOOST_CHECK_EQUAL(20, Truck->y_);
//	Car->stopVehicle();
//	Car->move();
//	BOOST_CHECK_EQUAL(23, Car->x_);
//	BOOST_CHECK_EQUAL(20, Car->y_);
//}
//BOOST_AUTO_TEST_SUITE_END()
