#include "../include/chart.hpp"
#include <iostream>
#include <math.h>
#include <sstream>
using namespace std;


// linechart constructor
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

    height = lines;
    width = cols;

    // add chart color
    color = newColor;
}

string Chart::getType() {
    return type;
}

vector<float> Chart::getData() {
    vector<float> returnV;

    for ( int i = 0; i < data.size(); i++) {
        returnV.push_back(data[i]);
        cout << data[i] << endl;
    } 
    return returnV;
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
        vector<int> tl = { posX, posY };
        vector<int> tr = { posX + chartCharWidth - 1, posY };
        vector<int> bl = { posX, posY + chartCharHeight - 1 };
        vector<int> br = { posX + chartCharWidth - 1, posY + chartCharHeight - 1 };

        for (int i = 0; i <= termHeight; i++) {

            vector<string> row;

            if ( i < tl[1] ) {
                //===========================================
                // If the current row is above the start row of 
                // the chart, then add a blank row to the screen.
                //===========================================

                for ( int j = 0; j <= termWidth; j++) {
                    row.push_back(" ");
                }
            }

            else if ( i == tl[1] ) {
                //========================================
                // The current row is the top chart row
                //========================================
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
                //================================================
                // The current row is chart cont between top/bottom
                //================================================
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
                //====================================
                // The current row is the bottom row
                //===================================
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
                //========================================
                // The current row is below the chart 
                // content so add a blank row to the screen.
                //========================================

                for ( int j = 0; j <= termWidth; j++) {
                    row.push_back(" ");
                }
            }

            window.push_back(row);
        }

    }
}

void Chart::draw() {
    //===================
    // Print the window
    //===================
    
    for ( int j = 0; j < height; j++ ) {
        for ( int k = 0; k < chartCharWidth + posX; k++ ) {
            cout << window[j][k];
        }
        cout << endl;
    } 
}

void Linechart::drawChar(int coordX, int coordY, string content, string color) {
    if ( area ) {
        coordX--;
        coordY--;

        int bl[2];

        bl[1] = posX + 1; 
        bl[0] = posY + chartCharHeight - 2;

        int coord[2] = {bl[0] - coordY, bl[1] + coordX};

        // cout << "Adding " << content << " at " << coord[1] << ", " << coord[0] << endl;
        if ( coord[0] < 0 ) {
            // cout << "Something went wrong" << endl;
        }
        else {
            // cout << "start: " << coord[0] << ", end: " << posY + chartCharHeight + 1 << endl;
            // window[coord[0]][coord[1]] = color + content + "\e[0m";
            for ( int i = coord[0] + 1; i < (posY + chartCharHeight - 1); i++) {
                if ( window[i][coord[1]] == " " ) {
                    window[i][coord[1]] = color + "█" + "\e[0m";
                }
            }
            window[coord[0]][coord[1]] = color + content + "\e[0m";

        }
    }
    else {
        coordX--;
        coordY--;

        int bl[2];

        bl[1] = posX + 1; 
        bl[0] = posY + chartCharHeight - 2;

        int coord[2] = {bl[0] - coordY, bl[1] + coordX};

        // cout << "Adding " << content << " at " << coord[1] << ", " << coord[0] << endl;
        // cout << "window size: " << window.size() << ", " << window[0].size() << endl;

        if ( coord[0] < 0 ) {
            // cout << "Something went wrong" << endl;
        }
        else {
            window[coord[0]][coord[1]] = color + content + "\e[0m";
        }
    }
}


vector<string> Linechart::pattern(vector<float> steps) {
    vector<string> returnVec;
    bool lastRound = false;
    for ( int i = 0; i < steps.size(); i = i + 2) {

        float x1 = round(steps[i]);
        float y1 = round(steps[i + 1]);

        // cout << "coord: " << x1 << ", " << y1 << endl;

        int x2 = round(steps[i + 2]);
        int y2 = round(steps[i + 3]);



        if ( i != steps.size() - 2  ) {
            int up = (y2 - y1);
            int over = (x2 - x1);

            // // cout << "up " << up << " over " << over << endl;
            // if ( up > 0 ) {
            //     drawChar(x1,y1,lineChars[3], color);
            // }
            // else if ( up < 0 ) {
            //     drawChar(x1,y1,lineChars[1], color);
            // }
            // else {
            //     drawChar(x1,y1,lineChars[5], color);
            // }
            
            // cout << "up: " << up << endl;
            // cout << "over: " << over << endl;

            // if ( fabs(up) > over ) {
            //     cout << up << " is greater than " << over << endl;
            // }
            // else {
            //     cout << over << " is greater than " << up << endl;
            // }
            if ( fabs(up) > over ) {
                // cout << "got here 0" << endl;
                if ( up == 0 ) {
                    up = 1;
                    cout << 0 << endl;
                }

                if ( over == 0 ) {
                    over = 1;
                    cout << 00 << endl;
                }
                int whole = (int) up / over;
                // cout << over << endl;
                // cout << up << endl;
                // cout << "got here 1" << endl;



                int mod = up % over;
                int upAdd;

                for ( int x = 0; x < over; x++ ) {
                    returnVec.push_back("over");
                    for ( int y = 0; y < fabs(whole); y++ ) {
                        string type = "4";
                        if ( whole > 0 ) {
                            type = "up";
                            // up
                        }
                        else {
                            type = "down";
                            // down
                        }
                        returnVec.push_back(type);
                        if ( fabs(mod) > 0 ) {
                            returnVec.push_back(type);
                            if ( type == "up" ) {
                                mod--;
                            }
                            else {
                                mod++;
                            }
                        }
                    }
                }
            }
            else if ( up == 0 ) {
                if ( over == 0) {
                    over = 1;
                }
                for ( int i = 0; i < over; i++) {
                    returnVec.push_back("over");
                }

            }
            else {
                if ( up == 0 ) {
                    up = 1;
                    cout << 0 << endl;
                }

                if ( over == 0 ) {
                    over = 2;
                    cout << 00 << endl;
                }

                int whole = (int) over / fabs(up);
                int mod = over % (int) fabs(up);
                int overAdd;
                string type = "5";
                
                if ( up > 0 ) {
                    type = "up";
                }
                else {
                    type = "down";
                }

                for ( int x = 0; x < fabs(up); x++ ) {
                    returnVec.push_back(type);
                    for ( int y = 0; y < whole; y++ ) {
                        returnVec.push_back("over");
                        if ( mod > 0 ) {
                            returnVec.push_back("over");
                            mod--;   
                        }
                    }
                }
            }
        }
        else {
            // drawChar(x1,y1,"─", color);
        }
    }
    return returnVec;
}

