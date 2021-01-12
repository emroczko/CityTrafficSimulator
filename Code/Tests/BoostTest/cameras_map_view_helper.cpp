#define BOOST_TEST_DYN_LINK
#include "../../cameras_map_view_helper.hpp"
#include "../../definitions.hpp"

#include "SFML/Graphics.hpp"

#include <boost/test/unit_test.hpp>

struct CamerasHelperFixture {
    CamerasHelperFixture()
	{
        camerasHelper_ = std::make_unique<zpr::CamerasHelper>(cellSize_);
	}
    
    std::unique_ptr<zpr::CamerasHelper> camerasHelper_;
    int cellSize_= 62;
    sf::RectangleShape cameras_[3];
	~CamerasHelperFixture() = default;
    
};

BOOST_FIXTURE_TEST_SUITE(CamerasHelperTest, CamerasHelperFixture)

BOOST_AUTO_TEST_CASE(CamerasHelperTest_CameraExist)
{
    cameras_[0].setPosition(314+cellSize_/2, 190+cellSize_/2);
	BOOST_CHECK_EQUAL(1, camerasHelper_->checkCameraExists(sf::Vector2f(314,190), cameras_));
}
BOOST_AUTO_TEST_CASE(CamerasHelperTest_CameraDoesntExist)
{
    cameras_[0].setPosition(100+cellSize_/2, 100+cellSize_/2);
    BOOST_CHECK_EQUAL(0, camerasHelper_->checkCameraExists(sf::Vector2f(314,190), cameras_));
}


BOOST_AUTO_TEST_SUITE_END()
