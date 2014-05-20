#ifndef TURINGMACHINEMODEL_H
#define TURINGMACHINEMODEL_H
#include <string>
#include <vector>
#include <map>
#include <set>
#include <algorithm>

using namespace std;

struct TuringFunctionValue{
    string outState;
    char outSymbol;
    bool outDirection;
};
typedef map<string,TuringFunctionValue> functionSubType;
typedef map<char,functionSubType> functionType;
class TuringMachineModel
{
    string alphabet;
    set<string> states;
    functionType function;
    int length;
    vector<char> tape;
    int tapePosition;
    string state;

public:
    TuringMachineModel();
    void setAlphabet(string alphabet);
    void addState(string state);
    void removeState(string state);
    void setLength(int length);
    void setTape(int tapeBegin,string tapeString);
    void setTapePosition(int position);
    int getTapePosition();
    void setState(string state);
    string getState();
};

#endif // TURINGMACHINEMODEL_H
