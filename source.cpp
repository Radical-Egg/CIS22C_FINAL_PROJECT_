#include <iostream>
#include <string>
#include "hash.h"

using namespace std;

// sample main of using the hash table functions
int main() 
{ 
    Hash t;

    t.addItem("123 test", 2000, 3, 5, "single_family", 900);
    t.addItem("567 test addr", 8000, 3, 2, "condo", 400);
    t.addItem("567 test addr", 8000, 3, 2, "condo", 400);

    t.printTable();
    t.printItemsInBucket("567 test addr");
    t.removeItem("567 test addr");
    t.printTable();

    return 0; 
} 