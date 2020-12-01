#define CATCH_CONFIG_MAIN // Add this macro
#include "catch_amalgamated.hpp"// the file downloaded from the link mentioned above

#include "Simulator.h"
#include "MapView.h"
#include <iostream>
#include "Simulator.h"
#include "Definitions.h"

ZPR::Simulator sim(SCREEN_WIDTH, SCREEN_HEIGHT, "CityTrafficSimulator");

namespace ZPR {

    TEST_CASE( "Testing map view" ) { //sample test case
        SimulatorDataRef data = std::make_shared<SimulatorData>();
        int gridSize = 32;
        MapView mapTest(data, gridSize);
        //BOOST_CHECK(gridSize == mapTest.getGridSize());
        REQUIRE(gridSize == mapTest.getGridSize());
    };

}

