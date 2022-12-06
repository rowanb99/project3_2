
#include "Relation.h"
#include <iostream>

Relation::Relation(string name, Header* columnNames) {
    this->name = name;
    this->columnNames = columnNames;
}

Relation::Relation(string name) {
    this->name = name;
}

string Relation::toString() {
    stringstream s;
    if (columnNames->getAttributes().size() != 0) {
        for (Tuple t: rows) {
            int i = 0;
            s << "  ";
            string line = "";
            for (string element: t.getValues()) { // t.getValues() returns vector<string>
                line += columnNames->getSingleAttribute(i);
                line += "=";
                line += element;
                line += ", ";
                i++; // next tuple
            }
            line.pop_back();
            line.pop_back();
            s << line;
            s << '\n'; // new line
        }
    }
    return s.str();
}

Relation* Relation::select1(int columnIndex, string value) {
    //cout << "Select 1" << endl;
    // create new relation but with the same structure as the relation this function was called on
    Relation* newRelation = new Relation(this->name, this->columnNames);
    // find the tuple with value inside the columnName column
    for (Tuple tuple : rows) {
        if (tuple.getValues()[columnIndex] == value) {
            //cout << "\nMatched value: " << tuple.getValues()[columnIndex];
            newRelation->AddTuple(tuple);
        }
    }
    //cout << "Relation right after select 1: \n" << newRelation->toString();
    return newRelation;
}

Relation* Relation::select2(int columnIndex1, int columnIndex2) {
    // create new relation but with the same structure as the relation this function was called on
    Relation* newRelation = new Relation(this->name, this->columnNames);
    // find the tuple with value inside the columnName column
    for (Tuple tuple : rows) {
        if (tuple.getValues()[columnIndex1] == tuple.getValues()[columnIndex2]) {
            newRelation->AddTuple(tuple);
        }
    }
    //cout << "\nRelation right after select 2: \n" << newRelation->toString();
    return newRelation;
}

Relation* Relation::project(vector<int> columnsToProject) {
    Header* newHeader = new Header;
    vector<string> newHeaderValues;
    vector<string> attributes = columnNames->getAttributes();
    for (unsigned int i = 0; i < attributes.size(); i++) {
        for (unsigned int j = 0; j < columnsToProject.size(); j++) {
            if (i == (unsigned int)columnsToProject.at(j)) {
                newHeader->setSingleAttribute(attributes.at(i));
            }
        }
    }

    /*
     * for (unsigned int i = 0; i < columnsToProject.size(); i++) {
            newHeader->setSingleAttribute(attributes[columnsToProject[i]]);
        }
    */

    Relation* newRelation = new Relation(this->name, newHeader);
    for (Tuple tuple : rows) {
        vector<string> newValues;
        for (unsigned int i = 0; i < columnsToProject.size(); i++) {
            newValues.push_back(tuple.getValues()[columnsToProject[i]]);
        }
        Tuple newTuple(newValues);
        newRelation->AddTuple(newTuple);
    }
    //cout << "Relation right after project: \n" << newRelation->toString();
    return newRelation;
}

Relation* Relation::rename(vector<string> newColumnNames) {
    Header* newHeader = new Header;
    bool columnsGood = false;
    for (unsigned int i = 0; i < newColumnNames.size(); i++) {
        if (newColumnNames.at(i)[0] != '\'') columnsGood = true; // we find a variable in the header
    }
    if (columnsGood) newHeader->setAttributeValues(newColumnNames);
    // else leave the header empty
    Relation* newRelation = new Relation(this->name, newHeader);
    for (Tuple tuple : rows) {
        newRelation->AddTuple(tuple);
    }
    return newRelation;
}
