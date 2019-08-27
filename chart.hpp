#include <string>
#include <vector>

using namespace std;

class Chart {
  int datasize;
  string type;
  vector<float> data;

public:
    void addType(string type);
    string getType();

    void addData(string data);
    void getData();

};