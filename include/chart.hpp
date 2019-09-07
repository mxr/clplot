#include <string>
#include <vector>

using namespace std;

class Chart {

  int width;
  int height;
  int topCoordY;
  int topCoordX;

  string type;
  vector<float> data;

public:
    void addType(string type);
    string getType();

    void addData(string data, int lines, int cols);
    vector<float> getData();

    void addPos(string position);
};