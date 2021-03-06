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
    b_changed.at(1, 1) = 42;

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

TEST_CASE("Multiplying irregular dimensions") {
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

TEST_CASE("Transposition: 1x1") {
    Matrix<int> a = Matrix<int>::eye(1);

    Matrix<int> transposed = a.transpose();

    REQUIRE(transposed.rows() == 1);
    REQUIRE(transposed.cols() == 1);
    REQUIRE(transposed.at(1, 1) == 1);
}

TEST_CASE("Transposition: 3x1") {
    Matrix<int> a = Matrix<int>::natural(3, 1);

    Matrix<int> transposed = a.transpose();

    REQUIRE(transposed.rows() == 1);
    REQUIRE(transposed.cols() == 3);
    REQUIRE(transposed.at(1, 1) == 1);
    REQUIRE(transposed.at(1, 2) == 2);
    REQUIRE(transposed.at(1, 3) == 3);
}

TEST_CASE("Transposition: 1x3") {
    Matrix<int> a = Matrix<int>::natural(1, 3);

    Matrix<int> transposed = a.transpose();

    REQUIRE(transposed.rows() == 3);
    REQUIRE(transposed.cols() == 1);
    REQUIRE(transposed.at(1, 1) == 1);
    REQUIRE(transposed.at(2, 1) == 2);
    REQUIRE(transposed.at(3, 1) == 3);
}

TEST_CASE("Transposition: 3x3") {
    Matrix<int> a = Matrix<int>::natural(3, 3);

    Matrix<int> transposed = a.transpose();

    REQUIRE(transposed.rows() == 3);
    REQUIRE(transposed.cols() == 3);

    REQUIRE(transposed.at(1, 1) == 1);
    REQUIRE(transposed.at(2, 1) == 2);
    REQUIRE(transposed.at(3, 1) == 3);
    REQUIRE(transposed.at(1, 2) == 4);
    REQUIRE(transposed.at(2, 2) == 5);
    REQUIRE(transposed.at(3, 2) == 6);
    REQUIRE(transposed.at(1, 3) == 7);
    REQUIRE(transposed.at(2, 3) == 8);
    REQUIRE(transposed.at(3, 3) == 9);
}

TEST_CASE("Matrix inverse: identity matrices are their own inverses") {
    Matrix<int> a = Matrix<int>::eye(1);
    Matrix<int> b = Matrix<int>::eye(2);

    REQUIRE(a.inverse() == a);
    REQUIRE(b.inverse() == b);
}

TEST_CASE("Matrix inverse: 1x1") {
    Matrix<double> a = Matrix<double>::zeros(1);
    a.at(1, 1) = 5;

    Matrix<double> inverse = a.inverse();

    REQUIRE(inverse.cols() == 1);
    REQUIRE(inverse.rows() == 1);
    REQUIRE(inverse.at(1, 1) == Approx(0.2));
}

TEST_CASE("Matrix inverse: 2x2") {
    Matrix<double> a = Matrix<double>::zeros(2, 2);
    a.at(1, 1) = 1;
    a.at(1, 2) = 2;
    a.at(2, 1) = 3;
    a.at(2, 2) = 4;

    Matrix<double> inverse = a.inverse();

    REQUIRE(inverse.cols() == 2);
    REQUIRE(inverse.rows() == 2);
    REQUIRE(inverse.at(1, 1) == Approx(-2));
    REQUIRE(inverse.at(1, 2) == Approx(1));
    REQUIRE(inverse.at(2, 1) == Approx(1.5));
    REQUIRE(inverse.at(2, 2) == Approx(-0.5));
}

TEST_CASE("Matrix inverse: 3x3") {
    Matrix<double> a = Matrix<double>::zeros(3, 3);
    a.at(1, 1) = 1;
    a.at(1, 2) = 3;
    a.at(1, 3) = 2;
    a.at(2, 1) = 1;
    a.at(2, 2) = 2;
    a.at(2, 3) = 3;
    a.at(3, 1) = 3;
    a.at(3, 2) = 2;
    a.at(3, 3) = 1;

    Matrix<double> inverse = a.inverse();

    REQUIRE(inverse.cols() == 3);
    REQUIRE(inverse.rows() == 3);
    REQUIRE(inverse.at(1, 1) == Approx(-0.333).epsilon(0.01));
    REQUIRE(inverse.at(1, 2) == Approx(0.0833).epsilon(0.01));
    REQUIRE(inverse.at(1, 3) == Approx(0.4166).epsilon(0.01));
    REQUIRE(inverse.at(2, 1) == Approx(0.6666).epsilon(0.01));
    REQUIRE(inverse.at(2, 2) == Approx(-0.416).epsilon(0.01));
    REQUIRE(inverse.at(2, 3) == Approx(-0.083).epsilon(0.01));
    REQUIRE(inverse.at(3, 1) == Approx(-0.333).epsilon(0.01));
    REQUIRE(inverse.at(3, 2) == Approx(0.5833).epsilon(0.01));
    REQUIRE(inverse.at(3, 3) == Approx(-0.083).epsilon(0.01));
}

TEST_CASE("Should throw on non-rectangular matrix") {
    REQUIRE_THROWS(Matrix<int>::zeros(1, 2).inverse());
}

TEST_CASE("Should throw if matrix is non-invertible (det=0)") {
    Matrix<int> notInvertible = Matrix<int>::zeros(2);
    notInvertible.at(1, 1) = 1;
    notInvertible.at(1, 2) = 1;
    notInvertible.at(2, 1) = 2;
    notInvertible.at(2, 2) = 2;

    REQUIRE_THROWS(notInvertible.inverse());
}


TEST_CASE("Should solve a system with 1 equation: 5x = 10") {
    Matrix<double> a = Matrix<double>::zeros(1, 1);
    a.at(1, 1) = 5;
    Matrix<double> b = Matrix<double>::zeros(1, 1);
    b.at(1, 1) = 10;

    Matrix<double> x = Matrix<double>::solve(a, b);

    REQUIRE(x.rows() == 1);
    REQUIRE(x.cols() == 1);
    REQUIRE(x.at(1, 1) == Approx(2));
}

TEST_CASE("Should solve a system with 2 equations: 2x+3y=7 and 3x+4y=11") {
    Matrix<double> a = Matrix<double>::zeros(2, 2);
    a.at(1, 1) = 2;
    a.at(1, 2) = 3;
    a.at(2, 1) = 3;
    a.at(2, 2) = 4;
    Matrix<double> b = Matrix<double>::zeros(2, 1);
    b.at(1, 1) = 8;
    b.at(2, 1) = 11;

    Matrix<double> x = Matrix<double>::solve(a, b);

    REQUIRE(x.rows() == 2);
    REQUIRE(x.cols() == 1);
    REQUIRE(x.at(1, 1) == Approx(1));
    REQUIRE(x.at(2, 1) == Approx(2));
}

TEST_CASE("Should not attempt to solve if dimensions are invalid") {
    REQUIRE_THROWS(Matrix<int>::solve(Matrix<int>::zeros(2, 3), Matrix<int>::zeros(1, 2)));
    REQUIRE_THROWS(Matrix<int>::solve(Matrix<int>::zeros(2, 2), Matrix<int>::zeros(1, 3)));
}
