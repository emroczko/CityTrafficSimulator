/**
 * file_finder.hpp
 * Header of FileFinder class.
 */

#pragma once
#include <sys/types.h>
#include <sys/stat.h>
#ifndef WIN32
#include <unistd.h>
#endif

#ifdef WIN32
#define stat _stat
#endif

#include <iostream>

namespace zpr {

    /**
     * Class responsible for finding files to load project from.
     */
    class FileFinder{
    public:
        FileFinder();
        std::string checkIfFileExist(const std::string& name, int number);
        bool checkIfFileExist(const std::string& name);
    };
}
