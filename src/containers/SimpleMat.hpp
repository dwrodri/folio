#pragma once
#include <cstring>
#include <iostream>
#include <memory>

namespace folio {

template <typename T>
/// a simple fixed-size 2D array for linear algebra ops
class SimpleMat {
  private:
    /// the location of the data owned by this container
    T* memory_loc_;
    /// the amount of virtual rows in the matrix
    size_t rows_;
    /// the size of a row in the matrix
    size_t cols_;

  public:
    // default c'tor
    SimpleMat();
    // params c'tor
    SimpleMat(size_t const rows, size_t const cols, T const fill_value = T{0});
    // copy c'tor (deep copy)
    SimpleMat(SimpleMat const& other);
    // move c'tor
    SimpleMat(SimpleMat&& other);
    // copy assign op performs a shallow copy
    SimpleMat& operator=(SimpleMat const& other);
    // move assign op
    SimpleMat&& operator=(SimpleMat&& other);
    // d'tor
    ~SimpleMat();

    /// read-only view of size
    size_t size() const;
    size_t rows() const;
    size_t cols() const;

    /// providing square bracket operator is sketchy, so instead we provide an at()
    T& at(size_t const row, size_t const col) noexcept;
    T& at(size_t const row, size_t const col) const noexcept;
};

template <typename T>
SimpleMat<T>::SimpleMat() : rows_{0}, cols_{0}, memory_loc_{nullptr} {}

template <typename T>
SimpleMat<T>::SimpleMat(size_t const rows, size_t const cols, T const fill_value)
        : rows_{rows},
          cols_{cols},
          memory_loc_{std::allocator<T>().allocate(rows * cols)} {
    for (size_t i = 0; i < rows_ * cols_; i++) {
        memory_loc_[i] = fill_value;
    }
}

template <typename T>
SimpleMat<T>::SimpleMat(SimpleMat const& other)
        : memory_loc_{std::allocator<T>().allocate(other.size())},
          rows_{other.rows_},
          cols_{other.cols_} {
    std::memcpy(memory_loc_, other.memory_loc_, rows_ * cols_ * sizeof(T));
}

template <typename T>
SimpleMat<T>::SimpleMat(SimpleMat&& other)
        : memory_loc_{other.memory_loc_}, rows_{other.rows_}, cols_{other.cols_} {
    other.memory_loc_ = nullptr;
}
template <typename T>
SimpleMat<T>::~SimpleMat() {
    std::allocator<T>().deallocate(memory_loc_, rows_ * cols_);
}

template <typename T>
size_t SimpleMat<T>::size() const {
    return rows_ * cols_;
}

template <typename T>
size_t SimpleMat<T>::rows() const {
    return rows_;
}

template <typename T>
size_t SimpleMat<T>::cols() const {
    return cols_;
}

template <typename T>
T& SimpleMat<T>::at(const size_t row, const size_t col) noexcept {
    return memory_loc_[row * cols_ + col];
}

template <typename T>
T& SimpleMat<T>::at(const size_t row, const size_t col) const noexcept {
    return memory_loc_[row * cols_ + col];
}
}  // namespace folio
