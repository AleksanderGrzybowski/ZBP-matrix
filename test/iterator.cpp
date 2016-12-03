#include <iostream>
#include "catch.hpp"

#include "../src/Matrix.h"

TEST_CASE("Iterators: should iterate over sample matrix") {
    Matrix<int> matrix = Matrix<int>::natural(2, 3);
    Matrix<int>::matrix_iterator it = matrix.begin();

    for (int i = 1; i <= 6; ++i) {
        REQUIRE(*it == i);
        ++it;
    }
}

TEST_CASE("Iterators: should iterate over row matrix") {
    Matrix<int> matrix = Matrix<int>::natural(1, 10);
    Matrix<int>::matrix_iterator it = matrix.begin();

    for (int i = 1; i <= 10; ++i) {
        REQUIRE(*it == i);
        ++it;
    }
}

TEST_CASE("Iterators: should iterate over col matrix") {
    Matrix<int> matrix = Matrix<int>::natural(10, 1);
    Matrix<int>::matrix_iterator it = matrix.begin();

    for (int i = 1; i <= 10; ++i) {
        REQUIRE(*it == i);
        ++it;
    }
}

TEST_CASE("Iterators: should iterate over sample view of matrix") {
    Matrix<int> matrix = Matrix<int>::natural(3, 3);
    Matrix<int> view = matrix.view(1, 1, 2, 2);
    Matrix<int>::matrix_iterator it = view.begin();

    REQUIRE(*it == 1);
    ++it;
    REQUIRE(*it == 2);
    ++it;
    REQUIRE(*it == 4);
    ++it;
    REQUIRE(*it == 5);
    ++it;
}

TEST_CASE("Iterators: should iterate over row view of matrix") {
    Matrix<int> matrix = Matrix<int>::natural(3, 3);
    Matrix<int> view = matrix.view(1, 1, 1, 3);
    Matrix<int>::matrix_iterator it = view.begin();

    for (int i = 1; i <= 3; ++i) {
        REQUIRE(*it == i);
        ++it;
    }
}

TEST_CASE("Iterators: should iterate over col view of matrix") {
    Matrix<int> matrix = Matrix<int>::natural(3, 3);
    Matrix<int> view = matrix.view(1, 1, 3, 1);
    Matrix<int>::matrix_iterator it = view.begin();

    REQUIRE(*it == 1);
    ++it;
    REQUIRE(*it == 4);
    ++it;
    REQUIRE(*it == 7);
}

TEST_CASE("Should throw when attempting to go past the end of iterator") {
    Matrix<int> matrix = Matrix<int>::natural(2, 2);
    Matrix<int>::matrix_iterator it = matrix.begin();
    REQUIRE_NOTHROW(++it);
    REQUIRE_NOTHROW(++it);
    REQUIRE_NOTHROW(++it);
    REQUIRE_NOTHROW(++it);
    REQUIRE_THROWS(++it);
}

TEST_CASE("Should properly implement == operator") {
    Matrix<int> matrix = Matrix<int>::natural(3, 3);
    Matrix<int>::matrix_iterator it_1 = matrix.begin();
    Matrix<int>::matrix_iterator it_2 = matrix.begin();

    REQUIRE(it_1 == it_2);
}

TEST_CASE("Should properly implement end() method") {
    Matrix<int> matrix = Matrix<int>::natural(2, 2);
    Matrix<int>::matrix_iterator it_1 = matrix.begin();
    Matrix<int>::matrix_iterator it_2 = matrix.end();

    ++it_1;
    ++it_1;
    ++it_1;
    ++it_1;
    REQUIRE(it_1 == it_2);
}

TEST_CASE("Integration test of begin() and end() ") {
    Matrix<int> matrix = Matrix<int>::natural(3, 2);

    int i = 1;
    for (Matrix<int>::matrix_iterator it = matrix.begin(); it != matrix.end(); ++it) {
        REQUIRE(i == *it);
        i++;
    }
}

TEST_CASE("C++ foreach") {
    Matrix<int> matrix = Matrix<int>::natural(3, 2);

    int i = 1;
    for (auto& val: matrix) {
        REQUIRE(i == val);
        i++;
    }
}
