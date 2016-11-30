#include "catch.hpp"

#include "../src/Matrix.h"

Matrix<int> make1234() {
    Matrix<int> a = Matrix<int>::eye(2);
    a.at(1, 1) = 1;
    a.at(1, 2) = 2;
    a.at(2, 1) = 3;
    a.at(2, 2) = 4;
    return a;
}

Matrix<int> make5678() {
    Matrix<int> a = Matrix<int>::eye(2);
    a.at(1, 1) = 5;
    a.at(1, 2) = 6;
    a.at(2, 1) = 7;
    a.at(2, 2) = 8;
    return a;
}


TEST_CASE("Operations: +") {
    Matrix<int> a = make1234();
    Matrix<int> b = make5678();

    Matrix<int> sum = a + b;
    REQUIRE(sum.at(1, 1) == 6);
    REQUIRE(sum.at(1, 2) == 8);
    REQUIRE(sum.at(2, 1) == 10);
    REQUIRE(sum.at(2, 2) == 12);
}

TEST_CASE("Operations: + should throw if incompatible dims") {
    REQUIRE_THROWS(Matrix<int>::eye(2) + Matrix<int>::eye(1););
}

TEST_CASE("Operations: -") {
    Matrix<int> a = make1234();
    Matrix<int> b = make5678();

    Matrix<int> diff = a - b;
    REQUIRE(diff.at(1, 1) == -4);
    REQUIRE(diff.at(1, 2) == -4);
    REQUIRE(diff.at(2, 1) == -4);
    REQUIRE(diff.at(2, 2) == -4);
}

TEST_CASE("Operations: - should throw if incompatible dims") {
    REQUIRE_THROWS(Matrix<int>::eye(2) - Matrix<int>::eye(1););
}

TEST_CASE("Operations: +=") {
    Matrix<int> a = make1234();
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
    Matrix<int> a = make1234();
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
    Matrix<int> a = make1234();

    a *= 10;
    REQUIRE(a.at(1, 1) == 10);
    REQUIRE(a.at(1, 2) == 20);
    REQUIRE(a.at(2, 1) == 30);
    REQUIRE(a.at(2, 2) == 40);
}

TEST_CASE("Operations: *") {
    Matrix<int> a = make1234();

    Matrix<int> result = a * 10;
    REQUIRE(result.at(1, 1) == 10);
    REQUIRE(result.at(1, 2) == 20);
    REQUIRE(result.at(2, 1) == 30);
    REQUIRE(result.at(2, 2) == 40);
}
