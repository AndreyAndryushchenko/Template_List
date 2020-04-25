#pragma once

#include <cassert>
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
    explicit ArrayList(int capacity = 2) : capacity_(capacity), length_(-1), size_(0) {
        if (capacity < 2) {
            capacity_ =2;
        }
        array_ = new T[capacity];
    }
    ArrayList(const ArrayList& arr) {
        capacity_ = arr.capacity_;
        size_ = arr.size_;
        length_ = arr.length_;
        array_ = new T[capacity_];
        for (int i = 0; i<arr.size_; i++) {
            array_[i] = arr.array_[i];
        }
    }
    ArrayList<T>& operator = (const ArrayList<T>& arr) {
        if (this != &arr) {
            capacity_ = arr.capacity_;
            size_ = arr.size_;
            length_ = arr.length_;
            delete[] array_;
            array_ = new T[capacity_];
            for (int i = 0; i < arr.size_; i++) {
                array_[i] = arr.array_[i];
            }
        }
        return *this;
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
        if (size_ == capacity_) {
            MacroMemory();
        }
        array_[length_] = value;
    }
    void prepend(T value) {
        size_++;
        length_++;
        if (size_ == capacity_) {
            MacroMemory();
        }
        for (int i = length_; i > 0; i--) {
            array_[i] = array_[i-1];
        }
        array_[0] = value;
    }
    void append_all(const ArrayList& arr) {
        for (int i = 0; i < arr.size_; i++) {
            append(arr.array_[i]);
        }
    }
    void insert_at(int index, T value) {
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
    void remove_at(int index) {
        assert(size_ > 0);
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
    void remove_all() {
        capacity_ = 2;
        size_ = 0;
        length_ = -1;
        delete [] array_;
        array_ = new T[capacity_];
    }
    T pop() {
        assert(size_ > 0);
        size_--;
        length_--;
        if (capacity_ / size_ == 4) {
            MicroMemory();
        }
        auto a = array_[size_];
        array_[size_] = 0;
        return a;
    }
    T dequeue() {
        assert(size_ > 0);
        size_--;
        length_--;
        if (capacity_ / size_ == 4) {
            MicroMemory();
        }
        auto a = array_[0];
        for (int i=0; i<size_; i++) {
            array_[i]=array_[i+1];
        }
        array_[size_] = 0;
        return a;
    }
    int length() {
        return size_;
    }
    T& operator[](int index) {
        assert(index >= 0 && index < size_);
        return array_[index];
    }
    T* begin() {
        return array_;
    }
    T* end() {
        return array_ + size_;
    }
    ~ArrayList() {
        std::cout << "ArrayList" << std::endl;
        delete [] array_;
    }
};