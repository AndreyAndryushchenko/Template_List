#include <ArrayList.hpp>
#include <LinkedList.hpp>
#include <memory>
#include <gtest/gtest.h>

TEST(ArrayList, test_with_copy_type) {
    array::ArrayList<int> list1 = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    array::ArrayList<int> list2;
    array::ArrayList<int> list3 = array::ArrayList<int>(5);
    ASSERT_EQ(0, list2.length());
    list2.append(1);
    list2.append(25);
    list3.append(10);
    ASSERT_EQ(1, list3.length());
    list2.prepend(100);
    ASSERT_EQ(100, list2[0]);
    list3.append(1000);
    list3.insert_at(0, 0);
    ASSERT_EQ(0, list3[1]);
    ASSERT_EQ(1000, list3.pop());
    ASSERT_EQ(100, list2.dequeue());
    list2.remove_at(0);
    ASSERT_EQ(25, list2[0]);
    list3.remove_all();
    ASSERT_EQ(0, list3.length());
    list3.append(30);
    list3.append(90);
    list2.append_all(list3);
    list1.append_all(list2);
    ASSERT_EQ(12, list1.length());
    ASSERT_EQ(3, list2.length());
    ASSERT_EQ(30, list2[1]);
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

TEST(ArrayList, test_copy_list) {
    array::ArrayList<int> list1 = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    array::ArrayList<int> list2 = list1;
    ASSERT_EQ(list2.pop(), list1.pop());
    ASSERT_EQ(list2.dequeue(), list1.dequeue());
    array::ArrayList<int> list3(1);
    list3 = list1;
    ASSERT_EQ(list3.pop(), list1.pop());
    ASSERT_EQ(list3.length(), list1.length());
}

TEST(ArrayList, test_with_uncopy_type_and_move_list) {
    array::ArrayList<std::unique_ptr<int>> v;
    ASSERT_EQ(v.length(), 0);
    v.append(std::make_unique<int>(42));
    ASSERT_EQ(v.length(), 1);
    ASSERT_EQ(*v.at(0).get(), 42);
    v.prepend(std::make_unique<int>(7));
    ASSERT_EQ(*v.at(0).get(), 7);
    ASSERT_EQ(*v.at(1).get(), 42);
    v.insert_at(0, std::make_unique<int>(25));
    ASSERT_EQ(*v.at(1).get(), 25);
    ASSERT_EQ(7, *v.dequeue().get());
    ASSERT_EQ(42, *v.pop().get());
    v.insert_at(0, std::make_unique<int>(50));
    ASSERT_EQ(*v.at(1).get(), 50);
    v.append(std::make_unique<int>(30));
    v.remove_at(1);
    ASSERT_EQ(*v.at(1).get(), 30);
    for (auto& el: v) {
        std::cout << *el << " ";
    }
    std::cout << std::endl;
    for (auto el = v.begin(); el != v.end(); el++) {
        std::cout << **el << " ";
    }
    std::cout << std::endl;
    array::ArrayList<std::unique_ptr<int >> v1(std::move(v));
    ASSERT_EQ(*v1.at(1).get(), 30);
    array::ArrayList<std::unique_ptr<int >> v2;
    v2 = std::move(v1);
    ASSERT_EQ(*v2.at(0).get(), 25);
}

TEST(ArrayList, testing_remove_all) {
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
        ASSERT_EQ(trigger, 0);
    }
    ASSERT_EQ(trigger, 0);
}

TEST(ArrayList, testing_remove_at) {
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
        ASSERT_EQ(trigger, 2);
    }
    ASSERT_EQ(trigger, 0);
}

TEST(LinkedList, testing_with_copy_type) {
    linked::LinkedList<int> list1 = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    linked::LinkedList<int> list2;
    linked::LinkedList<int> list3;
    ASSERT_EQ(0, list2.length());
    list2.append(1);
    list2.append(25);
    list3.append(10);
    ASSERT_EQ(9, list1.length());
    ASSERT_EQ(1, list3.length());
    list2.prepend(100);
    ASSERT_EQ(100, list2[0]);
    list3.append(1000);
    list3.insert_at(0, 0);
    ASSERT_EQ(0, list3[1]);
    ASSERT_EQ(1000, list3.pop());
    ASSERT_EQ(100, list2.dequeue());
    list2.remove_at(0);
    ASSERT_EQ(25, list2[0]);
    list3.remove_all();
    ASSERT_EQ(0, list3.length());
    list3.append(30);
    list3.append(90);
    list2.append_all(list3);
    list1.append_all(list2);
    ASSERT_EQ(12, list1.length());
    ASSERT_EQ(3, list2.length());
    ASSERT_EQ(30, list2[1]);
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

TEST(LinkedList, testing_copy_list) {
    linked::LinkedList<int> list1 = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    linked::LinkedList<int> list2 = list1;
    ASSERT_EQ(list2.pop(), list1.pop());
    ASSERT_EQ(list2.dequeue(), list1.dequeue());
    linked::LinkedList<int> list3;
    list3 = list1;
    ASSERT_EQ(list3.pop(), list1.pop());
    ASSERT_EQ(list3.length(), list1.length());
}