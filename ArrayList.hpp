#pragma once

#include <cassert>

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
    void append(T value);
    void prepend(T value);
    void AppendAll(const ArrayList& arr);
    void InsertAt(int index, T value);
    void RemoveAt(int index);
    void RemoveAll() {
        capacity_ = 0;
        size_ = 0;
        length_ = -1;
        delete [] array_;
        array_ = nullptr;
    }
    int Pop();
    int Dequeue();
    int Length();
    int GetAt(int index);
    ~ArrayList() {
        delete [] array_;
    }
};
