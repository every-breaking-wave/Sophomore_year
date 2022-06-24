
#include "evastate.h"

evaState::evaState()
{
    var = new int [50];
    state = new bool [50];
}

evaState::~evaState()
{
    delete []var ;
    delete []state;
}

bool evaState::isDefined(int i)
{
    return state[i];
}

void evaState::setValue(std::string name, int value){
    symbolTable[name] = value;

}
