#ifndef RULE_H
#define RULE_H
#include <vector>
#include "Predicate.h"
#include <sstream>

using namespace std;

class Rule {
private:
    Predicate* headPredicate;
    vector<Predicate*> bodyPredicates;
public:
    Rule() {

    }
    Rule(Predicate* predicate) {
        headPredicate = predicate;
    }
    ~Rule() {}

    string toString() {
        std::stringstream s;
        s << headPredicate->toString() << " :- ";
        for (unsigned int i = 0; i < bodyPredicates.size(); i++) {
            s << bodyPredicates.at(i)->toString();
            if (i != bodyPredicates.size()-1) s << ',';
            else s << '.';
        }
        return s.str();
    }

    void setHeadPredicate(Predicate* head) {
        headPredicate = head;
    }

    void addPredicate(Predicate* predicate) {
        bodyPredicates.push_back(predicate);
    }

    vector<Predicate*> getPredicates() {
        return bodyPredicates;
    }
};

#endif // RULE_H

