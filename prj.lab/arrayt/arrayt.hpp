#pragma once
#ifndef ARRAYT_ARRAYT_HPP_20241202
#define ARRAYT_ARRAYT_HPP_20241202

#include <cstddef>
#include <memory>
#include <stdexcept>
#include <algorithm> // for std::copy, std::copy_backward, std::fill

template<class T>
class ArrayT {
public:
    ArrayT() = default;
    ArrayT(const ArrayT& src);

    // size must be > 0
    explicit ArrayT(std::ptrdiff_t size);

    ~ArrayT() = default;

    ArrayT& operator=(const ArrayT& rhs);

    [[nodiscard]] std::ptrdiff_t Size() const noexcept { return size_; }

    // Resizes the array to 'size'. If new size > current size,
    // new elements are value-initialized to T().
    // size must be >= 0
    void Resize(std::ptrdiff_t size);

    // Access element by index, throws if idx is out of range.
    [[nodiscard]] T& operator[](std::ptrdiff_t idx);
    [[nodiscard]] const T& operator[](std::ptrdiff_t idx) const;

    // Insert a value at position idx, shifting subsequent elements forward.
    // 0 <= idx <= size_ allowed.
    // Increases the array size by 1.
    void Insert(std::ptrdiff_t idx, const T& val);

    // Remove element at position idx, shifting subsequent elements backward.
    // 0 <= idx < size_ must hold.
    void Remove(std::ptrdiff_t idx);

private:
    std::ptrdiff_t capacity_ = 0;
    std::ptrdiff_t size_ = 0;
    std::unique_ptr<T[]> data_;
};

// Copy constructor
template<class T>
ArrayT<T>::ArrayT(const ArrayT<T>& src)
  : capacity_(src.size_)
  , size_(src.size_)
  , data_(std::make_unique<T[]>(src.size_)) {
    std::copy(src.data_.get(), src.data_.get() + size_, data_.get());
}

// Constructor with size
template<class T>
ArrayT<T>::ArrayT(std::ptrdiff_t size)
  : capacity_(size)
  , size_(size) {
    if (size_ <= 0) {
        throw std::invalid_argument("ArrayT::ArrayT - non positive size");
    }
    data_ = std::make_unique<T[]>(size_);
}

// Assignment operator
template<class T>
ArrayT<T>& ArrayT<T>::operator=(const ArrayT<T>& rhs) {
    if (this != &rhs) {
        Resize(rhs.size_);
        std::copy(rhs.data_.get(), rhs.data_.get() + size_, data_.get());
    }
    return *this;
}

// Resize method
template<class T>
void ArrayT<T>::Resize(std::ptrdiff_t size) {
    if (size < 0) {
        throw std::invalid_argument("ArrayT::Resize - negative size");
    }

    if (size > capacity_) {
        // Need a larger buffer
        auto newData = std::make_unique<T[]>(size);
        if (size_ > 0) {
            std::copy(data_.get(), data_.get() + size_, newData.get());
        }
        data_ = std::move(newData);
        capacity_ = size;
    } else if (size > size_) {
        // Increasing size within capacity, initialize new elements
        std::fill(data_.get() + size_, data_.get() + size, T());
    }

    size_ = size;
}

// Element access
template<class T>
T& ArrayT<T>::operator[](std::ptrdiff_t idx) {
    if (idx < 0 || idx >= size_) {
        throw std::invalid_argument("ArrayT::operator[] - invalid index");
    }
    return data_[idx];
}

template<class T>
const T& ArrayT<T>::operator[](std::ptrdiff_t idx) const {
    if (idx < 0 || idx >= size_) {
        throw std::invalid_argument("ArrayT::operator[] - invalid index");
    }
    return data_[idx];
}

// Insert an element at idx
template<class T>
void ArrayT<T>::Insert(std::ptrdiff_t idx, const T& val) {
    if (idx < 0 || idx > size_) {
        throw std::invalid_argument("ArrayT::Insert - invalid index");
    }

    Resize(size_ + 1);
    if (idx != size_ - 1) {
        // Move elements [idx, end-1] one step forward
        std::copy_backward(data_.get() + idx, data_.get() + size_ - 1, data_.get() + size_);
    }
    data_[idx] = val;
}

// Remove element at idx
template<class T>
void ArrayT<T>::Remove(std::ptrdiff_t idx) {
    if (idx < 0 || idx >= size_) {
        throw std::invalid_argument("ArrayT::Remove - invalid index");
    }

    if (idx != size_ - 1) {
        // Move elements [idx+1, end] one step backward
        std::copy(data_.get() + idx + 1, data_.get() + size_, data_.get() + idx);
    }
    Resize(size_ - 1);
}

#endif // ARRAYT_ARRAYT_HPP_20241202
