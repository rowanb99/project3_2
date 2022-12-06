
#ifndef HEADER_H
#define HEADER_H
#include <string>
#include <vector>

using namespace std;

class Header {
private:
    vector<string> columnNames;
public:
    Header() {};
    void setAttributeValues(vector<string> attributes);
    void setSingleAttribute(string attributes);
    vector<string> getAttributes();
    string getSingleAttribute(int index);
    bool isEmpty() { return columnNames.empty(); }
};

#endif //HEADER_H
