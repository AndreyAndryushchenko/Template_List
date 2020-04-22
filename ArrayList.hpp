#pragma once

#include <cassert>

template <class T>
class ArrayList {
private:
    int capacity_;
    int size_;
    int length_;
    T* array_;
public:
    ArrayList() : capacity_(0), length_(-1), size_(0) {
        array_ = nullptr;
    }
    ArrayList(int capacity) : capacity_(capacity), length_(-1), size_(0) {
        array_ = new T[capacity];
    }
    ArrayList(const ArrayList& arr);
    ArrayList& operator = (const ArrayList& arr);
    void append(T value);
    void prepend(T value);
    void AppendAll(const ArrayList& arr);
    void InsertAt(int index, T value);
    void RemoveAt(int index);
    void RemoveAll();
    int Pop();
    int Dequeue();
    int Length();
    int GetAt(int index);
};
