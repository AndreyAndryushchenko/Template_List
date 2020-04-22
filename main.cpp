#include <iostream>
#include "ArrayList.hpp"

using namespace std;

int main() {
    ArrayList<int> list;
    ArrayList<int> list2;
    assert(0 == list.Length());
    list.append(1);
    list.append(25);
    list2.append(10);
    assert(1 == list2.Length());
    //list.prepend(100);
    //assert(100 == list[0]);
    //list2.append(1000);
    list2.InsertAt(0, 0);
    assert(0 == list2[1]);
    //assert(1000 == list2.Pop());
    //assert(100 == list.Dequeue());
    list.RemoveAt(0);
    assert(25 == list[0]);
    list2.RemoveAll();
    assert(0 == list2.Length());
    list2.append(30);
    list2.append(90);
    //list.AppendAll(list2);
    //assert(3 == list.Length());
    //assert(30 == list[1]);
    return 0;
}
