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

TEST_CASE("Operations: == and !=, matrices of different dimensions are not equal") {
    Matrix<int> a = Matrix<int>::eye(2);
    Matrix<int> b = Matrix<int>::eye(3);

    REQUIRE(a != b);
}

TEST_CASE("Operations: == and !=, matrices are equal when they have the same dimensions and elements") {
    Matrix<int> a = Matrix<int>::eye(2);
    Matrix<int> b_equal = Matrix<int>::eye(2);
    Matrix<int> b_changed = Matrix<int>::eye(2);
    b_changed.at(1,1) = 42;

    REQUIRE(a == b_equal);
    REQUIRE(a != b_changed);
}


TEST_CASE("Operations: +") {
    Matrix<int> a = Matrix<int>::natural(2, 2);
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
    Matrix<int> a = Matrix<int>::natural(2, 2);
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
    Matrix<int> a = Matrix<int>::natural(2, 2);
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
    Matrix<int> a = Matrix<int>::natural(2, 2);
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

TEST_CASE("Operations: *= by scalar") {
    Matrix<int> a = Matrix<int>::natural(2, 2);

    a *= 10;
    REQUIRE(a.at(1, 1) == 10);
    REQUIRE(a.at(1, 2) == 20);
    REQUIRE(a.at(2, 1) == 30);
    REQUIRE(a.at(2, 2) == 40);
}

TEST_CASE("Operations: * by scalar") {
    Matrix<int> a = Matrix<int>::natural(2, 2);

    Matrix<int> result = a * 10;
    REQUIRE(result.at(1, 1) == 10);
    REQUIRE(result.at(1, 2) == 20);
    REQUIRE(result.at(2, 1) == 30);
    REQUIRE(result.at(2, 2) == 40);
}

// matrix multiplication

TEST_CASE("Should not multiply matrices of incompatible dimensions") {
    Matrix<int> a = Matrix<int>::natural(3, 2);
    Matrix<int> b = Matrix<int>::natural(1, 2);

    REQUIRE_THROWS(a * b);
}

TEST_CASE("Simple square multiplication") {
    Matrix<int> a = Matrix<int>::natural(2, 2);
    Matrix<int> b = Matrix<int>::natural(2, 2);

    Matrix<int> result = a * b;
    REQUIRE(result.rows() == 2);
    REQUIRE(result.cols() == 2);
    REQUIRE(result.at(1, 1) == 7);
    REQUIRE(result.at(1, 2) == 10);
    REQUIRE(result.at(2, 1) == 15);
    REQUIRE(result.at(2, 2) == 22);
}

TEST_CASE("3x2 * 2x3") {
    Matrix<int> a = Matrix<int>::natural(3, 2);
    Matrix<int> b = Matrix<int>::natural(2, 3);

    Matrix<int> result = a * b;
    REQUIRE(result.rows() == 3);
    REQUIRE(result.cols() == 3);
    REQUIRE(result.at(1, 1) == 9);
    REQUIRE(result.at(1, 2) == 12);
    REQUIRE(result.at(1, 3) == 15);
    REQUIRE(result.at(2, 1) == 19);
    REQUIRE(result.at(2, 2) == 26);
    REQUIRE(result.at(2, 3) == 33);
    REQUIRE(result.at(3, 1) == 29);
    REQUIRE(result.at(3, 2) == 40);
    REQUIRE(result.at(3, 3) == 51);
}

TEST_CASE("Irregular dimensions") {
    Matrix<int> a = Matrix<int>::natural(3, 2);
    Matrix<int> b = Matrix<int>::natural(2, 4);

    Matrix<int> result = a * b;
    REQUIRE(result.rows() == 3);
    REQUIRE(result.cols() == 4);
    REQUIRE(result.at(1, 1) == 11);
    REQUIRE(result.at(1, 2) == 14);
    REQUIRE(result.at(1, 3) == 17);
    REQUIRE(result.at(1, 4) == 20);
    REQUIRE(result.at(2, 1) == 23);
    REQUIRE(result.at(2, 2) == 30);
    REQUIRE(result.at(2, 3) == 37);
    REQUIRE(result.at(2, 4) == 44);
    REQUIRE(result.at(3, 1) == 35);
    REQUIRE(result.at(3, 2) == 46);
    REQUIRE(result.at(3, 3) == 57);
    REQUIRE(result.at(3, 4) == 68);
}


