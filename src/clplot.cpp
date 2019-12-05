#include "../include/chart.hpp"
#include "../include/args.hpp"

using namespace std;


int main(int argc, char *argv[]) {
    
    // Define the window size
    //==================== 
    int cols, lines;

    struct winsize size;
    ioctl(STDOUT_FILENO,TIOCGWINSZ,&size);

    lines = size.ws_row;
    cols = size.ws_col;

    // cout << lines << ", " << cols << endl;

    bool dataSet = false;
    bool typeSet = false;
    bool widthSet = false;
    bool heightSet = false;
    bool colorSet = false;
    bool posSet = false;

    bool sparkline = false;
    bool areachart = false;

    int dataCount;
    int typeCount;
    int chartHeight = lines - 1;
    int chartWidth = cols - 1;
    int posX = 0;
    int posY = 0;

    string usageScreen = "usage: clplot [-s] -d data";
    string color = "\e[38;5;15m";

    string chartType = "line";
    string dataStr;



    //-==================================================
    //  Records the arguments, checks for errors in data
    //===================================================
    for (int i = 1; i < argc; i++) {
        
        if ( argv[i] == string("-d") || argv[i] == string("--data")) {
            if (dataSet) {
                cout << "clplot: \e[91merror: \e[0mMultiple data series is not supported yet. Call the program with only one instance of the \e[93m-d\e0m flag." << endl;
                return 1;
            }
            
            if (dataCheck(argv[i+1])) {
                dataStr = argv[i + 1];
            }
            else {
                cout << "clplot: \e[91merror: \e[0mThe data \"\e[93m" << argv[i+1] << "\e[0m\"" << " is not in the correct format." << endl;
                return 1;
            }
            
            dataSet = true;
        }
        else if (argv[i] == string("-t") || argv[i] == string("--type")) {
            if (typeSet) {
                cout << "clplot: \e[91merror: \e[0mOnly one chart type can be used. Use only one instance of the -t flag." << endl;
                return 1;
            }

            if (typeCheck(argv[i+1])) {
                chartType = argv[i + 1];
            }
            else {
                cout << "clplot: \e[91merror: \e[0m\"" << argv[i+1] << "\"" << " is not a recognized chart type." << endl;
                chartTypes();
                return 1;
            }
            
            typeSet = true;
        }
        else if (argv[i] == string("-a") || argv[i] == string("--area")) {
            areachart = true;
        }
        else if (argv[i] == string("-s") || argv[i] == string("--sparkline")) {
            sparkline = true;
        }
        else if (argv[i] == string("-h") || argv[i] == string("--height")) {
            if (heightSet) {
                cout << "clplot: \e[91merror: \e[0mHeight can only be set once" << endl;
                return 1;
            }

            if (sizeCheck(stoi(argv[i + 1]), lines, 5)) {
                chartHeight = stoi(argv[i + 1]);
            }
            else {
                cout << "clplot: \e[91merror: \e[0mThe height must be an integer number of lines between 5 and the terminal height, " << lines << "." << endl;
                return 1;
            }
            
            heightSet = true;
        }
        else if (argv[i] == string("-c") || argv[i] == string("--color")) {
            // cout << "color" << endl;
            if (colorSet) {
                cout << "clplot: \e[91merror: \e[0mColor can only be set once" << endl;
                return 1;
            }

            if (colorCheck(argv[i + 1])) {
                color = getColor(argv[i + 1]);
            }
            else {
                cout << "clplot: \e[91merror: \"\e[93m" << argv[i + 1] << "\e[0m\" is not recognized as a color." << endl;
                return 1;
            }
            
            colorSet = true;
        }
        else if (argv[i] == string("-w") || argv[i] == string("--width")) {
            if (widthSet) {
                cout << "clplot: \e[91merror: \e[0mWidth can only be set once" << endl;
                return 1;
            }

            if (sizeCheck(stoi(argv[i + 1]), cols, 8)) {
                chartWidth = stoi(argv[i + 1]);
            }
            else {
                cout << "clplot: \e[91merror: \e[0mThe width must be an integer number of rows between 8 and the terminal width, " << cols << "." << endl;
                return 1;
            }
            
            widthSet = true;
        }
        else if (argv[i] == string("-p") || argv[i] == string("--position")) {
            if (posSet) {
                cout << "clplot: \e[91merror: \e[0mPosition can only be set once" << endl;
                return 1;
            }

            if (posCheck(argv[i+1])) {

                    string posString = argv[i+1];
                    replace(posString.begin(), posString.end(), ',', ' ');

                    vector<int> positions;
                    stringstream ss(posString);
                    int temp;

                    while (ss >> temp) {
                        positions.push_back(temp);
                    }

                    posX = positions[0];
                    posY = positions[1];

            }
            else {
                cout << "clplot: \e[91merror: \e[0m\"\e[93m" << argv[i+1] << "\e[0m\" is an invalid position. Position must in the format \"\e[93mx,y\e[0m\"." << endl;
                return 1;
            }
            
            posSet = true;
        }
        else if ( argv[i] == string("-h") || argv[i] == string("--help") ) {
            system("printf \"$(cat man)\" | less -r");
            return 1;
        }
        else  {
            vector<string> args = { "-d", "-t", "-c", "-h", "-w", "-p", "--data", "--type", "--color", "--height", "--width", "--position" };
            if (!( find(args.begin(), args.end(), argv[i - 1]) != args.end() )) {
                cout << "clplot: \e[91merror: \e[0m\"\e[33m" << argv[i] << "\e[0m\" is not a recognized argument.\nArguments and values must be separated by spaces.\n" << endl;
                cout << usageScreen << endl;
                return 1;
            }
        }

    }

    // todo - make this the first error test

    if ( dataStr == "" ) {
        string newData;
        for (string line; getline(std::cin, line);) {
            newData+=line;
        }
        if (newData != "") {
            dataStr = "[" + newData + "]";
            dataCheck(dataStr);
        }
        else {
            cout << "clplot: \e[91merror: \e[0mData must be passed to chart with the -d flag or with stdin. See the readme for more information." << endl;
            return 1;        
        }
    }

    if ( areachart && chartType != "line" ) {
        cout << "clplot: \e[91merror: \e[0mThe \e[93marea\e[0m chart option can only be used with the \e[93mline\e[0m chart type. \nUse \e[93m-t 'line'\e[0m instead of \e[93m-t '" << chartType << "'\e[0m." << endl;
    }


    // increment positions to allow room for scales (if sparkline option not set)
    posY++;
    if (!sparkline) {
        posX++;
    }

    // Create chart object
    //====================
    if ( chartType == "line" ) {

        Linechart chart(chartType, dataStr, lines, cols, color, areachart);

        chart.winSet(chartHeight, chartWidth, posX, posY);
        chart.dataDraw();

        if ( !sparkline ) {
            chart.label();
        } 

        chart.draw();
    }
    else if ( chartType == "bar" ) {
        Barchart chart(chartType, dataStr, lines, cols, color);

        chart.winSet(chartHeight, chartWidth, posX, posY);
        chart.dataDraw();
        chart.draw();
    }

    
    return 0;
}