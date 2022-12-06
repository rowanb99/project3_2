

#ifndef TUPLE_H
#define TUPLE_H

#include <string>
#include <vector>
#include <sstream>

using namespace std;

class Tuple {
private:
    vector<string> values;
public:
    Tuple() {};
    Tuple(vector<string> values) { this->values = values; }
    bool operator< (const Tuple & other) const {
        if (values < other.values) {
            return true;
        }
        else {
            return false;
        }
    }
    vector<string> getValues() {
        return values;
    }
};

#endif //TUPLE_H
