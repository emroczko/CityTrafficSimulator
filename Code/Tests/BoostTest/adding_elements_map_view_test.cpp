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
        addingHelper_ = std::make_unique<zpr::AddingHelper>(data, gridSize_);
        roads_.push_back(addingHelper_->addElement(roadName_, sf::Vector2i(2, 2)));
	}
    zpr::SimulatorDataRef data;
    std::unique_ptr<zpr::AddingHelper> addingHelper_;
    int gridSize_= 16;
    std::string roadName_ = "Road";
    std::vector<sf::RectangleShape> roads_;
	~AddingHelperFixture() = default;
    
};

BOOST_FIXTURE_TEST_SUITE(AddingHelperTest, AddingHelperFixture)

BOOST_AUTO_TEST_CASE(AddingHelperTest_sizeOfRoads)
{
	BOOST_CHECK_EQUAL(0, roads_.size());
}

BOOST_AUTO_TEST_SUITE_END()
