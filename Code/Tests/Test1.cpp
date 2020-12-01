#define CATCH_CONFIG_MAIN // Add this macro
#include "catch_amalgamated.hpp"// the file downloaded from the link mentioned above


#include "../Definitions.h"
#include "../Simulator.h"
#include "../MapView.h"

ZPR::Simulator sim(SCREEN_WIDTH, SCREEN_HEIGHT, "CityTrafficSimulator");

namespace ZPR {

    TEST_CASE( "Testing map view" ) {
        SimulatorDataRef data = std::make_shared<SimulatorData>();
        int gridSize = 32;
        MapView mapTest(data, gridSize);
        REQUIRE(gridSize == mapTest.getGridSize());
    };

}

