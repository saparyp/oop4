#ifndef ARRAY_H
#define ARRAY_H

#include <memory>
#include <stdexcept>
#include <iostream>

template<typename T>
class Array {
private:
    T* data;
    size_t capacity_;
    size_t size_;
    
    void resize(size_t newCapacity) {
        T* newData = new T[newCapacity];
        
        for (size_t i = 0; i < size_; ++i) {
            newData[i] = std::move(data[i]);
        }
        
        delete[] data;
        data = newData;
        capacity_ = newCapacity;
    }
    
public:
    Array() : data(nullptr), capacity_(0), size_(0) {}
    
    Array(size_t initialCapacity) : capacity_(initialCapacity), size_(0) {
        data = new T[capacity_];
    }
    
    ~Array() {
        delete[] data;
    }
    
    Array(const Array& other) : capacity_(other.capacity_), size_(other.size_) {
        data = new T[capacity_];
        for (size_t i = 0; i < size_; ++i) {
            data[i] = other.data[i];
        }
    }
    
    Array& operator=(const Array& other) {
        if (this != &other) {
            delete[] data;
            capacity_ = other.capacity_;
            size_ = other.size_;
            data = new T[capacity_];
            for (size_t i = 0; i < size_; ++i) {
                data[i] = other.data[i];
            }
        }
        return *this;
    }
    
    Array(Array&& other) noexcept 
        : data(other.data), capacity_(other.capacity_), size_(other.size_) {
        other.data = nullptr;
        other.capacity_ = 0;
        other.size_ = 0;
    }
    
    Array& operator=(Array&& other) noexcept {
        if (this != &other) {
            delete[] data;
            data = other.data;
            capacity_ = other.capacity_;
            size_ = other.size_;
            other.data = nullptr;
            other.capacity_ = 0;
            other.size_ = 0;
        }
        return *this;
    }
    
    void push_back(const T& item) {
        if (size_ >= capacity_) {
            resize(capacity_ == 0 ? 1 : capacity_ * 2);
        }
        data[size_++] = item;
    }
    
    void push_back(T&& item) {
        if (size_ >= capacity_) {
            resize(capacity_ == 0 ? 1 : capacity_ * 2);
        }
        data[size_++] = std::move(item);
    }
    
    void remove(size_t index) {
        if (index >= size_) {
            throw std::out_of_range("Index out of bounds");
        }
        
        for (size_t i = index; i < size_ - 1; ++i) {
            data[i] = std::move(data[i + 1]);
        }
        --size_;
    }
    
    T& operator[](size_t index) {
        if (index >= size_) {
            throw std::out_of_range("Array index out of bounds");
        }
        return data[index];
    }
    
    const T& operator[](size_t index) const {
        if (index >= size_) {
            throw std::out_of_range("Array index out of bounds");
        }
        return data[index];
    }
    
    size_t size() const { return size_; }
    size_t capacity() const { return capacity_; }
    bool empty() const { return size_ == 0; }
    
    void clear() {
        size_ = 0;
    }
    
    template<typename U = T>
    auto totalArea() const -> decltype(std::declval<U>()->area(), double()) {
        double total = 0;
        for (size_t i = 0; i < size_; ++i) {
            if (data[i]) {
                total += data[i]->area();
            }
        }
        return total;
    }
    
    template<typename U = T>
    auto totalArea() const -> decltype(std::declval<U>().area(), double()) {
        double total = 0;
        for (size_t i = 0; i < size_; ++i) {
            total += data[i].area();
        }
        return total;
    }
};

#endif // ARRAY_H