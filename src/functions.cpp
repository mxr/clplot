#include "../include/chart.hpp"
#include <iostream>
#include <string>

using namespace std;

string Chart::getType() {
    return type;
}

void Chart::addType(string newType) {
    type = newType;
}

void Chart::addData(string newData, int lines, int cols) {
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

    int dataNum = 0;
    while ((pos = newStrData.find(delimiter)) != string::npos) {
        token = newStrData.substr(0, pos);

        string::size_type sz;
        float addFloat = stof(token, &sz);
        data.push_back(addFloat);

        newStrData.erase(0, pos + delimiter.length());

        dataNum++;
    }

    dataNum++;
    string::size_type st;
    float addFloatEnd = stof(newStrData, &st);
    data.push_back(addFloatEnd);

    height = lines;
    width = cols;
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

void Chart::winSet(int height, int width, int posX, int posY, int termHeight, int termWidth) {
    // height will be lt termheight

    // cout << "chart height: " << height << endl;
    // cout << "position y: " << posY << endl;

    if ( height + posY > termHeight) {
        cout << "chart: \e[31merror:\e[0m The sum of the chart height (\e[93m" << height << "\e[0m) and vertical position (\e[93m" << posY <<  "\e[0m) is greater than the terminal height (\e[93m" << termHeight << "\e[0m)." << endl;
        exit(1);
    }
    else if ( width + posX > termWidth) {
        cout << "chart: \e[31merror:\e[0m The sum of the chart width (\e[93m" << width << "\e[0m) and horizontal position (\e[93m" << posX <<  "\e[0m) is greater than the terminal width (\e[93m" << termWidth << "\e[0m)." << endl;
        exit(1);
    }
    else {
        cout << "Chart height: " << height << endl;
        cout << "Chart width: " << width << endl;

        // Chart::window[1][2] = "gi";

        cout << window.size() << endl;

        vector<int> tl = { posX, posY };
        vector<int> tr = { posX + width, posY };
        vector<int> bl = { posX, posY + height };
        vector<int> br = { posX + width, posY + height };


        for (int i = 0; i < termHeight; i++) {
            vector<string> row; // Create an empty row

            if ( i == 0 ) {

                row.push_back(lineChars[0]);
                for ( int x = 0; x < termWidth - 2; x++)
                    row.push_back(lineChars[5]);
                row.push_back(lineChars[1]);

            }
            else if ( i == height - 1 ) {

                row.push_back(lineChars[2]);
                for ( int x = 0; x < termWidth - 2; x++)
                    row.push_back(lineChars[5]);
                row.push_back(lineChars[3]);

            }
            else {
                row.push_back(lineChars[4]);
                for ( int x = 0; x < termWidth - 2; x++)
                    row.push_back(" ");
                row.push_back(lineChars[4]);    
            }

            window.push_back(row);


            // for (int j = 0; j < width; j++) {
            //     row.push_back(i * j); // Add an element (column) to the row
            // }
            // vec.push_back(row); // Add the row to the main vector
            // // create a vector row then push this vector to the vector of vectors.
        }

        for ( int j = 0; j < termHeight; j++ ) {
            for ( int k = 0; k < termWidth; k++ ) {
                cout << window[j][k];
                // cout << j << k;
            }
            cout << endl;
        } 

    }
}
