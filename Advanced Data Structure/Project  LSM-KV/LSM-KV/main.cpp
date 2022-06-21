#include <iostream>
#include "kvstore.h"
#include <fstream>

using namespace std;


int main() {
    KVStore *kv = new KVStore("../SSTable");
    delete kv;
    return 0;
}
