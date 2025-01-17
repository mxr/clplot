#include <string>
#include <vector>
#include <iostream>
#include <sys/ioctl.h>
#include <unistd.h>
#include <sstream> 
#include <map>
#include <string.h>
#include <string>
#include <ctype.h>
#include <cstdlib>  
#include <random>
#include <algorithm>

using namespace std;
    
class Chart {

    public: 
        int width;
        int height;
        int posY;
        int posX;
        int chartCharWidth;
        int chartCharHeight;

        string color;
        string type;

        vector<float> data;
        vector<vector<string> > window;
        vector<string> winChars = { "╭", "╮", "╰", "╯", "│", "─" };
        vector<string> winCharsSharp = { "┌", "┐", "└", "┘", "│", "─" };

    public:
        
        // metadata methods
        void addColor(string newColor);
        void addType(string type);
        string getType();
        void addData(string data, int lines, int cols);
        vector<float> getData();

        // window methods
        void winSet(int chartheight, int chartwidth, int positionX, int positionY);
        void move();

        // drawing methods
        void draw();
        string getChar(int coordX, int coordY);
};


class Linechart : public Chart {

    // various line characters
    vector<string> chars = { "╭", "╮", "╰", "╯", "│", "─", "│"};
    vector<string> charsBold = { "╔", "╗", "╚", "╝", "║", "═", "║" };
    vector<string> charsArea = { "▗", "▖", "▙", "▟" , "▌" , "▄", "▐" };
    vector<string> sharpChars = { "┌", "┐", "└", "┘", "│", "─", "│" };
    
    bool area;
    
    public:
    // constructor
        Linechart(string newType, string newData, int lines, int cols, string newColor, bool areachart);
        
        void drawChar(int coordX, int coordY, string content, string color);
        void label();
        void dataDraw();
        vector<string> pattern(vector<float> steps);
};


class Barchart : public Chart {
    vector<string> chars = { "▁", "▂" "▃", "▄", "▅", "▆", "▇", "█" };

    public:
        Barchart(string newType, string newData, int lines, int cols, string newColor);

        void label();
        void dataDraw();
        void drawChar(int coordX, int coordY, string content, string color);
};