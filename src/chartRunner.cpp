#include <iostream>
#include "../include/chart.hpp"
#include <sys/ioctl.h>
#include <stdio.h>
#include <unistd.h>
#include <sstream> 
#include <map>
#include <string.h>
#include <ctype.h>

using namespace std;

inline bool isInteger(const string & s) {
    if ( s.empty() || ((!isdigit(s[0])) && (s[0] != '-') && (s[0] != '+'))) {
        return false;
    }
    
    char * p;
    strtol(s.c_str(), &p, 10);
    return (*p == 0);
}

string lower(string one) {
    string returnstring;
    std::locale loc;
    for (std::string::size_type i=0; i<one.length(); ++i)
        returnstring += std::tolower(one[i],loc);
    return returnstring;
}

bool dataCheck(string dataStr) {
    string b1 = dataStr.substr(0,1);
    string b2 =  dataStr.substr(dataStr.length() - 1,1);

    if ( b1 != "[" || b2 != "]") {
        return false;
    }
    string removed = dataStr.substr(1, dataStr.length() - 2);
    // cout << removed << endl;
    return true;
}

bool typeCheck(string type) {
    vector<string> dataTypes = { "line", "bar" };
    if (find(dataTypes.begin(), dataTypes.end(), type) != dataTypes.end()) {
        return true;
    }
    return false;
    
}

bool sizeCheck(int height, int termHeight, int min) {
    if ( height > min && height <= termHeight) {
        return true;
    }
    return false;
}

bool colorCheck(string colors) {
    map<string, int> colorList { 
        { "black", 0 }, 
        { "red", 1 }, 
        { "green", 2 }, 
        { "yellow", 3 }, 
        { "blue", 4 }, 
        { "magenta", 5 }, 
        { "purple", 5 }, 
        { "cyan", 6 }, 
        { "gray", 8 }, 
        { "white", 15 }, 
        { "orange", 208 },     
        { "light red", 9 }, 
        { "light orange", 214 }, 
        { "light yellow", 11 }, 
        { "light green", 10 }, 
        { "light blue", 12 }, 
        { "light cyan", 14 }, 
        { "light magenta", 13 }, 
        { "light purple", 13 } 
    }; 

    // int colorNum;

    if ( isInteger(colors) ) {
        if ( stoi(colors) > 0 && stoi(colors) < 256 ) {
            return true;
        }
        return false;
    }
    else {
        string search = lower(colors);
        if ( colorList.find(search) == colorList.end() ) {
            return false;
        }
        else {
            return true;
            // colorNum = colorList[search];
        }
    }
}

string getColor(string colors) {
    map<string, int> colorList { 
        { "black", 0 }, 
        { "red", 1 }, 
        { "green", 2 }, 
        { "yellow", 3 }, 
        { "blue", 4 }, 
        { "magenta", 5 }, 
        { "purple", 5 }, 
        { "cyan", 6 }, 
        { "gray", 8 }, 
        { "white", 15 }, 
        { "orange", 208 },     
        { "light red", 9 }, 
        { "light orange", 214 }, 
        { "light yellow", 11 }, 
        { "light green", 10 }, 
        { "light blue", 12 }, 
        { "light cyan", 14 }, 
        { "light magenta", 13 }, 
        { "light purple", 13 } 
    }; 

    int colorNum;

    if ( isInteger(colors) ) {
        if ( stoi(colors) > 0 && stoi(colors) < 256 ) {
            colorNum = stoi(colors);
        }
    }
    else {
        string search = lower(colors);
        colorNum = colorList[search];
    }
}

bool posCheck(string data) {
    size_t commaCount = count(data.begin(), data.end(), ',');

    if ( commaCount == 1 ) {
        replace(data.begin(), data.end(), ',', ' ');
        vector<string> positions;
        stringstream ss(data);
        string temp;

        while (ss >> temp) 
            positions.push_back(temp);

        if (positions.size() == 2 && isInteger(positions[0]) && isInteger(positions[1])) {
            return true;
        }
    }
    
    return false;
}

void chartTypes() {
    vector<string> dataTypes = { "line", "bar" };
    cout << "\nThe following are currently accepted chart types: \e[33m";
    for ( int i = 0; i < dataTypes.size() - 1; i++) {
        cout << dataTypes[i] << ", ";
    }
    cout << dataTypes[dataTypes.size() - 1] << endl;
}

