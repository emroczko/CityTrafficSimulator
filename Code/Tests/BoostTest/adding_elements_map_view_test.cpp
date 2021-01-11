#define BOOST_TEST_DYN_LINK
#include "../../adding_elements_map_view_helper.hpp"
#include "../../definitions.hpp"

#include "SFML/Graphics.hpp"

#include <boost/test/unit_test.hpp>

struct AddingHelperFixture {
    AddingHelperFixture()
	{
        data = std::make_shared<zpr::SimulatorData>();
        roads_.clear();
        data->assets_.loadTexture("Road", STREET_TEXTURE);
        data->assets_.loadTexture("Entry", ENTRY_TEXTURE);
        addingHelper_ = std::make_unique<zpr::AddingHelper>(data, gridSize_);
        
        
	}
    zpr::SimulatorDataRef data;
    std::unique_ptr<zpr::AddingHelper> addingHelper_;
    int gridSize_= 16;
    std::string roadName_ = "Road";
    std::vector<sf::RectangleShape> roads_;
    sf::RectangleShape road_;
	~AddingHelperFixture() = default;
    
};

BOOST_FIXTURE_TEST_SUITE(AddingHelperTest, AddingHelperFixture)

BOOST_AUTO_TEST_CASE(AddingHelperTest_sizeOfRoadsVector)
{
    roads_.push_back(addingHelper_->addElement(roadName_, sf::Vector2i(2, 2)));
	BOOST_CHECK_EQUAL(1, roads_.size());
}

BOOST_AUTO_TEST_CASE(AddingHelperTest_addRoad)
{
    addingHelper_->addEnterRoad(sf::Vector2i(2, 2), roads_);
    BOOST_CHECK_EQUAL(1, roads_.size());
}

BOOST_AUTO_TEST_CASE(AddingHelperTest_add_3_roads)
{
    addingHelper_->addEnterRoad(sf::Vector2i(2, 2), roads_);
    addingHelper_->addUserRoad(sf::Vector2i(2, 3), roads_);
    addingHelper_->addGarage(sf::Vector2i(2, 4), roads_);
    BOOST_CHECK_EQUAL(3, roads_.size());
}

BOOST_AUTO_TEST_CASE(AddingHelperTest_centeredPositionOfRoadX)
{
    road_ = addingHelper_->addElement(roadName_, sf::Vector2i(1, -2));
    BOOST_CHECK_EQUAL(97, road_.getPosition().x);
}

BOOST_AUTO_TEST_CASE(AddingHelperTest_centeredPositionOfRoadY)
{
    road_ = addingHelper_->addElement(roadName_, sf::Vector2i(1, -2));
    BOOST_CHECK_EQUAL(-89, road_.getPosition().y);
}
BOOST_AUTO_TEST_CASE(AddingHelperTest_sizeOfRoad)
{
    road_ = addingHelper_->addElement(roadName_, sf::Vector2i(1, -2));
    BOOST_CHECK_EQUAL(road_.getSize().x, road_.getSize().y);
}
BOOST_AUTO_TEST_SUITE_END()
