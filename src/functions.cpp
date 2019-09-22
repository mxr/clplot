#include "../include/chart.hpp"
#include <iostream>
#include <math.h>
#include <sstream>
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

}

vector<float> Chart::getData() {
    vector<float> returnV;

    for ( int i = 0; i < data.size(); i++) {
        returnV.push_back(data[i]);
    } 
    return returnV;
}

void Chart::addColor(string newColor) {
    color = newColor;
}

void Chart::winSet(int height, int width, int positionX, int positionY, int termHeight, int termWidth) {
    chartCharHeight = height;
    chartCharWidth = width;
    posX = positionX;
    posY = positionY;
    if ( height + positionY > termHeight) {
        std::cout << "chart: \e[31merror:\e[0m The sum of the chart height (\e[93m" << height << "\e[0m) and vertical position (\e[93m" << positionY <<  "\e[0m) is greater than the terminal height (\e[93m" << termHeight << "\e[0m)." << endl;
        exit(1);
    }
    else if ( width + positionX > termWidth) {
        std::cout << "chart: \e[31merror:\e[0m The sum of the chart width (\e[93m" << width << "\e[0m) and horizontal position (\e[93m" << positionX <<  "\e[0m) is greater than the terminal width (\e[93m" << termWidth << "\e[0m)." << endl;
        exit(1);
    }
    else {
        vector<int> tl = { positionX, positionY };
        vector<int> tr = { positionX + width - 1, positionY };
        vector<int> bl = { positionX, positionY + height - 1 };
        vector<int> br = { positionX + width - 1, positionY + height - 1 };

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
                        row.push_back(lineChars[0]);
                    }
                    else if ( j == tr[0]) {
                        row.push_back(lineChars[1]);
                    }
                    else if ( j > tl[0] && j < tr[0] ){
                        row.push_back(lineChars[5]);
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
                        row.push_back(lineChars[4]);
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
                        row.push_back(lineChars[2]);
                    }
                    else if ( j == tr[0]) {
                        row.push_back(lineChars[3]);
                    }
                    else if ( j > tl[0] && j < tr[0] ){
                        row.push_back(lineChars[5]);
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

void Chart::draw(int termHeight, int termWidth) {
    //===================
    // Print the window
    //===================
    
    for ( int j = 0; j < termHeight; j++ ) {
        for ( int k = 0; k < termWidth; k++ ) {
            std::cout << window[j][k];
        }
        std::cout << endl;
    } 
}

void Chart::drawChar(int coordX, int coordY, string content, string color) {
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

vector<string> Chart::chartPattern(vector<float> steps) {
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
                int whole = (int) up / over;
                // cout << over << endl;
                // cout << up << endl;

                if ( up == 0 ) {
                    up = 1;
                }

                if ( over == 0 ) {
                    over = 1;
                }

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
                for ( int i = 0; i < over; i++) {
                    returnVec.push_back("over");
                }
            }
            else {
                
                if ( up == 0 ) {
                    up = 1;
                }

                if ( over == 0 ) {
                    over = 1;
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
            drawChar(x1,y1,"─", color);
        }
    }
    return returnVec;
}

void Chart::label() {
    vector<int> tl = { posX, posY };
    vector<int> tr = { posX + chartCharWidth - 1, posY };
    vector<int> bl = { posX, posY + chartCharHeight - 1 };
    vector<int> br = { posX + chartCharWidth - 1, posY + chartCharHeight - 1 };


    float min =  *( min_element( data.begin(), data.end() ) );
    float max =  *( max_element( data.begin(), data.end() ) );
    float range = ( max - min );
    float horSteps = (chartCharWidth - 3) / (data.size() - 1);
    float verStepsChart = (Chart::chartCharHeight - 3) / range;

    float newRange = (range - 1) / verStepsChart;
    int x = 1;

    for ( int i = 1; i <= chartCharHeight - 2; i = i + verStepsChart) {

        // cout << "line: " << i << endl;
        // cout << "label: " << x * newRange << endl;
        
        float label = x * newRange;

        ostringstream ss;
        ss << label;
        string s(ss.str());

        // drawChar(-2,i,s,"\e[31m");

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

void Chart::dataDraw() {

    float min =  *( min_element( data.begin(), data.end() ) );
    float max =  *( max_element( data.begin(), data.end() ) );
    float range = ( max - min );

    float horSteps = (chartCharWidth - 3) / (data.size() - 1);
    float verStepsData = range / (Chart::chartCharHeight - 3);
    float verStepsChart = (Chart::chartCharHeight - 3) / range;

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

    vector<string> pattern = removeUpDown(chartPattern(chartSteps));
    // std::cout << "current coordinate: " << charCoord[0] << ", " << charCoord[1] << endl;
    
    for ( int i = 0; i < pattern.size() - 1; i++) {

        // cout << pattern[i] << " ";

        if ( pattern[i] == "over" ) {                
            if (pattern[i + 1] != "up" && pattern[i + 1] != "down" ) {
                charCoord[0]++;
                drawChar(charCoord[0], charCoord[1], lineChars[5], color);
            }
            else {
                charCoord[0]++;
                if ( pattern[i + 1] == "up" ) {
                    drawChar(charCoord[0], charCoord[1], lineChars[3], color);
                }
                else {
                    drawChar(charCoord[0], charCoord[1], lineChars[1], color);
                }
            }
        }
        else if ( pattern[i] == "up" ) {
            if ( pattern[i + 1] != "up" ) {
                if ( pattern[ i + 1 ] == "down" ) {
                    i++;
                    drawChar(charCoord[0], charCoord[1], lineChars[0], color);
                }
                else {
                    charCoord[1]++;
                    drawChar(charCoord[0], charCoord[1], lineChars[0], color);
                }
            }
            else {
                charCoord[1]++;
                drawChar(charCoord[0], charCoord[1], lineChars[4], color);
            }
        }
        else if ( pattern[i] == "down" ) {
            cout << "down " << i << endl;
            if ( pattern[i + 1] != "down" ) {
                if ( pattern[i + 1] == "up" ) {
                    // i++;
                    charCoord[1]--;
                    drawChar(charCoord[0], charCoord[1], lineChars[2], color);
                }
                else {
                    charCoord[1]--;
                    drawChar(charCoord[0], charCoord[1], lineChars[2], color);
                }
            }
            else {
                charCoord[1]--;
                drawChar(charCoord[0], charCoord[1], lineChars[4], color);
            }  
        }

        // cout << "current coordinate: " << charCoord[0] << ", " << charCoord[1] << endl;
        // if ( i + 1 == pattern.size() ) {
        //     cout << "LAST STEP";
        // }
    }

    // HANDLE LAST CHAR HERE BASED ON PREVIOUS CHAR:
    //===============================================
    cout << pattern[pattern.size() - 1] << endl;

    
    // drawChar(charCoord[0], charCoord[1], "t", color);
    //     string addChar;
    //     int increment[2] = {0,0};
    //     if ( pattern[i] == 1 && pattern[i + 1] == 1) {
    //         addChar = lineChars[5];
    //         increment[0] = 1;

    //         // increment curCoordinate
    //     }
    //     else if ( pattern[i] == 1 && pattern[i + 1] == 2) {
    //         addChar = lineChars[3];
    //         increment[0] = 1;
    //         increment[1] = 1;

    //         // increment curCoordinate

    //     }
    //     else if ( pattern[i] == 1 && pattern[i + 1] == 3) {
    //         addChar = lineChars[1];
    //         increment[0] = 1;
    //         increment[1] = -1;

    //         // increment curCoordinate

    //     }
    //     else if ( pattern[i] == 2 && pattern[i + 1] == 1) {
    //         addChar = lineChars[0];
    //         increment[0] = 1;
    //         increment[1] = 1;
    //         // increment curCoordinate

    //     }
    //     else if ( pattern[i] == 2 && pattern[i + 1] == 2) {
    //         addChar = lineChars[4];
    //         increment[0] = 2;
    //         // increment curCoordinate

    //     }
    //     else if ( pattern[i] == 3 && pattern[i + 1] == 1) {
    //         addChar = lineChars[2];
    //         increment[0] = 1;
    //         increment[1] = -1;
    //         // increment curCoordinate
    //     }
    //     else if ( pattern[i] == 3 && pattern[i + 1] == 3) {
    //         addChar = lineChars[4];
    //         increment[1] = -2;
    //         // increment curCoordinate
    //     }
    //     cout << addChar;

    //     // drawChar(charCoord[0],charCoord[1],addChar);

    //     charCoord[0] += increment[0];
    //     charCoord[1] += increment[1];

    //     // draw based on curCoordinate and addChar
    // }
    // window[15][1] = "t";
    // int bottomLeftCoord[2];
    // bottomLeftCoord[0] = posX + 1;
    // bottomLeftCoord[1] = posY + chartCharHeight - 2;

    // window[bottomLeftCoord[1]][bottomLeftCoord[0]] = "\e[31m┐\e[0m";

}
