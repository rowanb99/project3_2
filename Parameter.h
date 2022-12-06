#ifndef PARAMETER_H
#define PARAMETER_H
#include <vector>
#include <sstream>

using namespace std;

class Parameter
{
private:
    string STRING; // parameter
public:
    Parameter() {

    }
    Parameter(std::string s) {
        STRING = s;
    }
    ~Parameter() {}

    string toString() {
        std::stringstream s;
        s << STRING;
        return s.str();
    }

    void setString(std::string newString) {
        STRING = newString;
    }
};

#endif // PARAMETER_H

