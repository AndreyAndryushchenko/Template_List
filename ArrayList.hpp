#pragma once

#include <cassert>
#include <iostream>

namespace array {
    template<typename T>
    class ArrayList {
    private:
        int capacity_;
        int size_;
        int length_;
        T *array_;

        void MacroMemory() {
            capacity_ *= 2;
            auto arr = static_cast<T*>(::operator new(sizeof(T) * capacity_));
            for (int i = 0; i < size_; i++) {
                ::new(arr + i) T(std::move(array_[i]));
            }
            delete array_;
            array_ = arr;
        }

        void MicroMemory() {
            capacity_ /= 2;
            auto arr = static_cast<T*>(::operator new(sizeof(T) * capacity_));
            for (int i = 0; i < size_ + 1; i++) {
                ::new(arr + i) T(std::move(array_[i]));
            }
            delete array_;
            array_ = arr;
        }

    public:
        explicit ArrayList(int capacity = 2) : capacity_(capacity), length_(-1), size_(0) {
            if (capacity < 2) {
                capacity_ = 2;
            }
            array_ = static_cast<T*>(::operator new(sizeof(T) * capacity_));
        }

        ArrayList(const ArrayList<T> &arr) {
            capacity_ = arr.capacity_;
            size_ = arr.size_;
            length_ = arr.length_;
            array_ = new T[capacity_];
            for (int i = 0; i < arr.size_; i++) {
                array_[i] = arr.array_[i];
            }
        }

        ArrayList<T> &operator=(const ArrayList<T> &arr) {
            if (this != &arr) {
                capacity_ = arr.capacity_;
                size_ = arr.size_;
                length_ = arr.length_;
                delete array_;
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
            array_ = static_cast<T*>(::operator new(sizeof(T) * capacity_));
            int i = 0;
            for (auto &el : elements) {
                ::new(array_ + i) T(std::move(el));
                i++;
            }
        }

        ArrayList<T>(ArrayList<T> &&arr) {
            capacity_ = arr.capacity_;
            size_ = arr.size_;
            length_ = arr.length_;
            array_ = arr.array_;
            arr.array_ = nullptr;
        }

        ArrayList<T> &operator=(ArrayList<T> &&arr) {
            if (this != &arr) {
                capacity_ = arr.capacity_;
                size_ = arr.size_;
                length_ = arr.length_;
                delete array_;
                array_ = arr.array_;
                arr.array_ = nullptr;
            }
            return *this;
        }

        void append(const T& value) {
            size_++;
            length_++;
            if (size_ == capacity_) {
                MacroMemory();
            }
            ::new(array_ + length_) T(value);
        }

        void append(T&& value) {
            size_++;
            length_++;
            if (size_ == capacity_) {
                MacroMemory();
            }
            ::new(array_ + length_) T(std::move(value));
        }

        void prepend(const T& value) {
            size_++;
            length_++;
            if (size_ == capacity_) {
                MacroMemory();
            }
            for (int i = length_; i > 0; i--) {
                ::new(array_ + i) T(array_[i-1]);
            }
            ::new(array_) T(value);
        }

        void prepend(T&& value) {
            size_++;
            length_++;
            if (size_ == capacity_) {
                MacroMemory();
            }
            for (int i = length_; i > 0; i--) {
                ::new(array_ + i) T(std::move(array_[i-1])); //array_[i] = array_[i - 1];
            }
            ::new(array_) T(std::move(value));
        }

        void append_all(const ArrayList<T> &arr) {
            for (int i = 0; i < arr.size_; i++) {
                append(arr.array_[i]);
            }
        }

        void append_all(ArrayList<T> &&arr) = delete;

        void insert_at(int index, const T& value) {
            assert(index >= 0 && index < size_);
            size_++;
            length_++;
            if (size_ == capacity_) {
                MacroMemory();
            }
            for (int i = length_; i > index + 1; i--) {
                ::new(array_ + i) T(array_[i-1]);
            }
            ::new(array_ + index + 1) T(value);
        }

        void insert_at(int index, T&& value) {
            assert(index >= 0 && index < size_);
            size_++;
            length_++;
            if (size_ == capacity_) {
                MacroMemory();
            }
            for (int i = length_; i > index + 1; i--) {
                ::new(array_ + i) T(std::move(array_[i-1]));
            }
            ::new(array_ + index + 1) T(std::move(value));
        }

        void remove_at(int index) {
            assert(size_ > 0);
            size_--;
            length_--;
            if (capacity_ / size_ == 4) {
                MicroMemory();
            }
            for (int i = index; i < size_; i++) {
                array_[i].~T();
                ::new(array_ + i) T(std::move(array_[i+1]));
            }
            array_[size_].~T();
        }

        void remove_all() {
            capacity_ = 2;
            size_ = 0;
            length_ = -1;
            delete array_;
            array_ = static_cast<T*>(::operator new(sizeof(T) * capacity_));
        }

        T pop() {
            assert(size_ > 0);
            auto a = std::move(array_[length_]);
            remove_at(length_);
            return a;
        }

        T dequeue() {
            assert(size_ > 0);
            auto a = std::move(array_[0]);
            remove_at(0);
            return a;
        }

        int length() {
            return size_;
        }

        T &operator[](int index) {
            assert(index >= 0 && index < size_);
            return array_[index];
        }

        const T& at(int index) const {
            assert(index >= 0 && index < size_);
            return array_[index];
        }

        T *begin() {
            return array_;
        }

        T *end() {
            return array_ + size_;
        }

        ~ArrayList() {
            std::cout << "ArrayList" << std::endl;
            delete array_;
        }
    };
}
