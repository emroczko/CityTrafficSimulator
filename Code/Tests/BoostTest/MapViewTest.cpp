#include "../../MapView.h"
#include "../../Simulator.h"
#include "../../Definitions.h"
#include <SFML/Graphics.hpp>
#define BOOST_TEST_MODULE MapView test
#include <boost/test/included/unit_test.hpp>

struct MapViewTestFixture {
	MapViewTestFixture()
	{ 
		data = std::make_shared<ZPR::SimulatorData>();
		mapView = std::make_unique<ZPR::MapView>(data, 16);
		mapView->init();
	}
	ZPR::SimulatorDataRef data;
	std::unique_ptr<ZPR::MapView> mapView;
	~MapViewTestFixture() = default;
};

BOOST_FIXTURE_TEST_SUITE(MapViewTest, MapViewTestFixture)
BOOST_AUTO_TEST_CASE(CellSizeTest)
{
	BOOST_CHECK_EQUAL(SCREEN_HEIGHT / 16, mapView->getCellSize());
}

BOOST_FIXTURE_TEST_CASE(StartingRowAndColumn, MapViewTestFixture)
{
	BOOST_CHECK_EQUAL(-1, mapView->getRowCol().x);
	BOOST_CHECK_EQUAL(-1, mapView->getRowCol().y);
}

BOOST_FIXTURE_TEST_CASE(HandleInputTest, MapViewTestFixture) {
	sf::Vector2i mousePosition = sf::Vector2i(static_cast<int>(SCREEN_WIDTH / 2), static_cast<int>(SCREEN_HEIGHT / 2));
	BOOST_CHECK_EQUAL(mapView->isClicked(mousePosition), true);
}

BOOST_AUTO_TEST_SUITE_END()