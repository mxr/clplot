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

int main(int argc, char *argv[]) {

    bool dataSet = false;
    bool typeSet = false;

    int dataCount;
    int typeCount;

    string chartType;
    string dataStr;

    //-==================================================
    //   Records the data series in the dataStr variable
    //===================================================

    for (int i = 1; i < argc; i++) {
        if ( argv[i] == string("-d")) {
            if (dataSet) {
                cout << "Multiple data series is not supported yet. Call the program with only one instance of the -d flag." << endl;
                return 1;
            }
            
            if (dataCheck(argv[i+1])) {
                dataStr = argv[i + 1];
            }
            else {
                cout << "\"" << argv[i+1] << "\"" << " is not in the correct data format." << endl;
                return 1;
            }
            
            dataSet = true;
        }
        else if (argv[i] == string("-t")) {
            if (typeSet) {
                cout << "Only one chart type can be used. Use only one instance of the -t flag." << endl;
                return 1;
            }

            if (typeCheck(argv[i+1])) {
                chartType = argv[i + 1];
            }
            else {
                cout << "\"" << argv[i+1] << "\"" << " is not a recognized chart type." << endl;
                return 1;
            }
            
            typeSet = true;
        }
    }

    // Define the window size
    //====================
    int cols, lines;

    struct ttysize ts;
    ioctl(STDIN_FILENO, TIOCGSIZE, &ts);
    cols = ts.ts_cols;
    lines = ts.ts_lines;

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


