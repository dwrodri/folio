#define CATCH_CONFIG_MAIN
#include <catch2/catch_test_macros.hpp>
#include <iostream>

#include "../src/containers/BinaryTree.hpp"

TEST_CASE("default c'tor", "[main]") {
    folio::BinaryTree<int> b;
    REQUIRE(b.root() == nullptr);
}

TEST_CASE("init list c'tor", "[main]") {
    folio::BinaryTree<char> b{'q', 'w', 'e', 'r', 't', 'y'};
    REQUIRE(b.root()->value == 'q');
}

TEST_CASE("search", "[main]") {
    folio::BinaryTree<char> b{'q', 'w', 'e', 'r', 't', 'y'};
    for (char c : {'q', 'w', 'e', 'r', 't', 'y'}) {
        REQUIRE(b.contains(c));
    }
}