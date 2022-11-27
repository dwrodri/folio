#include <functional>
#include <utility>

#include "../containers/SimpleVec.hpp"

namespace folio {
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
}  // namespace folio