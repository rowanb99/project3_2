
#include "CommAutomaton.h"

void CommAutomaton::S0(const std::string &input)
{
    if (input[index] == ',') {
        inputRead = 1;
    }
    else {
        Serr();
    }
}