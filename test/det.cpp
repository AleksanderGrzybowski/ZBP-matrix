#include "catch.hpp"

#include "../src/Matrix.h"

TEST_CASE("remove_intersection: should not alter 1x1, 1xN or Nx1 matrix") {
    REQUIRE_THROWS(Matrix<int>::eye(1).remove_intersection(1, 1));
    REQUIRE_THROWS(Matrix<int>::zeros(1, 5).remove_intersection(1, 1));
    REQUIRE_THROWS(Matrix<int>::zeros(5, 1).remove_intersection(1, 1));
}

TEST_CASE("remove_intersection: should not try to remove at nonexistent coordinates") {
    Matrix<int> matrix = Matrix<int>::natural(3, 3);

    REQUIRE_THROWS(matrix.remove_intersection(-1, -1));
    REQUIRE_THROWS(matrix.remove_intersection(0, 0));
    REQUIRE_THROWS(matrix.remove_intersection(4, 3));
    REQUIRE_THROWS(matrix.remove_intersection(3, 4));
    REQUIRE_THROWS(matrix.remove_intersection(4, 4));
}


TEST_CASE("remove_intersection: should properly remove intersections") {
    Matrix<int> pattern = Matrix<int>::natural(3, 3);

    {
        Matrix<int> removed = pattern.remove_intersection(1, 1);
        REQUIRE(removed.at(1, 1) == 5);
        REQUIRE(removed.at(1, 2) == 6);
        REQUIRE(removed.at(2, 1) == 8);
        REQUIRE(removed.at(2, 2) == 9);
    }

    {
        Matrix<int> removed = pattern.remove_intersection(1, 2);
        REQUIRE(removed.at(1, 1) == 4);
        REQUIRE(removed.at(1, 2) == 6);
        REQUIRE(removed.at(2, 1) == 7);
        REQUIRE(removed.at(2, 2) == 9);
    }

    {
        Matrix<int> removed = pattern.remove_intersection(1, 3);
        REQUIRE(removed.at(1, 1) == 4);
        REQUIRE(removed.at(1, 2) == 5);
        REQUIRE(removed.at(2, 1) == 7);
        REQUIRE(removed.at(2, 2) == 8);
    }

    {
        Matrix<int> removed = pattern.remove_intersection(2, 1);
        REQUIRE(removed.at(1, 1) == 2);
        REQUIRE(removed.at(1, 2) == 3);
        REQUIRE(removed.at(2, 1) == 8);
        REQUIRE(removed.at(2, 2) == 9);
    }

    {
        Matrix<int> removed = pattern.remove_intersection(2, 2);
        REQUIRE(removed.at(1, 1) == 1);
        REQUIRE(removed.at(1, 2) == 3);
        REQUIRE(removed.at(2, 1) == 7);
        REQUIRE(removed.at(2, 2) == 9);
    }

    {
        Matrix<int> removed = pattern.remove_intersection(2, 3);
        REQUIRE(removed.at(1, 1) == 1);
        REQUIRE(removed.at(1, 2) == 2);
        REQUIRE(removed.at(2, 1) == 7);
        REQUIRE(removed.at(2, 2) == 8);
    }

    {
        Matrix<int> removed = pattern.remove_intersection(3, 1);
        REQUIRE(removed.at(1, 1) == 2);
        REQUIRE(removed.at(1, 2) == 3);
        REQUIRE(removed.at(2, 1) == 5);
        REQUIRE(removed.at(2, 2) == 6);
    }

    {
        Matrix<int> removed = pattern.remove_intersection(3, 2);
        REQUIRE(removed.at(1, 1) == 1);
        REQUIRE(removed.at(1, 2) == 3);
        REQUIRE(removed.at(2, 1) == 4);
        REQUIRE(removed.at(2, 2) == 6);
    }

    {
        Matrix<int> removed = pattern.remove_intersection(3, 3);
        REQUIRE(removed.at(1, 1) == 1);
        REQUIRE(removed.at(1, 2) == 2);
        REQUIRE(removed.at(2, 1) == 4);
        REQUIRE(removed.at(2, 2) == 5);
    }
}

TEST_CASE("Should not try to calculate determinant of non-square matrix") {
    REQUIRE_THROWS(Matrix<int>::zeros(1, 2).det());
}

TEST_CASE("Determinant of 1x1 matrix") {
    Matrix<int> matrix = Matrix<int>::eye(1);
    matrix.at(1, 1) = 42;

    REQUIRE(matrix.det() == 42);
}

TEST_CASE("Determinant of 2x2 matrix") {
    Matrix<int> matrix = Matrix<int>::natural(2, 2);

    REQUIRE(matrix.det() == -2);
}

TEST_CASE("Determinant of 3x3 matrix") {
    Matrix<int> matrix = Matrix<int>::eye(3);
    matrix.at(1, 1) = 5;
    matrix.at(1, 2) = 3;
    matrix.at(1, 3) = 4;
    matrix.at(2, 1) = 1;
    matrix.at(2, 2) = 2;
    matrix.at(2, 3) = 9;
    matrix.at(3, 1) = 7;
    matrix.at(3, 2) = 8;
    matrix.at(3, 3) = 6;

    REQUIRE(matrix.det() == -153);
}

TEST_CASE("Integration case: 6x6") {
    Matrix<int> matrix = Matrix<int>::eye(6);
    matrix.at(1, 1) = 9;
    matrix.at(1, 2) = 6;
    matrix.at(1, 3) = 3;
    matrix.at(1, 4) = 7;
    matrix.at(1, 5) = 8;
    matrix.at(1, 6) = 1;
    matrix.at(2, 1) = 0;
    matrix.at(2, 2) = 9;
    matrix.at(2, 3) = 5;
    matrix.at(2, 4) = 7;
    matrix.at(2, 5) = 4;
    matrix.at(2, 6) = 3;
    matrix.at(3, 1) = 1;
    matrix.at(3, 2) = 2;
    matrix.at(3, 3) = 3;
    matrix.at(3, 4) = 5;
    matrix.at(3, 5) = 1;
    matrix.at(3, 6) = 2;
    matrix.at(4, 1) = 6;
    matrix.at(4, 2) = 4;
    matrix.at(4, 3) = 1;
    matrix.at(4, 4) = 3;
    matrix.at(4, 5) = 5;
    matrix.at(4, 6) = 1;
    matrix.at(5, 1) = 1;
    matrix.at(5, 2) = 6;
    matrix.at(5, 3) = 1;
    matrix.at(5, 4) = 4;
    matrix.at(5, 5) = 0;
    matrix.at(5, 6) = 9;
    matrix.at(6, 1) = 1;
    matrix.at(6, 2) = 5;
    matrix.at(6, 3) = 1;
    matrix.at(6, 4) = 3;
    matrix.at(6, 5) = 9;
    matrix.at(6, 6) = 8;

    REQUIRE(matrix.det() == 4707);
}