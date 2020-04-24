#include "ArrayList.hpp"

using namespace std;

int main() {
    ArrayList<int> list1 = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    ArrayList<int> list2;
    ArrayList<int> list3 = ArrayList<int>(5);
    assert(0 == list2.length());
    list2.append(1);
    list2.append(25);
    list3.append(10);
    assert(1 == list3.length());
    list2.prepend(100);
    assert(100 == list2[0]);
    list3.append(1000);
    list3.insert_at(0, 0);
    assert(0 == list3[1]);
    assert(1000 == list3.pop());
    assert(100 == list2.dequeue());
    list2.remove_at(0);
    assert(25 == list2[0]);
    list3.remove_all();
    assert(0 == list3.length());
    list3.append(30);
    list3.append(90);
    list2.append_all(list3);
    list1.append_all(list2);
    assert(12 == list1.length());
    assert(3 == list2.length());
    assert(30 == list2[1]);
    for (auto& el: list1) {
        cout << el << " ";
    }
    cout << endl;
    ArrayList<int> list = {1,2,3,4,5,6,7,8,9};
    for (auto el = list.begin(); el != list.end(); el++) {
        cout << *el << " ";
    }
    cout << endl;
    return 0;
}
