#ifndef RELATION_H
#define RELATION_H
#include <string>
#include "Header.h"
#include "Tuple.h"
#include <set>
#include <sstream>

using namespace std;

class Relation {
private:
    string name;
    Header* columnNames;
    set<Tuple> rows;

public:
    Relation() {};
    Relation(string name);
    Relation(string name, Header* columnNames);
    void setHeader(Header* header) { columnNames = header; }
    void setRows(set<Tuple> newRows) { rows = newRows; }
    set<Tuple> getRows() { return rows; }
    string GetName() { return name; }
    Header* GetHeader() { return columnNames; }
    void AddTuple(Tuple newTuple) { rows.insert(newTuple); }
    string toString();
    Relation* select1(int columnIndex, string value);
    Relation* select2(int columnIndex1, int columnIndex2);
    Relation* project(vector<int> columnsToProject);
    Relation* rename(vector<string> newColumnNames);
    bool isEmpty() { if (rows.empty()) return true; else return false; }
    int size() { return rows.size(); }
};

#endif //RELATION_H
