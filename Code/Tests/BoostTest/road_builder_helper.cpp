#define BOOST_TEST_DYN_LINK
#include "../../road_builder_helper.hpp"
#include "../../definitions.hpp"

#include "SFML/Graphics.hpp"

#include <boost/test/unit_test.hpp>

struct RoadBuilderHelperFixture {
    RoadBuilderHelperFixture()
	{
        data = std::make_shared<zpr::SimulatorData>();
        roadBuilderHelper_ = std::make_unique<zpr::RoadBuilderHelper>(data, gridSize_);
	}
    zpr::SimulatorDataRef data;
    std::unique_ptr<zpr::RoadBuilderHelper> roadBuilderHelper_;
    int gridSize_ = 16;
    int cellSize_ = SCREEN_HEIGHT/gridSize_;
    std::vector<sf::RectangleShape> roads_;
    sf::RectangleShape road_;
	~RoadBuilderHelperFixture() = default;
    
};

BOOST_FIXTURE_TEST_SUITE(RoadBuilderHelperTest, RoadBuilderHelperFixture)

BOOST_AUTO_TEST_CASE(RoadBuilderHelperTest_RoadExist)
{
    road_.setPosition(200+cellSize_/2,200+cellSize_/2);
    roads_.push_back(road_);
	BOOST_CHECK_EQUAL(1, roadBuilderHelper_->checkRoadExists(sf::Vector2f(200,200), roads_));
    BOOST_CHECK_EQUAL(0, roadBuilderHelper_->checkRoadExists(sf::Vector2f(100,100), roads_));
}

BOOST_AUTO_TEST_SUITE_END()
