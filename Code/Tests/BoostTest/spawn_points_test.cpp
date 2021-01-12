#define BOOST_TEST_DYN_LINK
#include "../../spawn_points.hpp"
#include "../../definitions.hpp"


#include "SFML/Graphics.hpp"

#include <boost/test/unit_test.hpp>

struct SpawnPointsFixture {
    SpawnPointsFixture()
	{ 
        spawnPoints_ = std::make_unique<zpr::SpawnPoints>(gridSize_);
	}
    std::unique_ptr<zpr::SpawnPoints> spawnPoints_;
    int gridSize_= 16;
    std::vector<sf::RectangleShape> roads_;
    std::vector<sf::RectangleShape> exitSites_;
	~SpawnPointsFixture() = default;
    
};

BOOST_FIXTURE_TEST_SUITE(SpawnPointsTest, SpawnPointsFixture)

BOOST_AUTO_TEST_CASE(SpawnPointsTest_addingStartingPoints)
{
    spawnPoints_->addStartingRoad(roads_);
	BOOST_CHECK_EQUAL(2, roads_.size());
}
BOOST_AUTO_TEST_CASE(SpawnPointsTest_FirstStartingPointPosition)
{
    spawnPoints_->addStartingRoad(roads_);
    BOOST_CHECK_EQUAL(35, roads_.at(0).getPosition().x);
    BOOST_CHECK_EQUAL(-89, roads_.at(0).getPosition().y);
}
BOOST_AUTO_TEST_CASE(SpawnPointsTest_SecondStartingPointPosition)
{
    spawnPoints_->addStartingRoad(roads_);
    BOOST_CHECK_EQUAL(965, roads_.at(1).getPosition().x);
    BOOST_CHECK_EQUAL(-89, roads_.at(1).getPosition().y);
}

BOOST_AUTO_TEST_CASE(SpawnPointsTest_addingExitPoints)
{
    spawnPoints_->setupExitSites(exitSites_);
    BOOST_CHECK_EQUAL(2, exitSites_.size());
}
BOOST_AUTO_TEST_CASE(SpawnPointsTest_FirstExitPointPosition)
{
    spawnPoints_->setupExitSites(exitSites_);
    BOOST_CHECK_EQUAL(35, exitSites_.at(0).getPosition().x);
    BOOST_CHECK_EQUAL(-105, exitSites_.at(0).getPosition().y);
}
BOOST_AUTO_TEST_CASE(SpawnPointsTest_SecondExitPointPosition)
{
    spawnPoints_->setupExitSites(exitSites_);
    BOOST_CHECK_EQUAL(965, exitSites_.at(1).getPosition().x);
    BOOST_CHECK_EQUAL(-74, exitSites_.at(1).getPosition().y);
}
BOOST_AUTO_TEST_SUITE_END()
