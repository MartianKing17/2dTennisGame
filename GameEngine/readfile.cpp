//
// Created by maxim on 10.05.2019.
//

#include "readfile.h"
#include <iostream>
#include <vector>
#include <string>

using namespace std;

vector<string> readFile(string nameFile)
{
    ifstream read(nameFile);
    vector<string> buffer;
    string dataFile;

    if(!read.is_open())
    {
        read.exceptions(ifstream::failbit|ifstream::badbit);
        ifstream::failure e("Can't opening file");
        throw e;
    }

    while(!read.eof())
    {
        getline(read,dataFile);
        buffer.push_back(dataFile);
    }

    read.close();

    return buffer;
}