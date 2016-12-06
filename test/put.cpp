#include <iostream>
#include "catch.hpp"

#include "../src/Matrix.h"


TEST_CASE("Put single-element matrix into single-element matrix") {
    Matrix<int> dest = Matrix<int>::zeros(1);
    Matrix<int> src = Matrix<int>::eye(1);

    dest.put(src, 1, 1);

    REQUIRE(dest.at(1, 1) == 1);
}

TEST_CASE("Replace entire 2x2 matrix with another") {
    Matrix<int> dest = Matrix<int>::zeros(2);
    Matrix<int> src = Matrix<int>::natural(2, 2);

    dest.put(src, 1, 1);

    REQUIRE(dest.at(1, 1) == 1);
    REQUIRE(dest.at(1, 2) == 2);
    REQUIRE(dest.at(2, 1) == 3);
    REQUIRE(dest.at(2, 2) == 4);
}

TEST_CASE("Put single-element matrix into 3x3 matrix") {
    Matrix<int> dest = Matrix<int>::zeros(3);
    Matrix<int> src = Matrix<int>::eye(1);

    dest.put(src, 2, 2);

    REQUIRE(dest.at(1, 1) == 0);
    REQUIRE(dest.at(1, 2) == 0);
    REQUIRE(dest.at(1, 3) == 0);
    REQUIRE(dest.at(2, 1) == 0);
    REQUIRE(dest.at(2, 2) == 1);
    REQUIRE(dest.at(2, 3) == 0);
    REQUIRE(dest.at(3, 1) == 0);
    REQUIRE(dest.at(3, 2) == 0);
    REQUIRE(dest.at(3, 3) == 0);
}

//

TEST_CASE("Put 2x2 matrix into 3x4 matrix in top left") {
    Matrix<int> dest = Matrix<int>::natural(3, 4);
    Matrix<int> src = Matrix<int>::natural(2, 2);

    dest.put(src, 1, 1);

    REQUIRE(dest.at(1, 1) == 1);
    REQUIRE(dest.at(1, 2) == 2);
    REQUIRE(dest.at(1, 3) == 3);
    REQUIRE(dest.at(1, 4) == 4);
    REQUIRE(dest.at(2, 1) == 3);
    REQUIRE(dest.at(2, 2) == 4);
    REQUIRE(dest.at(2, 3) == 7);
    REQUIRE(dest.at(2, 4) == 8);
    REQUIRE(dest.at(3, 1) == 9);
    REQUIRE(dest.at(3, 2) == 10);
    REQUIRE(dest.at(3, 3) == 11);
    REQUIRE(dest.at(3, 4) == 12);
}


TEST_CASE("Put 2x2 matrix into 3x4 matrix in top right") {
    Matrix<int> dest = Matrix<int>::natural(3, 4);
    Matrix<int> src = Matrix<int>::natural(2, 2);

    dest.put(src, 1, 3);

    REQUIRE(dest.at(1, 1) == 1);
    REQUIRE(dest.at(1, 2) == 2);
    REQUIRE(dest.at(1, 3) == 1);
    REQUIRE(dest.at(1, 4) == 2);
    REQUIRE(dest.at(2, 1) == 5);
    REQUIRE(dest.at(2, 2) == 6);
    REQUIRE(dest.at(2, 3) == 3);
    REQUIRE(dest.at(2, 4) == 4);
    REQUIRE(dest.at(3, 1) == 9);
    REQUIRE(dest.at(3, 2) == 10);
    REQUIRE(dest.at(3, 3) == 11);
    REQUIRE(dest.at(3, 4) == 12);
}
TEST_CASE("Put 2x2 matrix into 3x4 matrix in bottom left") {
    Matrix<int> dest = Matrix<int>::natural(3, 4);
    Matrix<int> src = Matrix<int>::natural(2, 2);

    dest.put(src, 2, 1);

    REQUIRE(dest.at(1, 1) == 1);
    REQUIRE(dest.at(1, 2) == 2);
    REQUIRE(dest.at(1, 3) == 3);
    REQUIRE(dest.at(1, 4) == 4);
    REQUIRE(dest.at(2, 1) == 1);
    REQUIRE(dest.at(2, 2) == 2);
    REQUIRE(dest.at(2, 3) == 7);
    REQUIRE(dest.at(2, 4) == 8);
    REQUIRE(dest.at(3, 1) == 3);
    REQUIRE(dest.at(3, 2) == 4);
    REQUIRE(dest.at(3, 3) == 11);
    REQUIRE(dest.at(3, 4) == 12);
}
TEST_CASE("Put 2x2 matrix into 3x4 matrix in bottom right") {
    Matrix<int> dest = Matrix<int>::natural(3, 4);
    Matrix<int> src = Matrix<int>::natural(2, 2);

    dest.put(src, 2, 3);

    REQUIRE(dest.at(1, 1) == 1);
    REQUIRE(dest.at(1, 2) == 2);
    REQUIRE(dest.at(1, 3) == 3);
    REQUIRE(dest.at(1, 4) == 4);
    REQUIRE(dest.at(2, 1) == 5);
    REQUIRE(dest.at(2, 2) == 6);
    REQUIRE(dest.at(2, 3) == 1);
    REQUIRE(dest.at(2, 4) == 2);
    REQUIRE(dest.at(3, 1) == 9);
    REQUIRE(dest.at(3, 2) == 10);
    REQUIRE(dest.at(3, 3) == 3);
    REQUIRE(dest.at(3, 4) == 4);
}

TEST_CASE("Should throw and not modify destination if invalid position: single-element source") {
    Matrix<int> dest = Matrix<int>::zeros(4);
    Matrix<int> pattern = dest;
    Matrix<int> src = Matrix<int>::eye(1);

    REQUIRE_THROWS(dest.put(src, 0, 0));
    REQUIRE(dest == pattern);
    REQUIRE_THROWS(dest.put(src, 0, 1));
    REQUIRE(dest == pattern);
    REQUIRE_THROWS(dest.put(src, 1, 0));
    REQUIRE(dest == pattern);
    REQUIRE_THROWS(dest.put(src, 5, 4));
    REQUIRE(dest == pattern);
    REQUIRE_THROWS(dest.put(src, 4, 5));
    REQUIRE(dest == pattern);
}

TEST_CASE("Should throw and not modify destination if invalid position: sample matrix source") {
    Matrix<int> dest = Matrix<int>::natural(3, 4);
    Matrix<int> pattern = dest;
    Matrix<int> src = Matrix<int>::eye(2);

    REQUIRE_THROWS(dest.put(src, 3, 1));
    REQUIRE(dest == pattern);
    REQUIRE_THROWS(dest.put(src, 1, 4));
    REQUIRE(dest == pattern);
    REQUIRE_THROWS(dest.put(src, 3, 3));
    REQUIRE(dest == pattern);
    REQUIRE_THROWS(dest.put(src, 2, 4));
    REQUIRE(dest == pattern);
    REQUIRE_THROWS(dest.put(src, 3, 4));
    REQUIRE(dest == pattern);
}
