#pragma once

#include <cassert>
#include <iostream>

template <typename T>
struct Node {
    T value_;
    struct Node<T>* next_;
public:
    explicit Node() {}
    ~Node() {
        std::cout << "~Node" << std::endl;
        if (next_ != nullptr) {
            next_->~Node<T>();
            ::operator delete(next_);
        }
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
                append(list[i]);
            }
        }

        LinkedList<T> &operator=(const LinkedList<T> &list) {
            if (this != &list) {
                if (head_ != nullptr) {
                    head_->~Node<T>();
                    ::operator delete(head_);
                }
                head_ = nullptr;
                for (int i = 0; i < list.length(); i++) {
                    append(list[i]);
                }
            }
            return *this;
        }

        LinkedList(LinkedList<T> &&list) noexcept {
            head_ = std::move(list.head_);
            tail_ = std::move(list.tail_);
            list.head_ = nullptr;
            list.tail_ = nullptr;
        }

        LinkedList<T> &operator=(LinkedList &&list) noexcept {
            if (this != &list) {
                if (head_ != nullptr) {
                    head_->~Node<T>();
                    ::operator delete(head_);
                }
                head_ = std::move(list.head_);
                tail_ = std::move(list.tail_);
                list.head_ = nullptr;
                list.tail_ = nullptr;
            }
            return *this;
        }

        void append(const T& value) {
            auto new_node = static_cast<Node<T>*>(::operator new(sizeof(Node<T>)));
            new_node->value_ = value;
            new_node->next_ =nullptr;
            if (head_ == nullptr) {
                head_ = new_node;
                tail_ = new_node;
            } else {
                tail_->next_ = new_node;
                tail_ = new_node;
            }
        }

        void append(T&& value) {
            auto new_node = static_cast<Node<T>*>(::operator new(sizeof(Node<T>)));
            ::new(new_node) T(std::move(value));
            new_node->next_ =nullptr;
            if (head_ == nullptr) {
                head_ = new_node;
                tail_ = new_node;
            } else {
                tail_->next_ = new_node;
                tail_ = new_node;
            }
        }

        void prepend(const T& value) {
            auto new_node = static_cast<Node<T>*>(::operator new(sizeof(Node<T>)));
            new_node->value_ = value;
            new_node->next_ =nullptr;
            if (head_ == nullptr) {
                head_ = new_node;
                tail_ = new_node;
            } else {
                new_node->next_ = head_;
                head_ = new_node;
            }
        }

        void prepend(T&& value) {
            auto new_node = static_cast<Node<T>*>(::operator new(sizeof(Node<T>)));
            ::new(new_node) T(std::move(value));
            new_node->next_ =nullptr;
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
                append(list[i]);
            }
        }

        void append_all(LinkedList<T>&& list) = delete;

        void insert_at(int index, const T& value) {
            assert(index >= 0 && index < length());
            int c = 0;
            Node<T> *ptr = head_;
            while (c != index) {
                ptr = ptr->next_;
                c++;
            }
            auto new_node = static_cast<Node<T>*>(::operator new(sizeof(Node<T>)));
            new_node->value_ = value;
            new_node->next_ = ptr->next_;
            if (index == length()-1) {
                tail_ = new_node;
            }
            ptr->next_ = new_node;
        }

        void insert_at(int index, T&& value) {
            assert(index >= 0 && index < length());
            int c = 0;
            Node<T> *ptr = head_;
            while (c != index) {
                ptr = ptr->next_;
                c++;
            }
            auto new_node = static_cast<Node<T>*>(::operator new(sizeof(Node<T>)));
            ::new(new_node) T(std::move(value));
            new_node->next_ = ptr->next_;
            if (index == length()-1) {
                tail_ = new_node;
            }
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
            cmp->~Node<T>();
            ::operator delete(cmp);
        }

        void remove_all() {
            head_->~Node<T>();
            ::operator delete(head_);
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
            auto a = std::move(ptr->value_);
            ptr->~Node<T>();
            ::operator delete(ptr);
            return a;
        }

        T dequeue() {
            Node<T> *cmp = head_;
            head_ = head_->next_;
            cmp->next_ = nullptr;
            auto a = std::move(cmp->value_);
            cmp->~Node<T>();
            ::operator delete(cmp);
            return a;
        }

        [[nodiscard]] int length() const {
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

        const T &operator[](int index) const {
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
            if (head_ != nullptr) {
                head_->~Node<T>();
                ::operator delete(head_);
            }
        }
    };
}
