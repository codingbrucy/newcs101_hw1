

#include <iostream>
#include "LinkedList.h"
using namespace std;
int main(int argc, const char * argv[]) {
    LinkedList *l = new LinkedList();
    l->insert(4);
    l->insert(3);
    l->insert(2);
    l->insert(1);
    l->reverse();
    l->printList();
}
