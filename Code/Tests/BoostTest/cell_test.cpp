#define BOOST_TEST_DYN_LINK
#include "../../cell.hpp"
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_CASE(Cell_positionTest)
{
	zpr::Cell cell(3, 5);
	BOOST_CHECK_EQUAL(3, cell.getPosition().x);
	BOOST_CHECK_EQUAL(5, cell.getPosition().y);
}