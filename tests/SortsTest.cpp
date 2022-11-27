#define CATCH_CONFIG_MAIN
#include <catch2/catch_test_macros.hpp>
#include <iostream>

#include "../src/algos/Sorts.hpp"

TEST_CASE("BubbleSort", "[main]") {
    folio::SimpleVec<int> v;
    for (int i = 0; i < 12; i++) {
        v.pushBack(100 - i);
    }
    std::cout << '[';
    for (int i = 0; i < v.size(); i++) {
        std::cout << v[i] << ", ";
    }
    std::cout << "]\n";
    folio::BubbleSort(v);
    std::cout << '[';
    for (int i = 0; i < v.size(); i++) {
        std::cout << v[i] << ", ";
    }
    std::cout << "]\n";
    REQUIRE(v.isSorted());
}