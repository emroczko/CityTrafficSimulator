#pragma once

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
