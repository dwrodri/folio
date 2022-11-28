#pragma once
#include <cstring>
#include <functional>
#include <memory>

namespace folio {

static constexpr size_t DEFAULT_INITIAL_SIMPLEVEC_CAPACITY = 16;
static constexpr float DEFAULT_SIMPLEVEC_AUGMENT_THRESHOLD = 0.50;

template <typename T>
class SimpleVec {
  private:
    // the thing that gives us memory
    std::allocator<T> allocator_;
    /// the location of the data owned by this container
    T* memory_loc_;
    /// the amount of memory we have available measured in sizeof(T)
    size_t capacity_;
    /// the amount of initialized T currently stored
    size_t size_;

    /// double the capacity of the memory buffer
    void augment();

  public:
    // default c'tor
    SimpleVec();
    // params c'tor
    SimpleVec(size_t const capacity);
    // copy c'tor
    SimpleVec(SimpleVec const& other);
    // move c'tor
    SimpleVec(SimpleVec&& other);
    // copy assign op performs a shallow copy
    SimpleVec& operator=(SimpleVec const& other);
    // move assign op
    SimpleVec&& operator=(SimpleVec&& other);
    // d'tor
    ~SimpleVec();

    /// read-only view of capacity
    size_t capacity() const;

    /// read-only view of size
    size_t size() const;

    /// add the element to the container and augment if necessary
    void pushBack(T const elem);

    /// return the last value and remove it from the container
    T popBack();

    /// read-only ref to first value
    T& front() const;

    /// read-only ref to last value
    T& back() const;

    /// index operator
    T& operator[](const size_t index) noexcept;

    /// index operator
    T& operator[](const size_t index) const noexcept;

    /// check if contents are sorted
    bool isSorted(std::function<bool(T const, T const)> comp = std::less<T>()) const;
};

template <typename T>
void SimpleVec<T>::augment() {
    T* new_mem = allocator_.allocate(capacity_ * 2);
    std::memcpy(new_mem, memory_loc_, sizeof(T) * capacity_);
    allocator_.deallocate(memory_loc_, capacity_);
    memory_loc_ = new_mem;
    capacity_ *= 2;
}

template <typename T>
SimpleVec<T>::SimpleVec()
        : allocator_{},
          memory_loc_{allocator_.allocate(DEFAULT_INITIAL_SIMPLEVEC_CAPACITY)},
          capacity_{DEFAULT_INITIAL_SIMPLEVEC_CAPACITY},
          size_{0} {}

template <typename T>
SimpleVec<T>::SimpleVec(size_t const capacity)
        : allocator_{},
          memory_loc_{allocator_.allocate(capacity)},
          capacity_{capacity},
          size_{0} {}

template <typename T>
SimpleVec<T>::SimpleVec(SimpleVec const& other)
        : allocator_{},
          memory_loc_{allocator_.allocate(other.capacity())},
          capacity_{other.capacity()},
          size_{other.size()} {
    // does this always perform a deep copy?
    for (size_t i = 0; i < size_; i++) {
        memory_loc_[i] = other[i];
    }
}

template <typename T>
SimpleVec<T>::SimpleVec(SimpleVec<T>&& other)
        : allocator_{},
          memory_loc_{std::forward<T* const>(other.memory_loc_)},
          capacity_{std::forward<const size_t>(other.capacity_)},
          size_{std::forward<const size_t>(other.size_)} {
    other.memory_loc_ = nullptr;
}

template <typename T>
SimpleVec<T>& SimpleVec<T>::operator=(SimpleVec<T> const& other) {
    allocator_ = other.allocator_;
    if (capacity_ != other.capacity_) {
        allocator_.deallocate(memory_loc_, capacity_);
        memory_loc_ = allocator_.allocate(other.capacity());
        capacity_ = other.capacity_;
    }
    std::memcpy(memory_loc_, other.memory_loc_, other.capacity_);
    size_ = other.size_;
    return *this;
}

template <typename T>
SimpleVec<T>&& SimpleVec<T>::operator=(SimpleVec&& other) {
    if (capacity_ != 0) {
        allocator_.deallocate(memory_loc_, capacity_);
    }
    memory_loc_ = std::forward<T* const>(other.memory_loc_);
    capacity_ = std::forward<size_t const>(other.capacity_);
    size_ = std::forward<size_t const>(other.size_);
    other.memory_loc_ = nullptr;
    return std::forward<SimpleVec>(*this);
}

template <typename T>
SimpleVec<T>::~SimpleVec() {
    allocator_.deallocate(memory_loc_, capacity_);
}

template <typename T>
size_t SimpleVec<T>::capacity() const {
    return capacity_;
}

template <typename T>
size_t SimpleVec<T>::size() const {
    return size_;
}

template <typename T>
void SimpleVec<T>::pushBack(T const elem) {
    if (static_cast<float>(size_) / capacity_ >= DEFAULT_SIMPLEVEC_AUGMENT_THRESHOLD) {
        augment();
    }
    memory_loc_[size_++] = elem;
}

template <typename T>
T SimpleVec<T>::popBack() {
    T popped = back();
    size_--;
    return popped;
}

template <typename T>
T& SimpleVec<T>::front() const {
    return memory_loc_[0];
}

template <typename T>
T& SimpleVec<T>::back() const {
    return memory_loc_[size_ - 1];
}

template <typename T>
T& SimpleVec<T>::operator[](const size_t index) noexcept {
    return memory_loc_[index];
}

template <typename T>
T& SimpleVec<T>::operator[](const size_t index) const noexcept {
    return memory_loc_[index];
}

template <typename T>
bool SimpleVec<T>::isSorted(std::function<bool(T const, T const)> comp) const {
    for (size_t i = 0; i < size_ - 1; i++) {
        if (!comp(memory_loc_[i], memory_loc_[i + 1])) {
            return false;
        }
    }
    return true;
}
}  // namespace folio