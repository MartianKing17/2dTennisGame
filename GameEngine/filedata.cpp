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

        if(isspace(data.at(i)))
        {
            continue;
        }

        str.push_back(data.at(i));
    }

    return str;
}


vector<string> getClearDataFromFile()
{
    vector<string> data=readFile("path/setting.dat");

    vector <string> value=readFile("path/save.dat");
    data.insert(data.end(),value.begin(),value.end());

    vector<string> new_data;

    for (string i:data)
    {
        if(i == "")
        {
            continue;
        }

        i = clearing(i);
        new_data.push_back(i);
    }

    return new_data;
}

