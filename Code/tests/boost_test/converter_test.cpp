#define BOOST_TEST_DYN_LINK
#include "../../helpers/converter.hpp"
#include "../../definitions.hpp"
#include "../../components/cell.hpp"

#include "SFML/Graphics.hpp"

#include <boost/test/unit_test.hpp>

struct ConverterFixture {
    ConverterFixture()
	{ 
        converter_ = std::make_unique<zpr::Converter>(gridSize_);
	}
    std::unique_ptr<zpr::Converter> converter_;
    int gridSize_= 16;
    sf::Vector2f pixels_ = sf::Vector2f(66, -120);
    sf::Vector2i rowcol_ = sf::Vector2i(1, -2);
    double pixelsDouble_ = -89;
    int rowcolInt_ = -2;
    int cellSize_ = (SCREEN_HEIGHT / gridSize_);
    zpr::Cell cell_;
    sf::RectangleShape tempCell_;
	~ConverterFixture() = default;
    
};

BOOST_FIXTURE_TEST_SUITE(ConverterTest, ConverterFixture)

BOOST_AUTO_TEST_CASE(ConverterTest_calculatingPrefix)
{
	BOOST_CHECK_EQUAL(4, converter_->calculatePrefix());
}

BOOST_AUTO_TEST_CASE(ConverterTest_transformingRowColToPixelsXpos)
{
    BOOST_CHECK_EQUAL(pixels_.x, converter_->transformRowColToPixels(rowcol_).x);
}

BOOST_AUTO_TEST_CASE(ConverterTest_transformingRowColToPixelsYpos)
{
    BOOST_CHECK_EQUAL(pixels_.y, converter_->transformRowColToPixels(rowcol_).y);
}

BOOST_AUTO_TEST_CASE(ConverterTest_transformingPixelsToRowCol)
{
    BOOST_CHECK_EQUAL(rowcolInt_, converter_->transformPixelsToRowCol(pixelsDouble_));
}

BOOST_AUTO_TEST_CASE(ConverterTest_getCellSize)
{
    BOOST_CHECK_EQUAL(cellSize_, converter_->getCellSize());
}

BOOST_AUTO_TEST_CASE(ConverterTest_convertingEnterCell)
{
    cell_ = zpr::Cell(-2,1);
    tempCell_ = converter_->convertCellToCenteredRectShape(cell_, "Enter");
    BOOST_CHECK_EQUAL(97, tempCell_.getPosition().x);
    BOOST_CHECK_EQUAL(-89, tempCell_.getPosition().y);
}
BOOST_AUTO_TEST_CASE(ConverterTest_convertingUserCell)
{
    cell_ = zpr::Cell(4,0);
    tempCell_ = converter_->convertCellToCenteredRectShape(cell_, "User");
    BOOST_CHECK_EQUAL(283, tempCell_.getPosition().x);
    BOOST_CHECK_EQUAL(35, tempCell_.getPosition().y);
}
BOOST_AUTO_TEST_SUITE_END()
