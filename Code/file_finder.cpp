/**
 * file_finder.cpp
 * Implementation of FileFinder class.
 */
#include "file_finder.hpp"
#include <string>
#include <fstream>

namespace zpr{
    
    /**
     * FileFinder constructor.
     */
    FileFinder::FileFinder() {};

    /**
     * Method checking if file does exist.
     * @param name - Name of file we are looking for.
     * @param number - Number of slot where the save should exist in the application.
     * @return - Returns file's name or name of slot we were checking.
     */
    std::string FileFinder::checkIfFileExist(const std::string& name, int number){
        
        struct stat buffer;
        if (stat (name.c_str(), &buffer) == 0){
            //auto mod_time = buffer.st_mtime;
            return name;
        }
        else
            return "Slot "+std::to_string(number);
    }
    /**
     * Method checking if file does exist (returning only true/false).
     * @param name - Name of file we are looking for.
     * @return - Returns true if file exists or false if it doesn't exist.
     */
    bool FileFinder::checkIfFileExist(const std::string& name){
        
        struct stat buffer;
        if (stat (name.c_str(), &buffer) == 0)
            return true;
        else
            return false;
    }
}
