#define BOOST_TEST_DYN_LINK
#include "../../Helpers/init_create_state_helper.hpp"
#include "../../definitions.hpp"
#include "../../Components/button.hpp"
#include <SFML/Graphics.hpp>
#include <boost/test/unit_test.hpp>

struct InitCreateStateHelperFixture {
    InitCreateStateHelperFixture()
	{ 
        testButton1_ = zpr::Button("16x16");
	}
    zpr::InitCreateStateHelper helper_;
    zpr::Button testButton1_;
    std::string textToChange_ = "16";
	~InitCreateStateHelperFixture() = default;
    
};

BOOST_FIXTURE_TEST_SUITE(InitCreateStateHelperTest, InitCreateStateHelperFixture)

BOOST_AUTO_TEST_CASE(InitCreateStateHelperTest_ToString)
{
	BOOST_CHECK_EQUAL(16, helper_.changeTextToInt(textToChange_));
}

BOOST_AUTO_TEST_CASE(InitCreateStateHelperTest_ButtonTextToInt)
{
    BOOST_CHECK_EQUAL(16, helper_.getGridSizeFromButton(testButton1_));
}

BOOST_AUTO_TEST_SUITE_END()
