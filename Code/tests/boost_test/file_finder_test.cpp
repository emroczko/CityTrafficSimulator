#define BOOST_TEST_DYN_LINK
#include "../../helpers/file_finder.hpp"

#include <boost/test/unit_test.hpp>

struct FileFinderFixture {
    FileFinderFixture()
	{ 
        
	}
    zpr::FileFinder fileFinder_;
    std::string fileName_ = "SavedMaps/Demo.txt";
    std::string mapName_ = "SavedMaps/Map1.txt";
	~FileFinderFixture() = default;
    
};

BOOST_FIXTURE_TEST_SUITE(FileFinderTest, FileFinderFixture)

BOOST_AUTO_TEST_CASE(FileFinderTest_FindDemo)
{
	BOOST_CHECK_EQUAL(true, fileFinder_.checkIfFileExist(fileName_));
}




BOOST_AUTO_TEST_SUITE_END()
