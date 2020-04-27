#include "ArrayList.hpp"
#include "LinkedList.hpp"

void test1() {
    array::ArrayList<int> list1 = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    array::ArrayList<int> list2;
    array::ArrayList<int> list3 = array::ArrayList<int>(5);
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
        std::cout << el << " ";
    }
    std::cout << std::endl;
    array::ArrayList<int> list = {1,2,3,4,5,6,7,8,9};
    for (auto el = list.begin(); el != list.end(); el++) {
        std::cout << *el << " ";
    }
    std::cout << std::endl;
}

void test2() {
    array::ArrayList<int> list1 = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    array::ArrayList<int> list2 = list1;
    assert(list2.pop() == list1.pop());
    assert(list2.dequeue() == list1.dequeue());
    array::ArrayList<int> list3(1);
    list3 = list1;
    assert(list3.pop() == list1.pop());
    assert(list3.length() == list1.length());
}

void test3() {
    linked::LinkedList<int> list1 = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    linked::LinkedList<int> list2;
    linked::LinkedList<int> list3;
    assert(0 == list2.length());
    list2.append(1);
    list2.append(25);
    list3.append(10);
    assert(9 == list1.length());
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
//    for (auto& el: list1) {
//        std::cout << el.value_ << " ";
//    }
//    std::cout << std::endl;
//    linked::LinkedList<int> list = {1,2,3,4,5,6,7,8,9};
//    for (auto el = list.begin(); el != list.end(); el++) {
//        std::cout << el->value_ << " ";
//    }
//    std::cout << std::endl;
}

void test4() {
    linked::LinkedList<int> list1 = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    linked::LinkedList<int> list2 = list1;
    assert(list2.pop() == list1.pop());
    assert(list2.dequeue() == list1.dequeue());
    linked::LinkedList<int> list3;
    list3 = list1;
    assert(list3.pop() == list1.pop());
    assert(list3.length() == list1.length());
}

int main() {
    test1();
    test2();
    test3();
    test4();
    return 0;
}
