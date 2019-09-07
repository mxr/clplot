#include <iostream>
#include "../include/chart.hpp"
// #include <ncurses.h>
#include <sys/ioctl.h>
#include <stdio.h>
#include <unistd.h>
#include <vector>

using namespace std;

bool dataCheck(string dataStr) {

    string b1 = dataStr.substr(0,1);
    string b2 =  dataStr.substr(dataStr.length() - 1,1);

    if ( b1 != "[" || b2 != "]") {
        return false;
    }
    return true;
}

bool typeCheck(string type) {
    vector<string> dataTypes = { "line", "bar" };
    if (find(dataTypes.begin(), dataTypes.end(), type) != dataTypes.end()) {
        return true;
    }
    return false;
    
}

void chartTypes() {
    vector<string> dataTypes = { "line", "bar" };
    cout << "\nThe following are currently accepted chart types: \e[33m";
    for ( int i = 0; i < dataTypes.size() - 1; i++) {
        cout << dataTypes[i] << ", ";
    }
    cout << dataTypes[dataTypes.size() - 1] << endl;
}

bool sizeCheck(int height, int termHeight, int min) {

    if ( height > min && height <= termHeight) {
        // cout << height << endl;
        return true;
    }

    return false;
}

int main(int argc, char *argv[]) {
    
    // Define the window size
    //====================
    int cols, lines;

    struct ttysize ts;
    ioctl(STDIN_FILENO, TIOCGSIZE, &ts);
    cols = ts.ts_cols;
    lines = ts.ts_lines;


    bool dataSet = false;
    bool typeSet = false;
    bool widthSet = false;
    bool heightSet = false;

    int dataCount;
    int typeCount;
    int chartHeight = lines;
    int chartWidth = cols;
    int posX = 0;
    int posY = 0;

    string chartType = "line";
    string dataStr;



    //-==================================================
    //   Records the data series in the dataStr variable
    //===================================================
    for (int i = 1; i < argc; i++) {
        
        if ( argv[i] == string("-d")) {
            if (dataSet) {
                cout << "chart: \e[91merror: \e[0mMultiple data series is not supported yet. Call the program with only one instance of the -d flag." << endl;
                return 1;
            }
            
            if (dataCheck(argv[i+1])) {
                dataStr = argv[i + 1];
            }
            else {
                cout << "chart: \e[91merror: \e[0m\"" << argv[i+1] << "\"" << " is not in the correct data format." << endl;
                return 1;
            }
            
            dataSet = true;
        }
        else if (argv[i] == string("-t")) {
            if (typeSet) {
                cout << "chart: \e[91merror: \e[0mOnly one chart type can be used. Use only one instance of the -t flag." << endl;
                return 1;
            }

            if (typeCheck(argv[i+1])) {
                chartType = argv[i + 1];
            }
            else {
                cout << "chart: \e[91merror: \e[0m\"" << argv[i+1] << "\"" << " is not a recognized chart type." << endl;
                chartTypes();
                return 1;
            }
            
            typeSet = true;
        }
        else if (argv[i] == string("-h")) {
            if (heightSet) {
                cout << "chart: \e[91merror: \e[0mHeight can only be set once" << endl;
                return 1;
            }

            if (sizeCheck(stoi(argv[i + 1]), lines, 5)) {
                chartHeight = stoi(argv[i + 1]);
            }
            else {
                cout << "chart: \e[91merror: \e[0mThe height must be an integer number of lines between 5 and the terminal height, " << lines << "." << endl;
                return 1;
            }
            
            heightSet = true;
        }
        else if (argv[i] == string("-w")) {
            if (widthSet) {
                cout << "chart: \e[91merror: \e[0mWidth can only be set once" << endl;
                return 1;
            }

            if (sizeCheck(stoi(argv[i + 1]), cols, 8)) {
                chartWidth = stoi(argv[i + 1]);
            }
            else {
                cout << "chart: \e[91merror: \e[0mThe width must be an integer number of rows between 8 and the terminal width, " << cols << "." << endl;
                return 1;
            }
            
            widthSet = true;
        }

    }

    if ( dataStr == "" ) {
        cout << "chart: \e[91merror: \e[0mData must be passed to chart with the -d flag. See the readme for more information." << endl;
        return 1;
    }

    // Create chart object
    //====================
    Chart chart;

    chart.addType(chartType);
    chart.addData(dataStr, lines, cols);
    // chart.addSize(chartHeight, chartWidth, chartPosX, chartPosY);


    cout << "Chart type: " << chart.getType() << endl;
    cout << "Chart data: ";
    vector<float> data = chart.getData();
    for (int i = 0; i < data.size(); i++) {
        cout << noshowpoint << data[i] << " ";
    }
    // cout << "\e[91mtest";

    cout << endl;
    
}


