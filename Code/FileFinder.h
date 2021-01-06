#pragma once
#include <sys/types.h>
#include <sys/stat.h>
#ifndef WIN32
#include <unistd.h>
#endif

#ifdef WIN32
#define stat _stat
#endif
#include "SlotsEnum.h"
#include <iostream>

namespace ZPR {
    class FileFinder{
    public:
        FileFinder();
        std::string CheckIfFileExist(const std::string& name, int number);
        
    private:
    };
}
