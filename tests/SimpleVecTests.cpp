#define CATCH_CONFIG_MAIN
#include <catch2/catch_test_macros.hpp>

#include "../src/containers/SimpleVec.hpp"

TEST_CASE("Default c'tor", "[main]") {
    folio::SimpleVec<int> v{};
    REQUIRE(v.size() == 0);
}

TEST_CASE("operator[]", "[main]") {
    folio::SimpleVec<int> v{};
    v[0] = 12;
    REQUIRE(v[0] == 12);
}

TEST_CASE("pushBack", "[main]") {
    folio::SimpleVec<int> v;
    int64_t val = 12;
    v.pushBack(val);
    REQUIRE(v[0] == 12);
}

TEST_CASE("parameterized c'tor", "[main]") {
    folio::SimpleVec<int> v{12};
    REQUIRE(v.capacity() == 12);
}

TEST_CASE("Copy c'tor", "[main]") {
    folio::SimpleVec<int> q{12};
    folio::SimpleVec<int> v{q};
    REQUIRE(v.capacity() == 12);
}

TEST_CASE("move c'tor", "[main]") {
    folio::SimpleVec<int> v{12};
    folio::SimpleVec<int> q{std::move(v)};
    REQUIRE(q.capacity() == 12);
}

TEST_CASE("copy assign c'tor", "[main]") {
    folio::SimpleVec<int> v{12};
    folio::SimpleVec<int> q{};
    q = v;
    REQUIRE(q.capacity() == 12);
}

TEST_CASE("move assign c'tor", "[main]") {
    folio::SimpleVec<int> v{12};
    folio::SimpleVec<int> q{12};
    q = std::move(v);
    REQUIRE(q.capacity() == 12);
}

TEST_CASE("front", "[main]") {
    folio::SimpleVec<int> v;
    v[0] = 12;
    REQUIRE(v.Front() == 12);
}

TEST_CASE("back", "[main]") {
    folio::SimpleVec<int> v;
    v.pushBack(12);
    REQUIRE(v.back() == 12);
}

TEST_CASE("popBack", "[main]") {
    folio::SimpleVec<int> v;
    v.pushBack(12);
    v.pushBack(13);
    int64_t val = v.popBack();
    REQUIRE(val == 13);
    REQUIRE(v.size() == 1);
}