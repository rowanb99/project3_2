#ifndef DATALOGPROGRAM_H
#define DATALOGPROGRAM_H
#include <vector>
#include "Predicate.h"
#include "Rule.h"
#include "Parameter.h"
#include <iostream>
#include "set"

class DataLogProgram
{
private:
    // order in which they are outputted
    vector<Predicate*> schemes;
    vector<Predicate*> facts;
    vector<Rule*> rules;
    vector<Predicate*> queries;
    set<string> domain;
public:
    DataLogProgram();
    ~DataLogProgram();
    vector<Predicate*> getSchemes();
    vector<Predicate*> getFacts();
    vector<Rule*> getRules();
    vector<Predicate*> getQueries();

    void setFacts(vector<Predicate*> newFacts);
    void setSchemes(vector<Predicate*> newSchemes);
    void setDomain(set<string> strings);
    void setRules(vector<Rule*> newRules);
    void setQueries(vector<Predicate*> newQueries);

    string toString();

};

#endif // DATALOGPROGRAM_H

