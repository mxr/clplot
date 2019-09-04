#include <iostream>
#include "../include/chart.hpp"
// #include <ncurses.h>
#include <sys/ioctl.h>
#include <stdio.h>
#include <unistd.h>

using namespace std;

int main(int argc, char *argv[]) {

    bool dataInc = false;
    bool typeInc = false;

    int dataCount;
    int typeCount;

    string chartType;
    string dataStr;

    //-==================================================
    //   Records the data series in the dataStr variable
    //===================================================

    for (int i = 1; i < argc; i++) {
        if ( argv[i] == string("-d")) {
            dataInc = true;
        }
        else {
            if (dataInc) {
                dataStr = argv[i];
                if ( dataCount == 1 ){
                    cout << "Multiple data series are not supported yet. Please use a single -d flag.\n";
                    return 1;
                }
                dataCount++;
            }
            else {
                cout << "";
            }
            dataInc = false;
        }

        //-==================================================
        //   Records the data type in the chartType variable
        //===================================================
        if ( argv[i] == string("-t")) {
            typeInc = true;
        }
        else {
            int plus = i + 1;

            if (typeInc) {
                if ( typeCount == 1 ) {
                    std::cout << "chart: ERROR: Only one chart type may be specified." << endl;
                    return 1;
                }
                chartType = argv[i]; 
                typeCount++;
            }
            else if ( typeCount == 0 && plus == argc ) {
                chartType = "default";
            }
            typeInc = false;
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
    // for (int i = 0; i < data.size(); i++) {
    //     cout << noshowpoint << data[i] << " ";
    // }
    cout << "\e[31mtest";

    cout << endl;
    
}


