#include "catch.hpp"

#include "../src/Matrix.h"

TEST_CASE("Creating: square") {
    Matrix<int> m = Matrix<int>::zeros(4);
    REQUIRE(m.rows() == 4);
    REQUIRE(m.cols() == 4);
    for (int i = 1; i <= 4; ++i) {
        for (int j = 1; j <= 4; ++j) {
            REQUIRE(m.at(i, j) == 0);
        }
    }
}

TEST_CASE("Creating: specific dimensions") {
    Matrix<int> m = Matrix<int>::zeros(3, 4);
    REQUIRE(m.rows() == 3);
    REQUIRE(m.cols() == 4);
    for (int i = 1; i <= 3; ++i) {
        for (int j = 1; j <= 4; ++j) {
            REQUIRE(m.at(i, j) == 0);
        }
    }
}

TEST_CASE("Creating: invalid dimensions") {
    REQUIRE_THROWS(Matrix<int>::zeros(0, -1));
    REQUIRE_THROWS(Matrix<int>::zeros(-2));
}

TEST_CASE("Creating: eye") {
    Matrix<int> m = Matrix<int>::eye(3);

    for (int i = 1; i <= 3; ++i) {
        for (int j = 1; j <= 3; ++j) {
            REQUIRE(m.at(i, j) == (i == j ? 1 : 0));
        }
    }
}

TEST_CASE("Creating: clone") {
    Matrix<int> m = Matrix<int>::zeros(2);

    m.at(1, 1) = 101;
    m.at(1, 2) = 102;
    m.at(2, 1) = 103;
    m.at(2, 2) = 104;

    Matrix<int> cloned = m.clone();

    REQUIRE(cloned.rows() == m.rows());
    REQUIRE(cloned.cols() == m.cols());
    REQUIRE(cloned.at(1,1) == 101);
    REQUIRE(cloned.at(1,2) == 102);
    REQUIRE(cloned.at(2,1) == 103);
    REQUIRE(cloned.at(2,2) == 104);
}

TEST_CASE("Copy constructor") {
    Matrix<int> m = Matrix<int>::eye(2);
    Matrix<int> copied(m);

    REQUIRE(copied.at(1,1) == 1);
    REQUIRE(copied.at(1,2) == 0);
    REQUIRE(copied.at(2,1) == 0);
    REQUIRE(copied.at(2,2) == 1);
}

// Just to shut up CLion saying 'method is not used'
TEST_CASE("to_string") {
    Matrix<int>::eye(2).to_string();
}
