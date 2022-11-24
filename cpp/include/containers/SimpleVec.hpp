#pragma once
#include <memory>

namespace folio
{

  static constexpr size_t DEFAULT_INITIAL_SIMPLEVEC_CAPACITY = 16;
  static constexpr float DEFAULT_SIMPLEVEC_AUGMENT_THRESHOLD = 0.50;

  /**
   * @brief A simple resizeable container that mimics the same properties as std::vector
   *
   */
  class SimpleVec
  {
  private:
    // the thing that gives us memory
    std::allocator<int64_t> allocator_;
    /// the location of the data owned by this container
    int64_t *memory_loc_;
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
    SimpleVec(SimpleVec const &other);
    // move c'tor
    SimpleVec(SimpleVec const &&other);
    // copy assign op performs a shallow copy
    SimpleVec &operator=(SimpleVec const &other);
    // move assign op
    SimpleVec &&operator=(SimpleVec const &&other);
    // d'tor
    ~SimpleVec();

    /// read-only view of capacity
    size_t capacity() const;

    /// read-only view of size
    size_t size() const;

    /// add the element to the container and augment if necessary
    void pushBack(int64_t const elem);

    /// return the last value and remove it from the container
    int64_t popBack();

    /// read-write ref to first value
    int64_t &front();

    int64_t &back();

    int64_t &operator[](const size_t index);

    int64_t &operator[](const size_t index) const;
  };

} // namespace folio
