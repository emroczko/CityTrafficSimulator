#define BOOST_TEST_DYN_LINK
#include "../../Helpers/deleting_elements_helper.hpp"
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
    sf::RectangleShape cameras_[3];
    sf::RectangleShape road_;
    sf::RectangleShape camera_;
	~DeletingHelperFixture() = default;
    
};

BOOST_FIXTURE_TEST_SUITE(DeletingHelperTest, DeletingHelperFixture)

BOOST_AUTO_TEST_CASE(DeletingHelperTest_sizeOfRoadsVector)
{
    road_.setPosition(sf::Vector2f(97,-89));
    roads_.push_back(road_);
    BOOST_CHECK_EQUAL(1, roads_.size());
    deletingHelper_->deleteRoad(sf::Vector2i(1, -2), roads_);
	BOOST_CHECK_EQUAL(0, roads_.size());
}

BOOST_AUTO_TEST_CASE(DeletingHelperTest_DeletingCameras)
{
    camera_.setPosition(sf::Vector2f(407, 159));
    cameras_[0] = camera_;
    BOOST_CHECK(camera_.getPosition().x == cameras_[0].getPosition().x);
    deletingHelper_->deleteCamera(sf::Vector2f(cameras_[0].getPosition().x, cameras_[0].getPosition().y), cameras_, 1);
    
    BOOST_CHECK( camera_.getPosition().x != cameras_[0].getPosition().x);
}

BOOST_AUTO_TEST_SUITE_END()
