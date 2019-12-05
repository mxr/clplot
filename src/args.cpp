#include <string>
#include <vector>
#include <map>
#include <sstream>
#include <iostream>
#include <random>

using namespace std;

// checks string for integer status
inline bool isInteger(const string & s) {
    if ( s.empty() || ((!isdigit(s[0])) && (s[0] != '-') && (s[0] != '+'))) {
        return false;
    }
    
    char * p;
    strtol(s.c_str(), &p, 10);
    return (*p == 0);
}

// string to lower case
string lower(string one) {
    string returnstring;
    std::locale loc;
    for (std::string::size_type i=0; i<one.length(); ++i)
        returnstring += std::tolower(one[i],loc);
    return returnstring;
}

// checks data for correct format
bool dataCheck(string dataStr) {
    // TODO: check data for float/int status
    string b1 = dataStr.substr(0,1);
    string b2 =  dataStr.substr(dataStr.length() - 1,1);

    if ( b1 != "[" || b2 != "]") {
        return false;
    }
    string removed = dataStr.substr(1, dataStr.length() - 2);
    return true;
}

// checks for type in vector
bool typeCheck(string type) {
    vector<string> dataTypes = { "line", "bar" };
    if (find(dataTypes.begin(), dataTypes.end(), type) != dataTypes.end()) {
        return true;
    }
    return false;
    
}

// print the chart error message
void chartTypes() {
    vector<string> dataTypes = { "line", "bar" };
    cout << "\nThe following are currently accepted chart types: \e[33m";
    for ( int i = 0; i < dataTypes.size() - 1; i++) {
        cout << dataTypes[i] << ", ";
    }
    cout << dataTypes[dataTypes.size() - 1] << endl;
}

// check specified size for terminal limits
bool sizeCheck(int height, int termHeight, int min) {
    if ( height > min && height <= termHeight) {
        return true;
    }
    return false;
}

// check if string is in map
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
        { "orange", 202 },     
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
        if (colors == "rand[]" ) {
            return true;
        }
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

// return string's integer in map
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


    vector<int> randVec = {0,1,2,3,4,5,6,8,15,208,9,214,11,10,12,14,13};
    random_device random_device;
    mt19937 engine{random_device()};
    uniform_int_distribution<int> dist(0, randVec.size() - 1);
    int random_element = randVec[dist(engine)];


    int colorNum = 15;
    string colorString;
    string search;

    if ( isInteger(colors) ) {
        if ( stoi(colors) > 0 && stoi(colors) < 256 ) {
            colorNum = stoi(colors);
        }
    }
    else {
        if ( colors == "rand[]" ) {
            colorNum = random_element;
        }
        else {
            search = lower(colors);
            colorNum = colorList[search];
        }

    }

    colorString += "\e[38;5;";
    colorString += to_string(colorNum);
    colorString += "m";

    return colorString;
}

// check the format of position data
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