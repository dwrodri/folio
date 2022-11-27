#include <functional>
#include <numeric>
#include <utility>

#include "../containers/SimpleVec.hpp"

namespace folio {
/**
 * @brief A good sorting algo for small containers
 *
 * @tparam T underlying type of the container
 * @param v the container to be sorted
 * @param comp comparison function, defaults to std::greater<T>
 */
template <typename T>
void BubbleSort(SimpleVec<T>& v,
        std::function<bool(const T, const T)> comp = std::greater<T>()) {
    for (size_t cursor_end = v.size(); cursor_end > 1; cursor_end--) {
        for (size_t cursor = 1; cursor <= cursor_end; cursor++) {
            if (comp(v[cursor - 1], v[cursor])) {
                std::swap(v[cursor - 1], v[cursor]);
            }
        }
    }
}

/**
 * @brief Not much better than bubble sort
 *
 * @tparam T the underlying type of the container
 * @param v the container to be sorted
 * @param comp comparison function
 */
template <typename T>
void InsertionSort(SimpleVec<T>& v,
        std::function<bool(const T, const T)> comp = std::greater<T>()) {
    for (size_t i = 1; i < v.size(); i++) {
        for (size_t j = i; j > 0 && comp(v[j - 1], v[j]); j--) {
            std::swap(v[j - 1], v[j]);
        }
    }
}

template <typename T>
void QuickSort(SimpleVec<T>& v,
        std::function<bool(const T, const T)> comp = std::greater<T>()) {
    QuickSort(v, 0, v.size() - 1, comp);
}

template <typename T>
void QuickSort(SimpleVec<T>& v, ssize_t start, ssize_t end,
        std::function<bool(const T, const T)>& comp = std::greater<T>()) {
    auto partition = [](SimpleVec<T>& vv, ssize_t start, ssize_t end,
                             std::function<bool(const T, const T)> comp =
                                     std::greater<T>()) {
        T pivot = vv[end];
        ssize_t to_swap = start - 1;
        for (ssize_t i = start; i < end; i++) {
            if (comp(pivot, vv[i])) {
                std::swap(vv[++to_swap], vv[i]);
            }
        }
        std::swap(vv[++to_swap], vv[end]);
        return to_swap;
    };

    if (end <= start || start < 0) {
        return;
    }
    size_t pivot_index = partition(v, 0, end, comp);
    QuickSort(v, 0, pivot_index - 1, comp);
    QuickSort(v, pivot_index + 1, end, comp);
}
}  // namespace folio