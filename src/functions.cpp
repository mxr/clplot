#include "chart.hpp"
#include <iostream>
#include <string>

using namespace std;

string Chart::getType() {
    return type;
}

void Chart::addType(string newType) {
    type = newType;
}


void Chart::addData(string newData) {
    int size = 0; 
    while (newData[size] != '\0') { 
        ++size; 
    } 

    string newStrData = newData.substr(1, size - 2);
    size = size - 2;

    int iterCount = (size + 1);
        
    string delimiter = ",";
    size_t pos = 0;
    string token;

    while ((pos = newStrData.find(delimiter)) != string::npos) {
        token = newStrData.substr(0, pos);

        string::size_type sz;
        float addFloat = stof(token, &sz);
        data.push_back(addFloat);

        newStrData.erase(0, pos + delimiter.length());


    }
    
    string::size_type st;
    float addFloatEnd = stof(newStrData, &st);
    data.push_back(addFloatEnd);
    // for (int i = 0; i < iterCount; i = i + 2) {
    //     // cout << i << endl;

    //     //assign the current data value to addstr

    //     string::size_type sz;
    //     float addFloat = stof(addstr, &sz);
    //     data.push_back(addFloat);
    // }
}

vector<float> Chart::getData() {
    vector<float> returnV;

    for ( int i = 0; i < data.size(); i++) {
        returnV.push_back(data[i]);
    } 
    return returnV;
}