#pragma once

#include <cassert>
#include <iostream>

template <typename T>
struct Node {
    T value_;
    struct Node<T>* next_;
public:
    explicit Node(T value = 0, Node<T>* next = nullptr) : value_(value), next_(next) {}
    ~Node() {
        std::cout << "~Node" << std::endl;
        delete next_;
    }
};

namespace linked {
    template<typename T>
    class LinkedList {
        Node<T> *head_;
        Node<T> *tail_;
    public:
        class Iterator {
        private:
            Node<T>* ptr_;
        public:
            explicit Iterator(Node<T>* ptr) : ptr_(ptr) {}
            const Iterator& operator++() {
                ptr_ = ptr_->next_;
                return *this;
            }
            Iterator operator++(int) {
                Iterator result = *this;
                ++(*this);
                return result;
            }
            T& operator*() const {
                return ptr_->value_;
            }
            T* operator->() const {
                return &ptr_->value_;
            }
            bool operator==(const Iterator& rhs) const {
                return ptr_ == rhs.ptr_;
            }
            bool operator!=(const Iterator& rhs) const {
                return ptr_ != rhs.ptr_;
            }
        };

        explicit LinkedList() : head_(nullptr), tail_(nullptr) {}

        LinkedList(std::initializer_list<T> elements) {
            head_ = nullptr;
            for (auto& el: elements) {
                append(el);
            }
        }

        LinkedList(const LinkedList<T> &list) {
            head_ = nullptr;
            for (int i = 0; i < list.length(); i++) {
                append(list.at(i));
            }
        }

        LinkedList<T> &operator=(const LinkedList<T> &list) {
            if (this != &list) {
                delete head_;
                head_ = nullptr;
                for (int i = 0; i < list.length(); i++) {
                    append(list.at(i));
                }
            }
            return *this;
        }

        void append(T value) {
            Node<T> *new_node = new Node<T>(value, nullptr);
            if (head_ == nullptr) {
                head_ = new_node;
                tail_ = new_node;
            } else {
                tail_->next_ = new_node;
                tail_ = new_node;
            }
        }

        void prepend(T value) {
            Node<T> *new_node = new Node<T>(value, nullptr);
            if (head_ == nullptr) {
                head_ = new_node;
                tail_ = new_node;
            } else {
                new_node->next_ = head_;
                head_ = new_node;
            }
        }

        void append_all(const LinkedList<T>& list) {
            for (int i = 0; i < list.length(); i++) {
                append(list.at(i));
            }
        }

        void insert_at(int index, T value) {
            assert(index >= 0 && index < length());
            int c = 0;
            Node<T> *ptr = head_;
            while (c != index) {
                ptr = ptr->next_;
                c++;
            }
            Node<T> *new_node = new Node<T>(value, ptr->next_);
            ptr->next_ = new_node;
        }

        void remove_at(int index) {
            if (index == 0) {
                dequeue();
                return;
            }
            Node<T> *cmp = head_;
            Node<T> *ptr = nullptr;
            int c = 0;
            while (c != index) {
                if (c == index - 1) {
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
            Node<T> *ptr = head_;
            for (int i = 0; i < this->length() - 1; i++) {
                tail_ = ptr;
                ptr = ptr->next_;
            }
            tail_->next_ = nullptr;
            auto a = ptr->value_;
            delete ptr;
            return a;
        }

        T dequeue() {
            Node<T> *cmp = head_;
            head_ = head_->next_;
            cmp->next_ = nullptr;
            auto a = cmp->value_;
            delete cmp;
            return a;
        }

        int length() const {
            int i = 0;
            Node<T> *cmp = head_;
            while (cmp != nullptr) {
                i++;
                cmp = cmp->next_;
            }
            return i;
        }

        T &operator[](int index) {
            assert(index >= 0 && index < length());
            int c = 0;
            Node<T> *cmp = head_;
            while (c != index) {
                cmp = cmp->next_;
                c++;
            }
            return cmp->value_;
        }

        const T& at(int index) const {
            assert(index >= 0 && index < length());
            int c = 0;
            Node<T> *cmp = head_;
            while (c != index) {
                cmp = cmp->next_;
                c++;
            }
            return cmp->value_;
        }

        Iterator begin() const {
            return Iterator(head_);
        }

        Iterator end() const {
            return Iterator(tail_->next_);
        }

        ~LinkedList() {
            std::cout << "~LinkedList" << std::endl;
            delete head_;
        }
    };
}
