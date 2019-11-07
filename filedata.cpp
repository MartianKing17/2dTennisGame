//
// Created by maxim on 05.08.2019.
//

#include "filedata.h"

using namespace std;

string clearing(string data)
{
    bool value=false;
    string str;

    for (int i = 0; i < data.size(); i++)
    {
        if(!value)
        {
            if(data.at(i)!=':')
            {
                continue;
            }

            value=true;
            continue;
        }

        str.push_back(data.at(i));
    }

    return str;
}


vector<string> getClearDataFromFile()
{
    vector<string> data=readFile("setting.dat");

    const size_t len=data.size();

    vector <string> value=readFile("save.dat");
    data.insert(data.end(),value.begin(),value.end());


    for (int i = 0; i < len; i++)
    {
        data.at(i)=clearing(data.at(i));
    }

    return data;
}

