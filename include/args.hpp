using namespace std;

inline bool isInteger(const string & s);               // checks string for integer status
string lower(string one);                              // string to lower case
bool dataCheck(string dataStr);                        // checks data for correct format
bool typeCheck(string type);                           // checks for type in vector
void chartTypes();                                     // print the chart error message
bool sizeCheck(int height, int termHeight, int min);   // check specified size for terminal limits
bool colorCheck(string colors);                        // check if string is in map
string getColor(string colors);                        // return string's integer in map
bool posCheck(string data);                            // check the format of position data