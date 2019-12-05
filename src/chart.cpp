// basic chart methods

#include "../include/chart.hpp"
#include <math.h>

using namespace std;

// linechart constructor:
Linechart::Linechart(string newType, string newData, int lines, int cols, string newColor, bool areachart){
    // add area chart
    area = areachart;
    // add chart type
    type = newType;

    // add chart data
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

    // add chart color
    color = newColor;
};

// barchart constructor
Barchart::Barchart(string newType, string newData, int lines, int cols, string newColor) {
    // add chart type
    type = newType;

    // add chart data
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

    // add chart size
    height = lines;
    width = cols;

    // add chart color
    color = newColor;
}

string Chart::getType() {
    return type;
}

// return the chart data as a vector;
vector<float> Chart::getData() {
    return data;
}

void Chart::winSet(int chartheight, int chartwidth, int positionX, int positionY) {
    int termHeight = height;
    int termWidth = width;
    
    chartCharHeight = chartheight;
    chartCharWidth = chartwidth;

    posX = positionX;
    posY = positionY;

    if ( chartCharHeight + posY > termHeight) {
        cout << "chart: \e[31merror:\e[0m The sum of the chart height (\e[93m" << height << "\e[0m) and vertical position (\e[93m" << positionY <<  "\e[0m) is greater than the terminal height (\e[93m" << termHeight << "\e[0m)." << endl;
        exit(1);
    }
    else if ( chartCharWidth + posX > termWidth) {
        cout << "chart: \e[31merror:\e[0m The sum of the chart width (\e[93m" << width << "\e[0m) and horizontal position (\e[93m" << positionX <<  "\e[0m) is greater than the terminal width (\e[93m" << termWidth << "\e[0m)." << endl;
        exit(1);
    }
    else {
        int tl[2] = { posX, posY };
        int tr[2] = { posX + chartCharWidth - 1, posY };
        int bl[2] = { posX, posY + chartCharHeight - 1 };
        int br[2] = { posX + chartCharWidth - 1, posY + chartCharHeight - 1 };

        // loop through the window
        for (int i = 0; i <= termHeight; i++) {

            vector<string> row;

            if ( i < tl[1] ) {
                // If the current row is above the start row of 
                // the chart, then add a blank row to the screen.

                for ( int j = 0; j <= termWidth; j++) {
                    row.push_back(" ");
                }
            }

            else if ( i == tl[1] ) {
                // the current row is the top chart row
                for ( int j = 0; j <= termWidth; j++ ) {
                    if ( j == tl[0] ) {
                        row.push_back(winChars[0]);
                    }
                    else if ( j == tr[0]) {
                        row.push_back(winChars[1]);
                    }
                    else if ( j > tl[0] && j < tr[0] ){
                        row.push_back(winChars[5]);
                    }
                    else {
                        row.push_back(" ");
                    }
                }
            }
            else if ( i > tl[1] && i < bl[1] ) {
                // the current row is chart cont between top/bottom
                for ( int j = 0; j <= termWidth; j++) {
                    if ( j == tl[0] || j == tr[0] ) {
                        row.push_back(winChars[4]);
                    }
                    else {
                        row.push_back(" ");
                    }
                }
            }
            else if ( i == bl[1] ) {
                // the current row is the bottom row
                for ( int j = 0; j <= termWidth; j++ ) {
                    if ( j == tl[0] ) {
                        row.push_back(winChars[2]);
                    }
                    else if ( j == tr[0]) {
                        row.push_back(winChars[3]);
                    }
                    else if ( j > tl[0] && j < tr[0] ){
                        row.push_back(winChars[5]);
                    }
                    else {
                        row.push_back(" ");
                    }
                }
            }
            else {
                // The current row is below the chart 
                // content so add a blank row to the screen.

                for ( int j = 0; j <= termWidth; j++) {
                    row.push_back(" ");
                }
            }

            window.push_back(row);
        }

    }
}

void Chart::draw() {

    // Print the window
    for ( int j = 0; j < height; j++ ) {
        for ( int k = 0; k < chartCharWidth + posX; k++ ) {
            cout << window[j][k];
        }
        cout << endl;
    } 

}