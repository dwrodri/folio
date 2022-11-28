#define CATCH_CONFIG_MAIN
#include <catch2/catch_test_macros.hpp>
#include <iostream>

#include "../src/algos/Sorts.hpp"

template <typename T>
void logVec(folio::SimpleVec<T>& v) {
    std::cout << "[ ";
    size_t i = 0;
    for (; i < v.size() - 1; i++) {
        std::cout << v[i] << ", ";
    }
    std::cout << v[i] << " ]" << std::endl;
}

TEST_CASE("BubbleSort", "[main]") {
    folio::SimpleVec<int> v{24};
    for (int i = 0; i < 12; i++) {
        v.pushBack(100 - i);
    }
    logVec(v);
    folio::BubbleSort(v);
    logVec(v);
    REQUIRE(v.isSorted());
}

TEST_CASE("InsertionSort", "[main]") {
    folio::SimpleVec<int> v;
    for (int i = 0; i < 12; i++) {
        v.pushBack(100 - i);
    }
    folio::InsertionSort(v);
    REQUIRE(v.isSorted());
}

TEST_CASE("QuickSort", "[main]") {
    folio::SimpleVec<int> v;
    for (int i = 0; i < 12; i++) {
        v.pushBack(100 - i);
    }
    folio::QuickSort(v);
    REQUIRE(v.isSorted());
}