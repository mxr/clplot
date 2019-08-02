#include <iostream>

using namespace std;

int main(int argc, char *argv[]) {

    bool dataInc = false;
    bool typeInc = false;

    int dataCount;
    int typeCount;

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
        if ( argv[i] == string("-t")) {
            typeInc = true;
        }
        else {
            int plus = i + 1;

            if (typeInc) {
                if ( typeCount == 1 ) {
                    cout << "Only one type is supported." << endl;
                    exit (EXIT_FAILURE);
                }
                cout << "type:" << argv[i] << endl;
                typeCount++;
            }
            else if ( typeCount == 0 && plus == argc ) {
                cout << "type: default" << endl;
            }
            typeInc = false;
        }
    }
}


