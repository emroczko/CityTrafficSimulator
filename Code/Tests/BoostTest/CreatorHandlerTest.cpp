#include "../../CreatorHandler.h"
#define BOOST_TEST_MODULE mytests
#include <boost/test/included/unit_test.hpp>

struct CreatorHandlerFixture {
	CreatorHandlerFixture(){}
	~CreatorHandlerFixture() = default;
	std::unique_ptr<ZPR::CreatorHandler> creatorHandler;
};

BOOST_AUTO_TEST_CASE(myTestCase)
{
  BOOST_TEST(1 == 1);
  BOOST_TEST(true);
}