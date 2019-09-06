#include <iostream>
#include "../include/chart.hpp"
// #include <ncurses.h>
#include <sys/ioctl.h>
#include <stdio.h>
#include <unistd.h>

using namespace std;

bool dataCheck(string data) {
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
                cout << "Multiple data series is not supported yet. Call the program with only on instance of the -d flag." << endl;
                return 1;
            }
            dataStr = argv[i + 1];
            dataSet = true;
        }
        else if (argv[i] == string("-t")) {
            chartType = argv[i + 1];
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


