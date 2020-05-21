#include "ArrayList.hpp"
#include "LinkedList.hpp"
#include <memory>
//#include <gtest/gtest.h>


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
    array::ArrayList<std::unique_ptr<int>> v;
    assert(v.length() == 0);
    v.append(std::make_unique<int>(42));
    assert(v.length() == 1);
    assert(*v.at(0).get() == 42);
    v.prepend(std::make_unique<int>(7));
    assert(*v.at(0).get() == 7);
    assert(*v.at(1).get() == 42);
    v.insert_at(0, std::make_unique<int>(25));
    assert(*v.at(1).get() == 25);
    assert(7 == *v.dequeue().get());
    assert(42 == *v.pop().get());
    v.insert_at(0, std::make_unique<int>(50));
    assert(*v.at(1).get() == 50);
    v.append(std::make_unique<int>(30));
    v.remove_at(1);
    assert(*v.at(1).get() == 30);
    for (auto& el: v) {
        std::cout << *el << " ";
    }
    std::cout << std::endl;
    for (auto el = v.begin(); el != v.end(); el++) {
        std::cout << **el << " ";
    }
    std::cout << std::endl;
    array::ArrayList<std::unique_ptr<int >> v1(std::move(v));
    assert(*v1.at(1).get() == 30);
    array::ArrayList<std::unique_ptr<int >> v2;
    v2 = std::move(v1);
    assert(*v2.at(0).get() == 25);
}

void test4() {
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
    for (auto& el: list1) {
        std::cout << el << " ";
    }
    std::cout << std::endl;
    linked::LinkedList<int> list = {1,2,3,4,5,6,7,8,9};
    for (auto el = list.begin(); el != list.end(); el++) {
        std::cout << *el << " ";
    }
    std::cout << std::endl;
}

void test5() {
    linked::LinkedList<int> list1 = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    linked::LinkedList<int> list2 = list1;
    assert(list2.pop() == list1.pop());
    assert(list2.dequeue() == list1.dequeue());
    linked::LinkedList<int> list3;
    list3 = list1;
    assert(list3.pop() == list1.pop());
    assert(list3.length() == list1.length());
}

void test6() {
    int trigger = 6;
    struct A {
        int *a_;
        explicit A(int *a) : a_(a) {}
        ~A() { (*a_)--; }
    };
    {
        array::ArrayList<A> v(4);
        v.append(A(&trigger));
        v.append(A(&trigger));
        v.append(A(&trigger));
        v.remove_all();
        assert(trigger == 0);
    }
    assert(trigger == 0);
}

void test7() {
    int trigger = 6;
    struct A {
        int *a_;
        explicit A(int *a) : a_(a) {}
        ~A() { (*a_)--; }
    };
    {
        array::ArrayList<A> v(4);
        v.append(A(&trigger));
        v.append(A(&trigger));
        v.append(A(&trigger));
        v.remove_at(1);
        assert(trigger == 2);
    }
    assert(trigger == 0);
}

int main(int argc, char** argv) {
//    ::testing::InitGoogleTest(&argc, argv);
//    return RUN_ALL_TESTS();
    std::cout << "=============================" << std::endl;
    test1();
    std::cout << "=============================" << std::endl;
    test2();
    std::cout << "=============================" << std::endl;
    test3();
    std::cout << "=============================" << std::endl;
    test4();
    std::cout << "=============================" << std::endl;
    test5();
    std::cout << "=============================" << std::endl;
    test6();
    std::cout << "=============================" << std::endl;
    test7();
    std::cout << "=============================" << std::endl;
}
