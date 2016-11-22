#define CATCH_CONFIG_MAIN

#include "catch.hpp"

#include "../src/Matrix.h"

TEST_CASE("Test framework works") {
    Matrix m;
    REQUIRE(m.test_value == 41); // fail
}