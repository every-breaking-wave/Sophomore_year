#ifndef EVASTATE_H
#define EVASTATE_H
#include <Qmap>
#include <string>
using namespace  std;

class evaState  // 存储变量的状态
{
public:
    evaState();
    ~evaState();
    int * var;
    bool * state;
    bool  isDefined(int i);  // 判断变量是否defined

    void setValue(std::string name, int value);
private:

   QMap<string, int> symbolTable;
};

#endif // EVASTATE_H
