#define CATCH_CONFIG_MAIN // Add this macro
#include "catch_amalgamated.hpp"// the file downloaded from the link mentioned above

#include "../Simulator.h"
#include "../MapView.h"
#include "../Definitions.h"
#include "../MainMenuState.h"
#include <iostream>

ZPR::Simulator sim(SCREEN_WIDTH, SCREEN_HEIGHT, "CityTrafficSimulator");

namespace ZPR {

    TEST_CASE( "Testing Map view" ) {
        SimulatorDataRef data = std::make_shared<SimulatorData>();
        int gridSize = 32;
        MapView mapTest(data, gridSize);
        SECTION("Testing grid size"){
            REQUIRE(gridSize == mapTest.getGridSize());
        }
        SECTION("Testing cell size"){
            REQUIRE((SCREEN_HEIGHT / gridSize) == mapTest.getCellSize());
        }
        SECTION("Testing Rows and Cols"){
            REQUIRE(sf::Vector2i(-1, -1) == mapTest.getRowCol());
        }
    };
    

    TEST_CASE( "Testing Main menu state" ) {
        SimulatorDataRef data = std::make_shared<SimulatorData>();
        unsigned long buttons = 2;
        MainMenuState menuButtonsTest(data);
        menuButtonsTest.Init();
        SECTION("Testing Buttons in menu state" ){
            REQUIRE(buttons == menuButtonsTest.GetButtonsAmount());
        }
    };

    
}

