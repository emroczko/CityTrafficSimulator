#include <boost/test/unit_test.hpp>
#include "../Simulator.h"
#include "../MapView.h"
#define BOOST_TEST_MODULE mapViewTest

namespace ZPR {
	BOOST_AUTO_TEST_CASE(constructorTest)
	{
		SimulatorDataRef data = std::make_shared<SimulatorData>();
		int gridSize = 32;
		MapView mapTest(data, gridSize);
		BOOST_CHECK(gridSize == mapTest.getGridSize());
	}
}