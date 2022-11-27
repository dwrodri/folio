#define CATCH_CONFIG_MAIN
#include <catch2/catch_test_macros.hpp>
#include <containers/SimpleVec.hpp>
#include <spdlog/spdlog.h>

TEST_CASE("Default c'tor", "[main]")
{
    spdlog::set_level(spdlog::level::trace);
    folio::SimpleVec v{};
    REQUIRE(v.size() == 0);
}

TEST_CASE("parameterized c'tor", "[main]")
{
    folio::SimpleVec v{12};
    REQUIRE(v.capacity() == 12);
}

TEST_CASE("move c'tor", "[main]")
{
    folio::SimpleVec v{12};
    folio::SimpleVec q{std::move(v)};
    REQUIRE(v.capacity() == 12);
}

TEST_CASE("copy assign c'tor", "[main]")
{
    folio::SimpleVec v{12};
    folio::SimpleVec q{};
    q = v;
    REQUIRE(q.capacity() == 12);
}

TEST_CASE("move assign c'tor", "[main]")
{
    folio::SimpleVec v{12};
    folio::SimpleVec q{};
    q = std::move(v);
    REQUIRE(q.capacity() == 12);
}

TEST_CASE("pushBack", "[main]")
{
    folio::SimpleVec v;
    int64_t val = 12;
    v.pushBack(val);
    REQUIRE(v[0] == 12);
}