int main(int argc, char *argv[]) {
    
    // Define the window size
    //====================
    int cols, lines;

    struct ttysize ts;
    ioctl(STDIN_FILENO, TIOCGSIZE, &ts);
    cols = ts.ts_cols;
    lines = ts.ts_lines;


    bool dataSet = false;
    bool typeSet = false;
    bool widthSet = false;
    bool heightSet = false;
    bool colorSet = false;
    bool posSet = false;

    bool sparkline = false;

    int dataCount;
    int typeCount;
    int chartHeight = lines - 2;
    int chartWidth = cols - 1;
    int posX = 0;
    int posY = 0;

    string color = "\e[38;5;15m";

    string chartType = "line";
    string dataStr;



    //-==================================================
    //  Records the arguments, checks for errors in data
    //===================================================
    for (int i = 1; i < argc; i++) {
        
        if ( argv[i] == string("-d")) {
            if (dataSet) {
                cout << "chart: \e[91merror: \e[0mMultiple data series is not supported yet. Call the program with only one instance of the \e[93m-d\e0m flag." << endl;
                return 1;
            }
            
            if (dataCheck(argv[i+1])) {
                dataStr = argv[i + 1];
            }
            else {
                cout << "chart: \e[91merror: \e[0mThe data \"\e[93m" << argv[i+1] << "\e[0m\"" << " is not in the correct format." << endl;
                return 1;
            }
            
            dataSet = true;
        }
        else if (argv[i] == string("-t")) {
            if (typeSet) {
                cout << "chart: \e[91merror: \e[0mOnly one chart type can be used. Use only one instance of the -t flag." << endl;
                return 1;
            }

            if (typeCheck(argv[i+1])) {
                chartType = argv[i + 1];
            }
            else {
                cout << "chart: \e[91merror: \e[0m\"" << argv[i+1] << "\"" << " is not a recognized chart type." << endl;
                chartTypes();
                return 1;
            }
            
            typeSet = true;
        }
        else if (argv[i] == string("-s")) {
            sparkline = true;
        }
        else if (argv[i] == string("-h")) {
            if (heightSet) {
                cout << "chart: \e[91merror: \e[0mHeight can only be set once" << endl;
                return 1;
            }

            if (sizeCheck(stoi(argv[i + 1]), lines, 5)) {
                chartHeight = stoi(argv[i + 1]);
            }
            else {
                cout << "chart: \e[91merror: \e[0mThe height must be an integer number of lines between 5 and the terminal height, " << lines << "." << endl;
                return 1;
            }
            
            heightSet = true;
        }
        else if (argv[i] == string("-c")) {
            // cout << "color" << endl;
            if (colorSet) {
                cout << "chart: \e[91merror: \e[Color can only be set once" << endl;
                return 1;
            }

            if (colorCheck(argv[i + 1])) {
                color = getColor(argv[i + 1]);
            }
            // else {
            //     cout << "chart: \e[91merror: \e[0mThe height must be an integer number of lines between 5 and the terminal height, " << lines << "." << endl;
            //     return 1;
            // }
            
            // heightSet = true;
        }
        else if (argv[i] == string("-w")) {
            if (widthSet) {
                cout << "chart: \e[91merror: \e[0mWidth can only be set once" << endl;
                return 1;
            }

            if (sizeCheck(stoi(argv[i + 1]), cols, 8)) {
                chartWidth = stoi(argv[i + 1]);
            }
            else {
                cout << "chart: \e[91merror: \e[0mThe width must be an integer number of rows between 8 and the terminal width, " << cols << "." << endl;
                return 1;
            }
            
            widthSet = true;
        }
        else if (argv[i] == string("-p")) {
            if (posSet) {
                cout << "chart: \e[91merror: \e[0mWidth can only be set once" << endl;
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
                cout << "chart: \e[91merror: \e[0m\"\e[93m" << argv[i+1] << "\e[0m\" is an invalid position. Position must in the format \"\e[93mx,y\e[0m\"." << endl;
                return 1;
            }
            
            posSet = true;
        }

    }

    // todo - make this the first error test

    if ( dataStr == "" ) {
        cout << "chart: \e[91merror: \e[0mData must be passed to chart with the -d flag. See the readme for more information." << endl;
        return 1;
    }


    // increment positions to allow room for scales (if sparkline option not set)
    posY++;
    if (!sparkline) {
        posX++;
    }

    // Create chart object
    //====================
    Chart chart;

    chart.addType(chartType);
    chart.addData(dataStr, lines, cols);
    chart.winSet(chartHeight, chartWidth, posX, posY, lines, cols);
    chart.dataDraw();

    chart.draw(lines,cols);

}