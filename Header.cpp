
#include "Header.h"

void Header::setAttributeValues(vector<string> attributes) {
    columnNames = attributes;
}

void Header::setSingleAttribute(string attributes) {
    columnNames.push_back(attributes);
}

string Header::getSingleAttribute(int index) {
    return columnNames[index];
}

vector<string> Header::getAttributes() {
    return columnNames;
}
