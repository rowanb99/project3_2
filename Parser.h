#ifndef PARSER_H
#define PARSER_H
#include <vector>
#include "Token.h"
#include "Parameter.h"
#include "Predicate.h"
#include "Rule.h"
#include "DataLogProgram.h"
//#include "Parser.cpp"
#include <iostream>
#include "set"

class Parser
{
private:
    DataLogProgram* program;
    std::vector<Token*> tokens;
    std::vector<Parameter*> parameters;
    set<string> domain;
    int index;

public:
    Parser();
    ~Parser();
    DataLogProgram* parse(std::vector<Token*> tokens); // parser takes in vector of tokens to parse
    void match(TokenType tokenToMatch);
    void parseDataLogProgram();

    void pushOnList(string token);

    void clearParameters();

    vector<Predicate*> parseSchemeList(vector<Predicate*> &Schemes);
    vector<Predicate*> parseFactList(vector<Predicate*> &Facts);
    vector<Rule*> parseRuleList(vector<Rule*> &Rules);
    vector<Predicate*> parseQueryList(vector<Predicate*> &Queries);

    Predicate* parseScheme();
    Predicate* parseFact();
    Rule* parseRule();
    Predicate* parseQuery();

    Predicate* parseHeadPredicate();
    Predicate* parsePredicate();

    vector<Predicate*> parsePredicateList(vector<Predicate*> &Predicates);
    void parseParameterList();
    void parseStringList();
    void parseIdList();
    Parameter* parseParameter();
};

#endif //PARSER_H