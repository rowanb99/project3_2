#include "Parser.h"
#include <iostream>

using namespace std;

Parser::Parser() {
    DataLogProgram* program = new DataLogProgram;
    this->program = program;
    index = 0;
}

Parser::~Parser() {
    //delete program;
}

DataLogProgram* Parser::parse(vector<Token*> tokens) {
    this->tokens = tokens; // this is kind of messy
    try {
        index = 0;
        parseDataLogProgram();
        /*cout << "Success!" << '\n';
        cout << program->toString();*/
        return program;
    }
    catch(Token* token) {
        /*cout << "Failure!" << '\n';
        cout << "  " << token->toString(token->getType()) << '\n';*/
        return program;
    }
}

void Parser::match(TokenType expectedToken) {
    if (tokens[index]->getType() == expectedToken) {
        index++;
    }
    else {
        throw tokens.at(index); // throw current token
    }
}

void Parser::pushOnList(string token) {
    Parameter* newParameter = new Parameter();
    if (tokens[index]->getDescription() != "") {
        newParameter->setString(token); // setting parameter
        parameters.push_back(newParameter);
    }
    else {}
    return ;
}

void Parser::parseDataLogProgram() {
    vector<Predicate*> Schemes;
    match(TokenType::SCHEMES);
    match(TokenType::COLON);
    Schemes.push_back(parseScheme());
    Schemes = parseSchemeList(Schemes);
    program->setSchemes(Schemes);

    vector<Predicate*> Facts;
    match(TokenType::FACTS);
    match(TokenType::COLON);
    Facts = parseFactList(Facts);
    program->setFacts(Facts);
    program->setDomain(domain);

    vector<Rule*> Rules;
    match(TokenType::RULES);
    match(TokenType::COLON);
    Rules = parseRuleList(Rules);
    program->setRules(Rules);

    vector<Predicate*> Queries;
    match(TokenType::QUERIES);
    match(TokenType::COLON);
    Queries.push_back(parseQuery());
    Queries = parseQueryList(Queries);
    program->setQueries(Queries);

    match(TokenType::EOF_TOKEN);
}

vector<Predicate*> Parser::parseSchemeList(vector<Predicate*> &Schemes) {
    Predicate* newScheme = new Predicate();
    if (tokens[index]->getType() == TokenType::FACTS) return Schemes; // we have the lambda production
    else {
        newScheme = parseScheme();
        Schemes.push_back(newScheme);
        parseSchemeList(Schemes);
        return Schemes;
    }
}

vector<Predicate*> Parser::parseFactList(vector<Predicate*> &Facts) {
    Predicate* newFact = new Predicate();
    if (tokens[index]->getType() == TokenType::RULES) return Facts;
    else {
        newFact = parseFact();
        Facts.push_back(newFact);
        vector<Parameter*> ParamList = newFact->getParameters();
        for (unsigned int i = 0; i < ParamList.size(); i++) {
            domain.insert(ParamList.at(i)->toString());
        }
        parseFactList(Facts);
        return Facts;
    }
}

vector<Rule*> Parser::parseRuleList(vector<Rule*> &Rules) {
    Rule* newRule = new Rule();
    if (tokens[index]->getType() == TokenType::QUERIES) return Rules;
    else {
        newRule = parseRule();
        Rules.push_back(newRule);
        parseRuleList(Rules);
        return Rules;
    }
}

vector<Predicate*> Parser::parseQueryList(vector<Predicate*> &Queries) {
    if (tokens[index]->getType() == TokenType::EOF_TOKEN) return Queries;
    else {
        Queries.push_back(parseQuery());
        parseQueryList(Queries);
        return Queries;
    }
}

Predicate* Parser::parseScheme() {
    parameters.clear();
    match(TokenType::ID);
    Predicate* newScheme = new Predicate(tokens[index-1]->getDescription());
    match(TokenType::LEFT_PAREN);
    match(TokenType::ID);
    pushOnList(tokens[index-1]->getDescription());
    parseIdList();
    match(TokenType::RIGHT_PAREN);
    for (unsigned int i = 0; i < parameters.size(); i++) {
        newScheme->addParameter(parameters.at(i));
    }
    return newScheme;
}

