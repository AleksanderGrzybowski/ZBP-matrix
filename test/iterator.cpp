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
