#include <string>
#include <vector>

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
        void winSet(int height, int width, int posX, int posY, int termHeight, int termWidth);
        void move();

        // drawing methods
        void draw(int termHeight, int termWidth);
        void drawChar(int coordX, int coordY, string content, string color);
        string getChar(int coordX, int coordY);
};


class Linechart : public Chart {

    // various line characters
    vector<string> chars = { "╭", "╮", "╰", "╯", "│", "─" };
    vector<string> charsBold = { "╔", "╗", "╚", "╝", "║", "═" };
    vector<string> charsArea = { "▗", "▖", "▙", "▟" , "▐" , "▄" };
    vector<string> sharpChars = { "┌", "┐", "└", "┘", "│", "─" };
    
    bool area;
    
    public:
        void label();
        void dataDraw();
        vector<string> pattern(vector<float> steps);
};


class Barchart : public Chart {
    vector<string> chars = { "▁", "▂" "▃", "▄", "▅", "▆", "▇", "█" };
    
    public:
        void label();
        void dataDraw();
};