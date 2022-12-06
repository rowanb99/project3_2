#include "DataLogProgram.h"

DataLogProgram::DataLogProgram() {

}
DataLogProgram::~DataLogProgram() {

}
vector<Predicate*> DataLogProgram::getSchemes() {
    return schemes;
}
vector<Predicate*> DataLogProgram::getFacts() {
    return facts;
}
vector<Rule*> DataLogProgram::getRules() {
    return rules;
}
vector<Predicate*> DataLogProgram::getQueries() {
    return queries;
}
void DataLogProgram::setFacts(vector<Predicate*> newFacts) {
    for (unsigned int i = 0; i < newFacts.size(); i++) {
        facts.push_back(newFacts[i]);
    }
}

void DataLogProgram::setSchemes(vector<Predicate*> newSchemes) {
    for (unsigned int i = 0; i < newSchemes.size(); i++) {
        schemes.push_back(newSchemes[i]);
    }
}

void DataLogProgram::setDomain(set<string> strings) {
    domain = strings;
}

void DataLogProgram::setRules(vector<Rule*> newRules) {
    for (unsigned int i = 0; i < newRules.size(); i++) {
        rules.push_back(newRules[i]);
    }
}

void DataLogProgram::setQueries(vector<Predicate*> newQueries) {
    for (unsigned int i = 0; i < newQueries.size(); i++) {
        queries.push_back(newQueries.at(i));
    }
}

string DataLogProgram::toString() {
    stringstream s;
    s << "Schemes(" << schemes.size() << "):\n";
    for (auto predicate : schemes) {
        s << "  " << predicate->toString() << '\n';
    }
    s << "Facts(" << facts.size() << "):\n";
    for (auto predicate : facts) {
        s << "  " << predicate->toString() << ".\n";
    }
    s << "Rules(" << rules.size() << "):\n";
    for (auto predicate : rules) {
        s << "  " << predicate->toString() << '\n';
    }
    s << "Queries(" << queries.size() << "):\n";
    for (unsigned int i = 0; i < queries.size(); i ++) {
        s << "  " << queries.at(i)->toString() << "?\n";
    }
    s << "Domain(" << domain.size() << "):\n";
    for (auto element: domain) {
        s << "  " << element << '\n';
    }
    return s.str();
}