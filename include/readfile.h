//
// Created by maxim on 10.05.2019.
//

#ifndef GAMEGRAPHICLIBRARY_READFILE_H
#define GAMEGRAPHICLIBRARY_READFILE_H

#include <iostream>
#include <memory>
#include <fstream>
#include <utility>
#include <vector>
using namespace std;

size_t findSymbol(shared_ptr<std::vector<char>> buffer,size_t i);

string getDataFromFile(shared_ptr<vector<char>> & buffer,size_t & i);

shared_ptr<vector<char>> readFile();


#endif //GAMEGRAPHICLIBRARY_READFILE_H
