#define BOOST_TEST_DYN_LINK
#include "../../states/main_menu_state.hpp"
#include "../../simulator.hpp"
#include "../../definitions.hpp"
#include <SFML/Graphics.hpp>
#include <boost/test/unit_test.hpp>

struct MainMenuStateTestFixture {
	MainMenuStateTestFixture()
	{ 
		data = std::make_shared<zpr::SimulatorData>();
        main_menu_state = std::make_shared<zpr::MainMenuState>(data);
        main_menu_state->init();
	}
    zpr::SimulatorDataRef data;
    std::shared_ptr<zpr::MainMenuState> main_menu_state;
	~MainMenuStateTestFixture() = default;
};

BOOST_FIXTURE_TEST_SUITE(MainMenuStateTest, MainMenuStateTestFixture)

BOOST_AUTO_TEST_CASE(MainMenuState_ButtonsAmount)
{
	BOOST_CHECK_EQUAL(4, main_menu_state->getButtonsAmount());
}

BOOST_AUTO_TEST_SUITE_END()
