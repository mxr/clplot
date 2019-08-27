#include <iostream>
#include "chart.hpp"

using namespace std;

int main(int argc, char *argv[]) {

    bool dataInc = false;
    bool typeInc = false;

    int dataCount;
    int typeCount;

    string chartType;
    string dataStr;

    for (int i = 1; i < argc; i++) {
        if ( argv[i] == string("-d")) {
            dataInc = true;
        }
        else {
            if (dataInc) {
                dataStr = argv[i];
                if ( dataCount == 1 ){
                    cout << "Multiple data series are not supported yet. Please use a single -d flag.\n";
                    exit (EXIT_FAILURE);
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
                    exit (EXIT_FAILURE);
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

    Chart chart;
    cout << "Chart information:\n==================\n";

    chart.addType(chartType);
    cout << "Chart type: " << chart.getType() << endl;

    chart.addData(dataStr);
    cout << "Chart data: ";
    vector<float> data = chart.getData();
    for (int i = 0; i < data.size(); i++) {
        cout << noshowpoint << data[i] << " ";
    }
    cout << endl;

}


