#include "catch.hpp"

#include "../src/Matrix.h"

TEST_CASE("Creating: square") {
    Matrix<int>* m = DataMatrix<int>::zeros(4);
    REQUIRE(m->rows() == 4);
    REQUIRE(m->cols() == 4);
    for (int i = 1; i <= 4; ++i) {
        for (int j = 1; j <= 4; ++j) {
            REQUIRE(m->at(i, j) == 0);
        }
    }
}

TEST_CASE("Creating: specific dimensions") {
    Matrix<int>* m = DataMatrix<int>::zeros(3, 4);
    REQUIRE(m->rows() == 3);
    REQUIRE(m->cols() == 4);
    for (int i = 1; i <= 3; ++i) {
        for (int j = 1; j <= 4; ++j) {
            REQUIRE(m->at(i, j) == 0);
        }
    }
}

TEST_CASE("Creating: invalid dimensions") {
    REQUIRE_THROWS(DataMatrix<int>::zeros(0, -1));
    REQUIRE_THROWS(DataMatrix<int>::zeros(-2));
}
