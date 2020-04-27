#pragma once

#include <iostream>
#include <cassert>

template <typename T>
struct Node {
    T value_;
    struct Node* next_;
public:
    explicit Node(T value = 0, Node<T>* next = nullptr) : value_(value), next_(next) {}
    ~Node() {
        std::cout << "~Node" << std::endl;
        delete next_;
    }
};

template <typename T>
class LinkedList {
    Node<T>* head_;
    Node<T>* tail_;
public:
    explicit LinkedList() : head_(nullptr), tail_(nullptr) {}
    LinkedList(std::initializer_list<T> elements) {
        for (auto& el: elements) {
            this->append(el);
        }
    }
    void append(T value) {
        Node<T>* new_node = new Node<T>;
        new_node->value_ = value;
        new_node->next_ = nullptr;
        if (head_ == nullptr) {
            head_ = new_node;
            tail_ = new_node;
        } else {
            tail_->next_ = new_node;
            tail_ = new_node;
        }
    }
    void prepend(T value) {
        Node<T>* new_node = new Node<T>;
        new_node->value_ = value;
        new_node->next_ = nullptr;
        if (head_ == nullptr) {
            head_ = new_node;
            tail_ = new_node;
        } else {
            new_node->next_ = head_;
            head_ = new_node;
        }
    }
    void append_all(const LinkedList& list) {
        for (int i = 0; i < list.length(); i++) {
            append(list[i]);
        }
    }
    void insert_at(int index, T value) {
        assert(index >= 0 && index < this->length());
        int c=0;
        Node<T>* ptr = head_;
        while (c!=index) {
            ptr = ptr->next_;
            c++;
        }
        Node<T>* new_node = new Node<T>;
        new_node->value_ = value;
        new_node->next_ = ptr->next_;
        ptr->next_ = new_node;
    }
    void remove_at(int index) {
        Node<T>* cmp = head_;
        Node<T>* ptr = nullptr;
        int c = 0;
        while (c != index) {
            if (c == index-1) {
                ptr = cmp;
            }
            cmp = cmp->next_;
            c++;
        }
        ptr->next_ = cmp->next_;
        cmp->next_ = nullptr;
        delete cmp;
    }
    void remove_all() {
        delete head_;
        head_ = nullptr;
        tail_ = nullptr;
    }
    T pop() {
        Node<T>* ptr = head_;
        for (int i=0; i<this->length()-1; i++) {
            tail_ = ptr;
            ptr = ptr->next_;
        }
        tail_->next_ = nullptr;
        T a = ptr->value_;
        delete ptr;
        return a;
    }
    T dequeue() {
        Node<T>* cmp = head_;
        head_ = head_->next_;
        cmp->next_ = nullptr;
        T a = cmp->value_;
        delete cmp;
        return a;
    }
    int length();
    T& operator[](int index) {
        assert(index >= 0 && index < this->length());
        int c=0;
        Node<T>* cmp = head_;
        while (c != index) {
            cmp = cmp->next_;
            c++;
        }
        return cmp->value_;
    }
    ~LinkedList() {
        std::cout << "~LinkedList" << std::endl;
        delete head_;
    }
};

template<typename T>
int LinkedList<T>::length() {
    int i = 0;
    Node<T>* cmp = head_;
    while (cmp != nullptr) {
        i++;
        cmp = cmp->next_;
    }
    return i;
}
