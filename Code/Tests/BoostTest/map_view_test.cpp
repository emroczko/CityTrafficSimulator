#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE CityTrafficSimulator test
#include "../../Views/map_view.hpp"
#include "../../simulator.hpp"
#include "../../definitions.hpp"
#include <SFML/Graphics.hpp>
#include <boost/test/unit_test.hpp>

struct MapViewTestFixture {
	MapViewTestFixture()
	{ 
		data = std::make_shared<zpr::SimulatorData>();
		mapView = std::make_unique<zpr::MapView>(data, 16);
		mapView->init();
	}
	zpr::SimulatorDataRef data;
	std::unique_ptr<zpr::MapView> mapView;
	~MapViewTestFixture() = default;
};

BOOST_FIXTURE_TEST_SUITE(MapViewTest, MapViewTestFixture)

BOOST_AUTO_TEST_CASE(MapView_CellSizeTest)
{
	BOOST_CHECK_EQUAL(SCREEN_HEIGHT / 16, mapView->getCellSize());
}

BOOST_AUTO_TEST_CASE(MapView_StartingRowAndColumn)
{
	BOOST_CHECK_EQUAL(-1, mapView->getRowCol().x);
	BOOST_CHECK_EQUAL(-1, mapView->getRowCol().y);
}

BOOST_AUTO_TEST_CASE(MapView_HandleInputTest) {
	sf::Vector2i mouse_position = sf::Vector2i(static_cast<int>(SCREEN_WIDTH / 2), static_cast<int>(SCREEN_HEIGHT / 2));
	BOOST_CHECK_EQUAL(mapView->isClicked(mouse_position), true);
}

BOOST_AUTO_TEST_SUITE_END()
