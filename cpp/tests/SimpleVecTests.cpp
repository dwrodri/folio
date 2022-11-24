#define CATCH_CONFIG_MAIN
#include <catch2/catch_test_macros.hpp>
#include <containers/SimpleVec.hpp>

TEST_CASE("Default c'tor", "[main]")
{
    folio::SimpleVec v{};
    REQUIRE(v.size() == 0);
}

TEST_CASE("parameterized c'tor", "[main]")
{
    folio::SimpleVec v{12};
    REQUIRE(v.capacity() == 12);
}

TEST_CASE("parameterized + move c'tor", "[main]")
{
    folio::SimpleVec v{folio::SimpleVec{12}};
    REQUIRE(v.capacity() == 12);
}

TEST_CASE("pushBack", "[main]")
{
    folio::SimpleVec v;
    int64_t val = 12;
    v.pushBack(val);
    REQUIRE(v[0] == 12);
}

TEST_CASE("copy assign", "[main]")
{
    folio::SimpleVec v;
    v.pushBack(12);
    folio::SimpleVec q;
    q = v;
    REQUIRE(q[0] == 12);
}