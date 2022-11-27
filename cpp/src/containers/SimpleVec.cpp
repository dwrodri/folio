#include <spdlog/spdlog.h>

#include <containers/SimpleVec.hpp>
#include <iostream>
#include <cstring>
#include <memory>
#include <utility>

namespace folio
{
  void SimpleVec::augment()
  {
    int64_t *new_mem = allocator_.allocate(capacity_ * 2);
    std::memcpy(new_mem, memory_loc_, sizeof(int64_t) * capacity_);
    allocator_.deallocate(memory_loc_, capacity_);
    memory_loc_ = new_mem;
    capacity_ *= 2;
  }

  SimpleVec::SimpleVec()
      : allocator_{},
        memory_loc_{allocator_.allocate(DEFAULT_INITIAL_SIMPLEVEC_CAPACITY)},
        capacity_{DEFAULT_INITIAL_SIMPLEVEC_CAPACITY},
        size_{0}
  {
    spdlog::trace("Default c'tor");
  }

  SimpleVec::SimpleVec(size_t const capacity)
      : allocator_{},
        memory_loc_{allocator_.allocate(capacity)},
        capacity_{capacity},
        size_{0}
  {
    spdlog::trace("Parameterized c'tor");
  }

  SimpleVec::SimpleVec(SimpleVec const &other)
      : allocator_{},
        memory_loc_{allocator_.allocate(other.capacity())},
        capacity_{other.capacity()},
        size_{other.size()}
  {
    spdlog::trace("Copy c'tor");
    // does this always perform a deep copy?
    for (size_t i = 0; i < size_; i++)
    {
      memory_loc_[i] = other[i];
    }
  }

  SimpleVec::SimpleVec(SimpleVec &&other)
      : allocator_{},
        memory_loc_{std::forward<int64_t *const>(other.memory_loc_)},
        capacity_{std::forward<const size_t>(other.capacity_)},
        size_{std::forward<const size_t>(other.size_)}
  {
    other.memory_loc_ = nullptr;
    spdlog::trace("move c'tor");
  }

  SimpleVec &SimpleVec::operator=(SimpleVec const &other)
  {
    spdlog::trace("copy assign c'tor");
    allocator_ = other.allocator_;
    if (capacity_ != other.capacity_)
    {
      allocator_.deallocate(memory_loc_, capacity_);
      memory_loc_ = allocator_.allocate(other.capacity());
      capacity_ = other.capacity_;
    }
    std::memcpy(memory_loc_, other.memory_loc_, other.capacity_);
    size_ = other.size_;
    return *this;
  }

  SimpleVec &&SimpleVec::operator=(SimpleVec &&other)
  {
    spdlog::trace("move assign c'tor");
    memory_loc_ = std::forward<int64_t *const>(other.memory_loc_);
    capacity_ = std::forward<size_t const>(other.capacity_);
    size_ = std::forward<size_t const>(other.size_);
    other.memory_loc_ = nullptr;
    return std::forward<SimpleVec>(*this);
  }

  // d'tor
  SimpleVec::~SimpleVec()
  {
    spdlog::trace("d'tor");
    allocator_.deallocate(memory_loc_, capacity_);
  }

  size_t SimpleVec::capacity() const { return capacity_; }

  size_t SimpleVec::size() const { return size_; }

  void SimpleVec::pushBack(int64_t const elem)
  {
    if (static_cast<float>(size_) / capacity_ >=
        DEFAULT_SIMPLEVEC_AUGMENT_THRESHOLD)
    {
      augment();
    }
    memory_loc_[size_++] = elem;
  }

  int64_t SimpleVec::popBack()
  {
    int64_t popped = back();
    size_--;
    return popped;
  }

  int64_t &SimpleVec::front() const { return memory_loc_[0]; }

  int64_t &SimpleVec::back() const { return memory_loc_[size_ - 1]; }

  int64_t &SimpleVec::operator[](const size_t index) { return memory_loc_[index]; }

  int64_t &SimpleVec::operator[](const size_t index) const { return memory_loc_[index]; }
} // namespace folio
