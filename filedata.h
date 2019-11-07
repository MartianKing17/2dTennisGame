//
// Created by maxim on 05.08.2019.
//

#ifndef INC_2DTENNISGAME_FILEDATA_H
#define INC_2DTENNISGAME_FILEDATA_H

#include <string>
#include <vector>
#include "include/readfile.h"

/*
    Getting clear data
    Example: monitor:full -> information about creating display
    After clearing we get full
*/
std::string clearing(std::string data);

std::vector<std::string> getClearDataFromFile();

#endif //INC_2DTENNISGAME_FILEDATA_H
