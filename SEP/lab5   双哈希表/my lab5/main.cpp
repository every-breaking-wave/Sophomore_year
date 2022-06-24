#include <iostream>
#include"cuckoo.h"
using namespace std;


void getCommand(hashNode &hn) {
    std::string str;
    std::cin >> str;
    int key;
    std::cin >> key;
    if(str == "Insert") {
        int value;
        std::cin >> value;
        hn.insert(key, value);

    }else if (str == "Lookup")
    {
        hn.look(key);
    }
    else if (str == "Delete"){
        hn.remove(key);
    }
}


int main()
{
  int n;
  cin>>n;
   hashNode hn;

   while (n--) {
       getCommand(hn);
       //hn.showHash();
     }


  return 0;
}
