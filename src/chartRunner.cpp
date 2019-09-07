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
    // vector<string> dataTypes = { "line", "bar" };
    // if (find(dataTypes.begin(), dataTypes.end(), type) != dataTypes.end()) {
    //     return true;
    // }
    return true;
    
}

bool heightCheck(int height, int termHeight) {
    if ( height > 5 && height <= termHeight) {
        return true;
        cout << height << endl;
    }

    return false;
}

int main(int argc, char *argv[]) {

    bool dataSet = false;
    bool typeSet = false;
    bool widthSet = false;
    bool heightSet = false;

    int dataCount;
    int typeCount;
    int chartHeight;
    int chartWidth;

    string chartType = "bar";
    string dataStr;

    // Define the window size
    //====================
    int cols, lines;

    struct ttysize ts;
    ioctl(STDIN_FILENO, TIOCGSIZE, &ts);
    cols = ts.ts_cols;
    lines = ts.ts_lines;

    //-==================================================
    //   Records the data series in the dataStr variable
    //===================================================
    for (int i = 1; i < argc; i++) {
        
        if ( argv[i] == string("-d")) {
            if (dataSet) {
                cout << "chart: ERROR: Multiple data series is not supported yet. Call the program with only one instance of the -d flag." << endl;
                return 1;
            }
            
            if (dataCheck(argv[i+1])) {
                dataStr = argv[i + 1];
            }
            else {
                cout << "chart: ERROR: \"" << argv[i+1] << "\"" << " is not in the correct data format." << endl;
                return 1;
            }
            
            dataSet = true;
        }
        else if (argv[i] == string("-t")) {
            if (typeSet) {
                cout << "chart: ERROR: Only one chart type can be used. Use only one instance of the -t flag." << endl;
                return 1;
            }

            if (typeCheck(argv[i+1])) {
                chartType = argv[i + 1];
            }
            else {
                cout << "chart: ERROR: \"" << argv[i+1] << "\"" << " is not a recognized chart type." << endl;
                return 1;
            }
            
            typeSet = true;
        }
        else if (argv[i] == string("-h")) {
            if (heightSet) {
                cout << "Height can only be set once" << endl;
                return 1;
            }

            if (heightCheck(stoi(argv[i + 1]), lines)) {
                chartHeight = stoi(argv[i + 1]);
            }
            else {
                cout << "chart: ERROR: The height must be an integer number of lines between 5 and the terminal height," << lines << "." << endl;
                return 1;
            }
            
            heightSet = true;
        }

    }

    if ( dataStr == "" ) {
        cout << "Data must be specified with the -d flag. See the readme for more information." << endl;
        return 1;
    }

    // Create chart object
    //====================
    Chart chart;

    chart.addType(chartType);
    chart.addData(dataStr, lines, cols);

    cout << "Chart type: " << chart.getType() << endl;
    cout << "Chart data: ";
    vector<float> data = chart.getData();
    for (int i = 0; i < data.size(); i++) {
        cout << noshowpoint << data[i] << " ";
    }
    // cout << "\e[31mtest";

    cout << endl;
    
}


