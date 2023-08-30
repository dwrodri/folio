#define CATCH_CONFIG_MAIN
#include <catch2/catch_template_test_macros.hpp>

#include "../src/containers/SimpleMat.hpp"

TEST_CASE("Default c'tor", "[main]") {
    folio::SimpleMat<int> x{};
    REQUIRE(x.size() == 0);
}

TEST_CASE("Size", "[main]") {
    folio::SimpleMat<int> x{12, 12};
    REQUIRE(x.size() == 144);
}

TEST_CASE("Rows and Cols", "[main]") {
    folio::SimpleMat<int> x{4, 5};
    REQUIRE(x.rows() == 4);
    REQUIRE(x.cols() == 5);
}

TEST_CASE("Params c'tor", "[main]") {
    folio::SimpleMat<float> x{27, 27, 0.5};
    for (size_t i = 0; i < x.rows(); i++) {
        for (size_t j = 0; j < x.cols(); j++) {
            REQUIRE(x.at(i, j) == 0.5);
        }
    }
}

TEST_CASE("Copy c'tor", "[main]") {
    folio::SimpleMat<uint8_t> other{5, 6, 1};
    folio::SimpleMat<uint8_t> copied{other};
    for (size_t i = 0; i < copied.rows(); i++) {
        for (size_t j = 0; j < copied.cols(); j++) {
            REQUIRE(copied.at(i, j) == 1);
        }
    }
}

TEST_CASE("Move c'tor", "[main]") {
    folio::SimpleMat<uint8_t> source{10, 10, 1};
    folio::SimpleMat<uint8_t> moved{std::move(source)};
    for (size_t i = 0; i < moved.rows(); i++) {
        for (size_t j = 0; j < moved.cols(); j++) {
            REQUIRE(moved.at(i, j) == 1);
        }
    }
}