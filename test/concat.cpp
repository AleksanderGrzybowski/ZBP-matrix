#include "catch.hpp"

#include "../src/Matrix.h"

TEST_CASE("concat_horizontal: should not concat matrices with nonmatching dimensions") {
    Matrix<int> first = Matrix<int>::natural(3, 3);
    Matrix<int> second = Matrix<int>::natural(4, 3);
    REQUIRE_THROWS(first.concat_horizontal(second));
}

TEST_CASE("concat_horizontal: should concat two 1-element matrices") {
    Matrix<int> first = Matrix<int>::eye(1);
    Matrix<int> second = Matrix<int>::zeros(1);
    Matrix<int> result = first.concat_horizontal(second);

    REQUIRE(result.at(1, 1) == 1);
    REQUIRE(result.at(1, 2) == 0);
}

TEST_CASE("concat_horizontal: should concat two square matrices") {
    Matrix<int> first = Matrix<int>::eye(2);
    Matrix<int> second = Matrix<int>::natural(2, 2);
    Matrix<int> result = first.concat_horizontal(second);

    REQUIRE(result.at(1, 1) == 1);
    REQUIRE(result.at(1, 2) == 0);
    REQUIRE(result.at(2, 1) == 0);
    REQUIRE(result.at(2, 2) == 1);

    REQUIRE(result.at(1, 3) == 1);
    REQUIRE(result.at(1, 4) == 2);
    REQUIRE(result.at(2, 3) == 3);
    REQUIRE(result.at(2, 4) == 4);
}

TEST_CASE("concat_horizontal: should concat two non-square matrices, smaller on the left") {
    Matrix<int> first = Matrix<int>::eye(2);
    Matrix<int> second = Matrix<int>::natural(2, 3);
    Matrix<int> result = first.concat_horizontal(second);

    REQUIRE(result.at(1, 1) == 1);
    REQUIRE(result.at(1, 2) == 0);
    REQUIRE(result.at(2, 1) == 0);
    REQUIRE(result.at(2, 2) == 1);

    REQUIRE(result.at(1, 3) == 1);
    REQUIRE(result.at(1, 4) == 2);
    REQUIRE(result.at(1, 5) == 3);
    REQUIRE(result.at(2, 3) == 4);
    REQUIRE(result.at(2, 4) == 5);
    REQUIRE(result.at(2, 5) == 6);
}

TEST_CASE("concat_horizontal: should concat two non-square matrices, smaller on the right") {
    Matrix<int> first = Matrix<int>::eye(2);
    Matrix<int> second = Matrix<int>::natural(2, 3);
    Matrix<int> result = second.concat_horizontal(first);

    REQUIRE(result.at(1, 1) == 1);
    REQUIRE(result.at(1, 2) == 2);
    REQUIRE(result.at(1, 3) == 3);
    REQUIRE(result.at(2, 1) == 4);
    REQUIRE(result.at(2, 2) == 5);
    REQUIRE(result.at(2, 3) == 6);

    REQUIRE(result.at(1, 4) == 1);
    REQUIRE(result.at(1, 5) == 0);
    REQUIRE(result.at(2, 4) == 0);
    REQUIRE(result.at(2, 5) == 1);
}




TEST_CASE("concat_vertical: should not concat matrices with nonmatching dimensions") {
    Matrix<int> first = Matrix<int>::natural(3, 3);
    Matrix<int> second = Matrix<int>::natural(3, 4);
    REQUIRE_THROWS(first.concat_vertical(second));
}

TEST_CASE("concat_vertical: should concat two 1-element matrices") {
    Matrix<int> first = Matrix<int>::eye(1);
    Matrix<int> second = Matrix<int>::zeros(1);
    Matrix<int> result = first.concat_vertical(second);

    REQUIRE(result.at(1, 1) == 1);
    REQUIRE(result.at(2, 1) == 0);
}

TEST_CASE("concat_vertical: should concat two square matrices") {
    Matrix<int> first = Matrix<int>::eye(2);
    Matrix<int> second = Matrix<int>::natural(2, 2);
    Matrix<int> result = first.concat_vertical(second);

    REQUIRE(result.at(1, 1) == 1);
    REQUIRE(result.at(1, 2) == 0);
    REQUIRE(result.at(2, 1) == 0);
    REQUIRE(result.at(2, 2) == 1);

    REQUIRE(result.at(3, 1) == 1);
    REQUIRE(result.at(3, 2) == 2);
    REQUIRE(result.at(4, 1) == 3);
    REQUIRE(result.at(4, 2) == 4);
}

TEST_CASE("concat_vertical: should concat two non-square matrices, smaller on the top") {
    Matrix<int> first = Matrix<int>::eye(2);
    Matrix<int> second = Matrix<int>::natural(3, 2);
    Matrix<int> result = first.concat_vertical(second);

    REQUIRE(result.at(1, 1) == 1);
    REQUIRE(result.at(1, 2) == 0);
    REQUIRE(result.at(2, 1) == 0);
    REQUIRE(result.at(2, 2) == 1);

    REQUIRE(result.at(3, 1) == 1);
    REQUIRE(result.at(3, 2) == 2);
    REQUIRE(result.at(4, 1) == 3);
    REQUIRE(result.at(4, 2) == 4);
    REQUIRE(result.at(5, 1) == 5);
    REQUIRE(result.at(5, 2) == 6);
}

TEST_CASE("concat_vertical: should concat two non-square matrices, smaller on the bottom") {
    Matrix<int> first = Matrix<int>::eye(2);
    Matrix<int> second = Matrix<int>::natural(3, 2);
    Matrix<int> result = second.concat_vertical(first);

    REQUIRE(result.at(1, 1) == 1);
    REQUIRE(result.at(1, 2) == 2);
    REQUIRE(result.at(2, 1) == 3);
    REQUIRE(result.at(2, 2) == 4);
    REQUIRE(result.at(3, 1) == 5);
    REQUIRE(result.at(3, 2) == 6);

    REQUIRE(result.at(4, 1) == 1);
    REQUIRE(result.at(4, 2) == 0);
    REQUIRE(result.at(5, 1) == 0);
    REQUIRE(result.at(5, 2) == 1);
}
