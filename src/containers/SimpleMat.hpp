#pragma once
#include <cstring>
#include <memory>

namespace folio {

static constexpr size_t DEFAULT_INITIAL_SIMPLEVEC_CAPACITY = 16;
static constexpr float DEFAULT_SIMPLEVEC_AUGMENT_THRESHOLD = 0.50;

template <typename T>
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
    SimpleMat() = default;
    // params c'tor
    SimpleMat(size_t const rows, size_t const cols, const T fill_value = T{0});
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

    /// since this is complying with C++17, we need a method of accessing nested
    T& at(size_t const row, size_t const col) noexcept;
    T& at(size_t const row, size_t const col) const;
};

template <typename T>
SimpleMat<T>::SimpleMat(size_t const rows, size_t const cols, T const fill_value = T{0})
        : rows_{rows},
          cols_{cols},
          memory_loc_{std::allocator<T>.allocate(rows * cols)} {
    std::memcpy_s(memory_loc_, rows_ * cols_, other.memory_loc_, other.size())
}

template <typename T>
SimpleMat<T>::SimpleMat(SimpleMat const& other)
        : memory_loc_{std::allocator<T>.allocate(other.size())},
          rows_{other.rows_},
          cols_{other.cols_},
          // does this always perform a deep copy?
          std::strncpy(other.memory_loc_, memory_loc_, rows * cols * sizeof(T));

}

template <typename T>
SimpleMat<T>::~SimpleMat() {
    allocator_.deallocate(memory_loc_, rows_ * cols_);
}

template <typename T>
size_t SimpleMat<T>::size() const {
    return rows_ * cols_;
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
