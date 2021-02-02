#define BOOST_TEST_DYN_LINK
#include "../../helpers/viewport_calculator.hpp"

#include <boost/test/unit_test.hpp>

struct ViewportCalculatorFixture {
    ViewportCalculatorFixture()
	{ 
        
	}
    zpr::ViewportCalculator viewportCalculator_;
    sf::FloatRect floatRect_;
	~ViewportCalculatorFixture() = default;
    
};

BOOST_FIXTURE_TEST_SUITE(ViewportCalculatorTest, ViewportCalculatorFixture)

BOOST_AUTO_TEST_CASE(ViewportCalculatorTest_CalculateCamerasViewport)
{
    float rect_width = (1.f - (float)SCREEN_HEIGHT / (float)SCREEN_WIDTH) / 2;
    float rect_left = 0.f;
    floatRect_ = sf::FloatRect(rect_left, 0.f, rect_width, 1.f);
    BOOST_CHECK_EQUAL(floatRect_.height, viewportCalculator_.calculateCamerasViewport().height);
    BOOST_CHECK_EQUAL(floatRect_.width, viewportCalculator_.calculateCamerasViewport().width);
    BOOST_CHECK_EQUAL(floatRect_.top, viewportCalculator_.calculateCamerasViewport().top);
    BOOST_CHECK_EQUAL(floatRect_.left, viewportCalculator_.calculateCamerasViewport().left);
}
BOOST_AUTO_TEST_CASE(ViewportCalculatorTest_CalculateMapViewport)
{
    float rect_width = (float)SCREEN_HEIGHT / (float)SCREEN_WIDTH;
    float rect_left = (1.f - rect_width)/2;
    floatRect_ = sf::FloatRect(rect_left, 0.f, rect_width, 1.f);
    BOOST_CHECK_EQUAL(floatRect_.height, viewportCalculator_.calculateMapViewport().height);
    BOOST_CHECK_EQUAL(floatRect_.width, viewportCalculator_.calculateMapViewport().width);
    BOOST_CHECK_EQUAL(floatRect_.top, viewportCalculator_.calculateMapViewport().top);
    BOOST_CHECK_EQUAL(floatRect_.left, viewportCalculator_.calculateMapViewport().left);
}

BOOST_AUTO_TEST_CASE(ViewportCalculatorTest_CalculateToolsViewport)
{
    float rect_width = (1.f - (float)SCREEN_HEIGHT / (float)SCREEN_WIDTH) / 2;
    float rect_left = rect_width + (float)SCREEN_HEIGHT / (float)SCREEN_WIDTH;
    floatRect_ = sf::FloatRect(rect_left, 0.f, rect_width, 1.f);
    BOOST_CHECK_EQUAL(floatRect_.height, viewportCalculator_.calculateToolsViewport().height);
    BOOST_CHECK_EQUAL(floatRect_.width, viewportCalculator_.calculateToolsViewport().width);
    BOOST_CHECK_EQUAL(floatRect_.top, viewportCalculator_.calculateToolsViewport().top);
    BOOST_CHECK_EQUAL(floatRect_.left, viewportCalculator_.calculateToolsViewport().left);
}


BOOST_AUTO_TEST_SUITE_END()
