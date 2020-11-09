#include "gtest/gtest.h"
#include "../../Code/StateMachine.h"
#include <memory>

struct StateMachineTest :testing::Test
{
	std::unique_ptr<ZPR::StateMachine> machine;

	StateMachineTest() {
		machine = std::make_unique<ZPR::StateMachine>(new ZPR::StateMachine());
	}
};

TEST_F(StateMachineTest, AddStateTest) {
	EXPECT_EQ(NULL, machine->GetActiveState());
}