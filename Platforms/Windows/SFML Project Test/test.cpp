#include "gtest/gtest.h"
#include "../../../Code/StateMachine.h"
#include "../../../Code/MainMenuState.h"
#include <memory>
#include "../../../Code/Simulator.h"

struct StateMachineTest :testing::Test
{
	ZPR::StateMachine* machine;

	ZPR::SimulatorDataRef _data = std::make_shared<ZPR::SimulatorData>();

	StateMachineTest() {
		machine = new ZPR::StateMachine();
	}
	~StateMachineTest() {
		delete machine;
	}

};

TEST_F(StateMachineTest, AddStateTest) {
	
	
}