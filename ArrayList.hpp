#pragma once

#include <cassert>
#include <stdexcept>
#include <iostream>

template <class T>
class ArrayList {
private:
    int capacity_;
    int size_;
    int length_;
    T* array_;
    void MacroMemory() {
        capacity_ *= 2;
        auto arr = new T[capacity_];
        for (int i = 0; i < size_; i++) {
            arr[i] = array_[i];
        }
        delete [] array_;
        array_ = arr;
    }
    void MicroMemory() {
        capacity_ /= 2;
        auto arr = new T[capacity_];
        for (int i = 0; i < size_+1; i++) {
            arr[i] = array_[i];
        }
        delete [] array_;
        array_ = arr;
    }
public:
    ArrayList(int capacity = 0) : capacity_(capacity), length_(-1), size_(0) {
        if (capacity == 0) {
            array_ = nullptr;
        } else {
            array_ = new T[capacity];
        }
    }
    ArrayList(const ArrayList& arr) {
        capacity_ = arr.capacity_;
        size_ = arr.size_;
        length_ = arr.length_;
        array_ = new T[capacity_];
        for (int i = 0; i<arr.size; i++) {
            array_[i] = arr.array_[i];
        }
    }
    ArrayList<T>& operator = (const ArrayList<T> arr) {
        capacity_ = arr.capacity_;
        size_ = arr.size_;
        length_ = arr.length_;
        array_ = new T[capacity_];
        for (int i = 0; i<arr.size; i++) {
            array_[i] = arr.array_[i];
        }
    }
    ArrayList(std::initializer_list<T> elements) {
        size_ = elements.size();
        length_ = elements.size() - 1;
        capacity_ = elements.size() * 2;
        array_ = new T[capacity_];
        int i = 0;
        for (auto& el : elements) {
            array_[i] = el;
            i++;
        }
    }
    void append(T value) {
        size_++;
        length_++;
        if (capacity_ == 0) {
            capacity_ =2;
            array_ = new T[capacity_];
        }
        if (size_ == capacity_) {
            MacroMemory();
        }
        array_[length_] = value;
    }
    void prepend(T value) {
        size_++;
        length_++;
        if (capacity_ == 0) {
            capacity_ =2;
            array_ = new T[capacity_];
        }
        if (size_ == capacity_) {
            MacroMemory();
        }
        for (int i = length_; i > 0; i--) {
            array_[i] = array_[i-1];
        }
        array_[0] = value;
    }
    void AppendAll(const ArrayList& arr);
    void InsertAt(int index, T value) {
        assert(index >= 0 && index < size_);
        size_++;
        length_++;
        if (size_ == capacity_) {
            MacroMemory();
        }
        for (int i = length_; i > index+1; i--) {
            array_[i] = array_[i-1];
        }
        array_[index+1] = value;
    }
    void RemoveAt(int index) {
        assert(size_ != 0);
        size_--;
        length_--;
        if (capacity_ / size_ == 4) {
            MicroMemory();
        }
        for (int i = index; i < size_; i++) {
            array_[i] = array_[i+1];
        }
        array_[length_+1] = (T)0;
    }
    void RemoveAll() {
        capacity_ = 0;
        size_ = 0;
        length_ = -1;
        delete [] array_;
        array_ = nullptr;
    }
    T Pop();
    T Dequeue();
    int Length();
    T& operator[](int index) {
        assert(index >= 0 && index < size_);
        return array_[index];
    }
    ~ArrayList() {
        std::cout << "ArrayList" << std::endl;
        delete [] array_;
    }
//    void PrintList() {
//        for (int i = 0; i < size_; i++) {
//            std::cout << array_[i] << " ";
//        }
//        std::cout << std::endl;
//    }
};

template<class T>
int ArrayList<T>::Length() {
    return size_;
}

// Нужно ли удалять конструктор перемещения и оператор присвоения перемещением?
// Как сделать заполняющий конструктор под шаблонный тип?
// Нужно ли указывать в методах значения по умолчанию в случае которых будем выбрасывать исключение?
// Какой тип нам необходимо передавать в методы, добавляющие элементы?
