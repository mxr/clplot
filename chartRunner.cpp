#include <iostream>

using namespace std;

int main(int argc, char *argv[]) {

    bool dataInc = false;

    for (int i = 1; i < argc; i++) {
        if ( argv[i] == string("-d")) {
            dataInc = true;
        }
        else {
            if ( dataInc == true ) {
                cout << "data:" << argv[i] << endl;
            }
            else {
                cout << argv[i] << endl;
            }
            dataInc = false;
        }
    }
}