void Linechart::label() {
    vector<int> tl = { posX, posY };
    vector<int> tr = { posX + chartCharWidth - 1, posY };
    vector<int> bl = { posX, posY + chartCharHeight - 1 };
    vector<int> br = { posX + chartCharWidth - 1, posY + chartCharHeight - 1 };


    float min =  *( min_element( data.begin(), data.end() ) );
    float max =  *( max_element( data.begin(), data.end() ) );
    float range = ( max - min );
    float horSteps = (float)(chartCharWidth - 3) / (float)(data.size() - 1);
    cout << "showpoint: " << horSteps << endl;

    if ( horSteps < 1 ) {
        cout << "There is more data than the width of the chart. We should handle this?" << endl;
    }
    
    float verStepsChart = (Chart::chartCharHeight - 3) / range;

    float newRange = (range - 1) / verStepsChart;
    int x = 1;

    for ( float i = 1; i <= chartCharHeight - 2; i += verStepsChart) {

        cout << "line: " << i << endl;
        cout << "label: " << x * newRange << endl;
        
        float label = x * newRange;

        ostringstream ss;
        ss << label;
        string s(ss.str());

        // drawChar(0,i,s,"\e[31m");

        x++;
    }


}

string Chart::getChar(int coordX, int coordY) {
    coordX--;
    coordY--;

    int bl[2];

    bl[1] = posX + 1; 
    bl[0] = posY + chartCharHeight - 2;

    int coord[2] = {bl[0] - coordY, bl[1] + coordX};

    if ( coord[0] < 0 ) {
        // cout << "Something went wrong" << endl;
        return " ";
    }
    else {
        return window[coord[0]][coord[1]];
    }
}

vector<string> removeUpDown(vector<string> input) {
    vector<string> returnString;
    for ( int i = 0; i < input.size(); i++) {
        if ((input[i] == "up" && input[i + 1] == "down") || (input[i] == "down" && input[i + 1] == "up") ) { 
            i++;
        }
        else {
            returnString.push_back(input[i]);
        }
    }
    return returnString;
}

