#include "dir.hpp"

std::string getCurrentWorkingDir()
{
    char buff[FILENAME_MAX];
    getCurrentDir(buff, FILENAME_MAX);
    std::string currentWorkingDir(buff);
    
    return currentWorkingDir;
}
