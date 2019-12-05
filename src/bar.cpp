// bar chart methods
#include "../include/chart.hpp"
#include <math.h>

using namespace std;

void Barchart::drawChar(int coordX, int coordY, string content, string color) {
    coordX--;
    coordY--;

    int bl[2];

    bl[1] = posX + 1; 
    bl[0] = posY + chartCharHeight - 2;

    int coord[2] = {bl[0] - coordY, bl[1] + coordX};

    if ( coord[0] < 0 ) {
        cout << "Error - the coord[0] cannot be lt 0" << endl;
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
    int widthPadding = 3;
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