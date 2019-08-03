#include <iostream>

using namespace std;

int main(int argc, char *argv[]) {

    bool dataInc = false;
    bool typeInc = false;

    int dataCount;
    int typeCount;

    string chartType;

    for (int i = 1; i < argc; i++) {
        // if ( argv[i] == string("-d")) {
        //     dataInc = true;
        // }
        // else {
        //     if ( dataInc == true ) {
        //         cout << "data:" << argv[i] << endl;

        //         if ( dataCount == 2 ){
        //             cout << "Too many data series!\n";
        //             exit (EXIT_FAILURE);
        //         }
        //         dataCount++;
        //     }
        //     else {
        //         cout << argv[i] << endl;
        //     }
        //     dataInc = false;
        // }


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
    std::cout << "Chart type:" << chartType << endl;
}