Predicate* Parser::parseFact() {
    parameters.clear();
    match(TokenType::ID);
    Predicate* newFact = new Predicate(tokens[index-1]->getDescription());
    match(TokenType::LEFT_PAREN);
    match(TokenType::STRING);
    pushOnList(tokens[index-1]->getDescription()); // add to vector of parameters
    parseStringList();
    match(TokenType::RIGHT_PAREN);
    match(TokenType::PERIOD);
    for (unsigned int i = 0; i < parameters.size(); i++) {
        newFact->addParameter(parameters.at(i));
    }
    return newFact;
}

Rule* Parser::parseRule() {
    Rule* newRule = new Rule();
    newRule->setHeadPredicate(parseHeadPredicate());
    match(TokenType::COLON_DASH);
    newRule->addPredicate(parsePredicate());
    vector<Predicate*> newRulePredicates = newRule->getPredicates();
    parsePredicateList(newRulePredicates);
    match(TokenType::PERIOD);
    for (unsigned int i = 1; i < newRulePredicates.size(); i++) {
        newRule->addPredicate(newRulePredicates.at(i));
    }
    return newRule;
}

Predicate* Parser::parseQuery() {
    Predicate* newQuery = new Predicate();
    newQuery = parsePredicate(); // parsePredicate() returns a Predicate pointer
    match(TokenType::Q_MARK);
    return newQuery;
}

Predicate* Parser::parseHeadPredicate() {
    Predicate* headPredicate = new Predicate();
    parameters.clear();
    match(TokenType::ID);
    headPredicate->setId(tokens[index-1]->getDescription());
    match(TokenType::LEFT_PAREN);
    match(TokenType::ID);
    pushOnList(tokens[index-1]->getDescription()); // add to vector of parameters
    parseIdList();
    match(TokenType::RIGHT_PAREN);
    for (unsigned int i = 0; i < parameters.size(); i++) {
        headPredicate->addParameter(parameters.at(i));
    }
    return headPredicate;
}

Predicate* Parser::parsePredicate() {
    parameters.clear();
    Predicate* newPredicate = new Predicate();
    match(TokenType::ID);
    newPredicate->setId(tokens[index-1]->getDescription());
    match(TokenType::LEFT_PAREN);
    newPredicate->addParameter(parseParameter());
    parseParameterList();
    match(TokenType::RIGHT_PAREN);
    for (unsigned int i = 0; i < parameters.size(); i++) {
        newPredicate->addParameter(parameters.at(i));
    }
    return newPredicate;
}

vector<Predicate*> Parser::parsePredicateList(vector<Predicate*> &Predicates) {
    if (tokens[index]->getType() == TokenType::PERIOD) return Predicates;
    else {
        match(TokenType::COMMA);
        Predicates.push_back(parsePredicate());
        parsePredicateList(Predicates);
        return Predicates;
    }
}

void Parser::parseParameterList() {
    Parameter* newParameter = new Parameter();
    if (tokens[index]->getType() == TokenType::RIGHT_PAREN) return ;
    else {
        match(TokenType::COMMA);
        newParameter = parseParameter();
        pushOnList(newParameter->toString());
        parseParameterList();
        return ;
    }
}

void Parser::parseStringList() {
    if (tokens[index]->getType() == TokenType::RIGHT_PAREN) return;
    else {
        match(TokenType::COMMA);
        match(TokenType::STRING);
        pushOnList(tokens[index-1]->getDescription());
        parseStringList();
        return ;
    }
}

void Parser::parseIdList() {
    if (tokens[index]->getType() == TokenType::RIGHT_PAREN) return;
    else {
        match(TokenType::COMMA);
        match(TokenType::ID);
        pushOnList(tokens[index-1]->getDescription());
        parseIdList();
        return ;
    }
}

Parameter* Parser::parseParameter() {
    Parameter* newParameter = new Parameter();
    if (tokens[index]->getType() == TokenType::STRING) {
        match(TokenType::STRING);
        newParameter->setString(tokens[index-1]->getDescription());
    }
    else {
        match(TokenType::ID);
        newParameter->setString(tokens[index-1]->getDescription());
    }
    return newParameter;
}
