#include "../MapView.h"

#define BOOST_TEST_MODULE mytests
#include <boost/test/included/unit_test.hpp>


BOOST_AUTO_TEST_CASE(myTestCase)
{
	ZPR::SimulatorDataRef data = std::make_shared<ZPR::SimulatorData>();
	int GridSize = 32;
	ZPR::MapView maptest(data, GridSize);
	BOOST_CHECK_EQUAL(GridSize, maptest.getGridSize());
}