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
        
    for (int i = 0; i < iterCount; i = i + 2) {
        // cout << i << endl;
        string addstr = newStrData.substr(i, 1);
        string::size_type sz;     // alias of size_t
        float addFloat = stof(addstr, &sz);
        data.push_back(addFloat);
    }
}

void Chart::getData() {
    for ( int i = 0; i < data.size(); i++) {
        cout << data[i] << " ";

    } 
    cout << endl;
}