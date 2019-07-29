#include <iostream>

using namespace std;

int main(int argc, char *argv[]) {

    bool dataInc = false;
    int dataCount;

    for (int i = 1; i < argc; i++) {
        if ( argv[i] == string("-d")) {
            dataInc = true;
        }
        else {
            if ( dataInc == true ) {
                cout << "data:" << argv[i] << endl;

                if ( dataCount == 2 ){
                    cout << "Too many data series!\n";
                    exit (EXIT_FAILURE);
                }
                dataCount++;
            }
            else {
                cout << argv[i] << endl;
            }
            dataInc = false;
        }
    }
}


