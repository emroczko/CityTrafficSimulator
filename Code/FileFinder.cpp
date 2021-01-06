#include "FileFinder.h"
#include <sys/stat.h>
#include <unistd.h>
#include <string>
#include <fstream>

namespace ZPR{

    FileFinder::FileFinder() {};

    std::string FileFinder::CheckIfFileExist(const std::string& name, int number){
        
        struct stat buffer;
        
        if (stat (name.c_str(), &buffer) == 0){
            auto mod_time = buffer.st_mtime;
            return name;
        }
        else
            return "Slot "+std::to_string(number);
    }
}
