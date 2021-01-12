#define BOOST_TEST_DYN_LINK
#include "../../Components/cell.hpp"
#include "../../Components/grid.hpp"
#include <boost/test/unit_test.hpp>


BOOST_AUTO_TEST_CASE(Grid_Test)
{
	std::vector<zpr::Cell> cells;
	for (int i = 0; i < 25; i++) {
		cells.push_back(zpr::Cell(i/5, i%5));
	}
	zpr::Grid grid(cells, 5);
	BOOST_CHECK_EQUAL(5, grid.size_);
	BOOST_CHECK_EQUAL(25, grid.cells_.size());
	BOOST_CHECK_EQUAL(cells.at(4).getPosition().x, grid.getCell(0, 4).getPosition().x);
	BOOST_CHECK_EQUAL(cells.at(4).getPosition().y, grid.getCell(0, 4).getPosition().y);
}