#include <iostream>
#include "cuckoo.h"
using namespace std;

int main()
{
    cuckoo cuckoo;
    int m,key,value;
    char cmd[7];
    cin >> m;
    for(int i = 0;i < m;++i)
    {
        cin >> cmd;
        if(cmd[0] == 'I')
        {
            cin >> key >> value;
            cuckoo.insert(key,value);
        }
        if(cmd[0] == 'L')
        {
            cin >> key;
            cuckoo.lookup(key);
        }
        if(cmd[0] == 'D')
        {
            cin >> key;
            cuckoo.Delete(key);
        }
    }
}
