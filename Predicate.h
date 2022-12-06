#ifndef PREDICATE_H
#define PREDICATE_H
#include <vector>
#include "Parameter.h"
#include <sstream>

using namespace std;


class Predicate
{
private:
    string ID;
    vector<Parameter*> parameters;
public:
    Predicate() {

    }
    Predicate(std::string iD) {
        ID = iD;
    }
    ~Predicate() {}

    string toString() {
        std::stringstream s;
        s << ID << '(';
        // outputting all the parameters in this predicate
        for (unsigned int i = 0; i < parameters.size(); i++) {
            s << parameters.at(i)->toString();
            if (i != parameters.size()-1) s << ',';
        }
        s << ')';
        return s.str();
    }

    vector<Parameter*> getParameters() {
        return parameters;
    }

    string getID() {
        return ID;
    }

    void addParameter(Parameter* p) {
        parameters.push_back(p);
    }

    int getNumParameters() {
        return parameters.size();
    }

    void setId(string id) {
        ID = id;
    }
};

#endif // PREDICATE_H

