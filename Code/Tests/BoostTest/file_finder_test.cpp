#define BOOST_TEST_DYN_LINK
#include "../../file_finder.hpp"

#include <boost/test/unit_test.hpp>

struct FileFinderFixture {
    FileFinderFixture()
	{ 
        
	}
    zpr::FileFinder fileFinder_;
    std::string fileName_ = "Demo.txt";
    std::string mapName_ = "Map1.txt";
	~FileFinderFixture() = default;
    
};

BOOST_FIXTURE_TEST_SUITE(FileFinderTest, FileFinderFixture)

BOOST_AUTO_TEST_CASE(FileFinderTest_FindDemo)
{
	BOOST_CHECK_EQUAL(true, fileFinder_.checkIfFileExist(fileName_));
}
//BOOST_AUTO_TEST_CASE(FileFinderTest_FindEmptySlot)
//{
//    BOOST_CHECK_EQUAL("Slot1", fileFinder_.checkIfFileExist(mapName_,1));
//}
//BOOST_AUTO_TEST_CASE(FileFinderTest_FindContainingSlot)
//{
//    BOOST_CHECK_EQUAL("Map1.txt", fileFinder_.checkIfFileExist(mapName_,1));
//}

BOOST_AUTO_TEST_SUITE_END()
