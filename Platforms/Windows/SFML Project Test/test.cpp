#include "gtest/gtest.h"
#include "../../../Code/StateMachine.h"
#include <memory>

struct StateMachineTest :testing::Test
{
	ZPR::StateMachine* machine;
	StateMachineTest() {
		machine = new ZPR::StateMachine();
	}
	~StateMachineTest() {
		delete machine;
	}

};

TEST_F(StateMachineTest, AddStateTest) {
	EXPECT_EQ(1, 1);
}