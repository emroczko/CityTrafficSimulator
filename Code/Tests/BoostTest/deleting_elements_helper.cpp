#define BOOST_TEST_DYN_LINK
#include "../../deleting_elements_helper.hpp"
#include "../../definitions.hpp"

#include "SFML/Graphics.hpp"

#include <boost/test/unit_test.hpp>

struct DeletingHelperFixture {
    DeletingHelperFixture()
	{
        data = std::make_shared<zpr::SimulatorData>();
        data->assets_.loadTexture("Road", STREET_TEXTURE);
        deletingHelper_ = std::make_unique<zpr::DeletingHelper>(data, gridSize_);
        
        
	}
    zpr::SimulatorDataRef data;
    std::unique_ptr<zpr::DeletingHelper> deletingHelper_;
    int gridSize_= 16;
    std::vector<sf::RectangleShape> roads_;
    sf::RectangleShape road_;
	~DeletingHelperFixture() = default;
    
};

BOOST_FIXTURE_TEST_SUITE(DeletingHelperTest, DeletingHelperFixture)

BOOST_AUTO_TEST_CASE(DeletingHelperTest_sizeOfRoadsVector)
{
    road_.setPosition(sf::Vector2f(66,-120));
    roads_.push_back(road_);
    BOOST_CHECK_EQUAL(1, roads_.size());
    deletingHelper_->deleteRoad(sf::Vector2f(1, -2), roads_);
	BOOST_CHECK_EQUAL(0, roads_.size());
}

BOOST_AUTO_TEST_SUITE_END()
