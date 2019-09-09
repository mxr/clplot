#include <string>
#include <vector>

using namespace std;
    
class Chart {
  vector<string> lineChars = { "╭", "╮", "╰", "╯", "│", "─" };

  // vector<string> lineChars = { "╔", "╖", "╙", "╝", "║", "═" };

  int width;
  int height;
  int posY;
  int posX;

  int chartCharWidth;
  int chartCharHeight;
  
  string type;
  vector<float> data;

  vector<vector<string> > window;

public:
    void addType(string type);
    string getType();

    void addData(string data, int lines, int cols);
    vector<float> getData();

    void winSet(int height, int width, int posX, int posY, int termHeight, int termWidth);

    void draw(int termHeight, int termWidth);

    void dataDraw();
};