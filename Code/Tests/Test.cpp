#include "../Simulator.h"
#include "../MapView.h"
#define BOOST_TEST_MODULE mytests
#include <boost/test/included/unit_test.hpp>

namespace ZPR {
	BOOST_AUTO_TEST_CASE(constructorTest)
	{
		SimulatorDataRef data = std::make_shared<SimulatorData>();
		int gridSize = 32;
		//MapView mapTest(data, gridSize);
		//BOOST_CHECK_EQUAL(gridSize, mapTest.getGridSize());
	}
}