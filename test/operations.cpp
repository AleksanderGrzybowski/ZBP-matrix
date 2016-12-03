#include "catch.hpp"

#include "../src/Matrix.h"

Matrix<int> make5678() {
    Matrix<int> a = Matrix<int>::eye(2);
    a.at(1, 1) = 5;
    a.at(1, 2) = 6;
    a.at(2, 1) = 7;
    a.at(2, 2) = 8;
    return a;
}


TEST_CASE("Operations: +") {
    Matrix<int> a = Matrix<int>::natural(2,2);
    Matrix<int> b = make5678();

    Matrix<int> result = a + b;
    REQUIRE(result.at(1, 1) == 6);
    REQUIRE(result.at(1, 2) == 8);
    REQUIRE(result.at(2, 1) == 10);
    REQUIRE(result.at(2, 2) == 12);
}

TEST_CASE("Operations: + should throw if incompatible dims") {
    REQUIRE_THROWS(Matrix<int>::eye(2) + Matrix<int>::eye(1););
}

TEST_CASE("Operations: -") {
    Matrix<int> a = Matrix<int>::natural(2,2);
    Matrix<int> b = make5678();

    Matrix<int> result = a - b;
    REQUIRE(result.at(1, 1) == -4);
    REQUIRE(result.at(1, 2) == -4);
    REQUIRE(result.at(2, 1) == -4);
    REQUIRE(result.at(2, 2) == -4);
}

TEST_CASE("Operations: - should throw if incompatible dims") {
    REQUIRE_THROWS(Matrix<int>::eye(2) - Matrix<int>::eye(1););
}

TEST_CASE("Operations: +=") {
    Matrix<int> a = Matrix<int>::natural(2,2);
    Matrix<int> b = make5678();

    a += b;
    REQUIRE(a.at(1, 1) == 6);
    REQUIRE(a.at(1, 2) == 8);
    REQUIRE(a.at(2, 1) == 10);
    REQUIRE(a.at(2, 2) == 12);
}

TEST_CASE("Operations: += should throw if incompatible dims") {
    REQUIRE_THROWS(Matrix<int>::eye(2) += Matrix<int>::eye(1););
}

TEST_CASE("Operations: -=") {
    Matrix<int> a = Matrix<int>::natural(2,2);
    Matrix<int> b = make5678();

    a -= b;
    REQUIRE(a.at(1, 1) == -4);
    REQUIRE(a.at(1, 2) == -4);
    REQUIRE(a.at(2, 1) == -4);
    REQUIRE(a.at(2, 2) == -4);
}

TEST_CASE("Operations: -= should throw if incompatible dims") {
    REQUIRE_THROWS(Matrix<int>::eye(2) -= Matrix<int>::eye(1););
}

TEST_CASE("Operations: *=") {
    Matrix<int> a = Matrix<int>::natural(2,2);

    a *= 10;
    REQUIRE(a.at(1, 1) == 10);
    REQUIRE(a.at(1, 2) == 20);
    REQUIRE(a.at(2, 1) == 30);
    REQUIRE(a.at(2, 2) == 40);
}

TEST_CASE("Operations: *") {
    Matrix<int> a = Matrix<int>::natural(2,2);

    Matrix<int> result = a * 10;
    REQUIRE(result.at(1, 1) == 10);
    REQUIRE(result.at(1, 2) == 20);
    REQUIRE(result.at(2, 1) == 30);
    REQUIRE(result.at(2, 2) == 40);
}