void Linechart::dataDraw() {

    float min =  *( min_element( data.begin(), data.end() ) );
    float max =  *( max_element( data.begin(), data.end() ) );
    float range = ( max - min );
    float horSteps = (float)(chartCharWidth - 3) / (float)(data.size() - 1);
    float verStepsData = range / (chartCharHeight - 3);
    float verStepsChart = (chartCharHeight - 3) / range;
    float currentCoord[2];
    float charCoord[2];

    currentCoord[0] = 1;
    charCoord[0] = 1;

    if ( data[0] == min ) {
        charCoord[1] = 1;

    }
    else if ( data[0] == max ) {
        charCoord[1] = chartCharHeight - 2;

    }
    else {
        charCoord[1] = round(verStepsChart * ( data[0] - min ) + 1);
        
    }
    // cout << horSteps << endl;
    currentCoord[1] = charCoord[1];

    vector<float> chartSteps;

    chartSteps.push_back(currentCoord[0]);
    chartSteps.push_back(currentCoord[1]);

    for ( int x = 1; x < data.size(); x++ ) {
        float diff = data[x] - data[x - 1];
        float verChange = diff * verStepsChart;
        currentCoord[0] += horSteps;
        currentCoord[1] += verChange;

        chartSteps.push_back(currentCoord[0]);
        chartSteps.push_back(currentCoord[1]);
    }

    vector<string> pattern = removeUpDown(Linechart::pattern(chartSteps));
    // std::cout << "current coordinate: " << charCoord[0] << ", " << charCoord[1] << endl;
    vector<string> chosenchars;
    if ( area ) {
        chosenchars = charsArea;
    }
    else {
        chosenchars = chars;
    }

    for ( int i = 0; i < pattern.size() - 1; i++) {

        // cout << pattern[i] << " ";

        if ( pattern[i] == "over" ) {                
            if (pattern[i + 1] != "up" && pattern[i + 1] != "down" ) {
                charCoord[0]++;
                drawChar(charCoord[0], charCoord[1], chosenchars[5], color);
            }
            else {
                charCoord[0]++;
                if ( pattern[i + 1] == "up" ) {
                    drawChar(charCoord[0], charCoord[1], chosenchars[3], color);
                }
                else {
                    drawChar(charCoord[0], charCoord[1], chosenchars[1], color);
                }
            }
        }
        else if ( pattern[i] == "up" ) {
            if ( pattern[i + 1] != "up" ) {
                charCoord[1]++;
                drawChar(charCoord[0], charCoord[1], chosenchars[0], color);
            }
            else {
                charCoord[1]++;
                drawChar(charCoord[0], charCoord[1], chosenchars[6], color);
            }
        }
        else if ( pattern[i] == "down" ) {
            if ( pattern[i + 1] != "down" ) {
                charCoord[1]--;
                drawChar(charCoord[0], charCoord[1], chosenchars[2], color);
            }
            else {
                charCoord[1]--;
                drawChar(charCoord[0], charCoord[1], chosenchars[4], color);
            }  
        }
    }

    // HANDLE LAST CHAR HERE BASED ON PREVIOUS CHAR:
    //===============================================
    if ( pattern[pattern.size() - 1] == "down" ) {
        charCoord[1]--;
        drawChar(charCoord[0], charCoord[1], chosenchars[2], color);
    }
    else if ( pattern[pattern.size() - 1] == "up" ) {
        charCoord[1]++;
        drawChar(charCoord[0], charCoord[1], chosenchars[0], color);
    }

}


// BAR CHART METHODS

void Barchart::drawChar(int coordX, int coordY, string content, string color) {
    coordX--;
    coordY--;

    int bl[2];

    bl[1] = posX + 1; 
    bl[0] = posY + chartCharHeight - 2;

    int coord[2] = {bl[0] - coordY, bl[1] + coordX};

    // cout << "Adding " << content << " at " << coord[1] << ", " << coord[0] << endl;
    // cout << "window size: " << window.size() << ", " << window[0].size() << endl;

    if ( coord[0] < 0 ) {
        // cout << "Something went wrong" << endl;
    }
    else {
        window[coord[0]][coord[1]] = color + content + "\e[0m";
    }
}

void Barchart::dataDraw() {
    float min =  *( min_element( data.begin(), data.end() ) );
    float max =  *( max_element( data.begin(), data.end() ) );
    float range = ( max - min );
    float horSteps = (float)(chartCharWidth - 3) / (float)(data.size());
    float verStepsData = range / (chartCharHeight - 3);
    float verStepsChart = (chartCharHeight - 3) / range;

    int endPadding;
    int widthPadding;
    int barWidth = floor(horSteps);
    int arbitraryLimit = 4;
    int secondArbitraryLimit = 8;

    int extra = (chartCharWidth - 2) - (floor(horSteps) * data.size()); // may need to be -3 instead of -2
    
    vector<int> heights;
    for ( int i = 0; i < data.size(); i++ ) {
        heights.push_back(round(((data[i] - min) / range) * (chartCharHeight - 5) + 2));
    }

    if ( extra >= data.size() - 1) {
        // all good, may be able to add padding
        if ( floor(horSteps) > arbitraryLimit ) {
            // we can add additional padding to the ends
            barWidth -= 2;
            endPadding = 1;
            if ( barWidth > secondArbitraryLimit ) {
                widthPadding = 4;
                barWidth -= 4;
                // we should make the above test more scientific:
                //      if the ba

                // we can padd the insides too;
                // here's how much we can pad:
                
            }
        }
        else {
            endPadding = 0;
            widthPadding = 0;
            // the bars are too small to pad it
        }
    }
    else {
        endPadding = 0;
        widthPadding = 1;
        //loop to make bars smaller 
        barWidth = 1;
        // we have a problem, need to make bars smaller to allow for bar inside padding

    }

    cout << "the bars have " << endPadding << " end padding.\n";
    cout << "the bars are " << barWidth << " wide.\n";
    cout << "the bars have " << widthPadding << " padding.\n";

    cout << "Scale: " << min << max << endl;
    int curCoord[2] = { 1 + endPadding, 1 };

    for ( int x = 0; x < data.size(); x++ ) {
        for ( int j = 0; j < barWidth; j++ ) {
            for ( int i = heights[x]; i >= 0; i-- ){
                curCoord[1] = i;
                if ( i != 0 ) {
                    drawChar(curCoord[0],curCoord[1],"█",color);
                }
                else {
                    drawChar(curCoord[0],curCoord[1],"▀",color);
                }
            }
            curCoord[0] += 1;
        }
        curCoord[0] += widthPadding;
    }
}