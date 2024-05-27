#include <iostream>
#include "linkedlist.h"
using namespace std;

int main()
{
    LinkedList<int> l;
    l.insertAsFirst(10);
    l.insertAsLast(20);
    l.insertAsLast(5);
    l.insertAsLast(10);
    Posi(int) p = l.last();

    l.selectionSorted(l.first(), 4);
    Posi(int) k = l.first();
    for (int i = 0; i < 4; i++)
    {
        cout << k->data << endl;
        k = k->succ;
    }

    return 0;
}