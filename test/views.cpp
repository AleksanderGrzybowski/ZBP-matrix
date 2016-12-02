#include "catch.hpp"

#include "../src/Matrix.h"

Matrix<int> make1to9() {
    Matrix<int> matrix = Matrix<int>::zeros(3);
    matrix.at(1, 1) = 1;
    matrix.at(1, 2) = 2;
    matrix.at(1, 3) = 3;
    matrix.at(2, 1) = 4;
    matrix.at(2, 2) = 5;
    matrix.at(2, 3) = 6;
    matrix.at(3, 1) = 7;
    matrix.at(3, 2) = 8;
    matrix.at(3, 3) = 9;
    return matrix;
}

Matrix<int> make1to4() {
    Matrix<int> matrix = Matrix<int>::zeros(2);
    matrix.at(1, 1) = 1;
    matrix.at(1, 2) = 2;
    matrix.at(2, 1) = 3;
    matrix.at(2, 2) = 4;
    return matrix;
}

TEST_CASE("Should make a simple view") {
    Matrix<int> matrix = make1to9();
    Matrix<int> view = matrix.view(1, 1, 2, 2);

    REQUIRE(view.rows() == 2);
    REQUIRE(view.cols() == 2);
    REQUIRE(view.at(1, 1) == 1);
    REQUIRE(view.at(1, 2) == 2);
    REQUIRE(view.at(2, 1) == 4);
    REQUIRE(view.at(2, 2) == 5);
}

TEST_CASE("Should make a nested view") {
    Matrix<int> matrix = make1to9();
    Matrix<int> view = matrix.view(2, 1, 3, 3);
    Matrix<int> nested_view = view.view(1, 2, 2, 3);
    // nested_view = [ 5 6
    //                 8 9 ]

    REQUIRE(nested_view.rows() == 2);
    REQUIRE(nested_view.cols() == 2);
    REQUIRE(nested_view.at(1, 1) == 5);
    REQUIRE(nested_view.at(1, 2) == 6);
    REQUIRE(nested_view.at(2, 1) == 8);
    REQUIRE(nested_view.at(2, 2) == 9);
}

TEST_CASE("Should not create view if out of the bounds") {
    Matrix<int> matrix = make1to9();

    REQUIRE_THROWS(matrix.view(-1, -1, -1, -1));
    REQUIRE_THROWS(matrix.view(0, 0, 0, 0));
    REQUIRE_THROWS(matrix.view(1, 1, 4, 4));
    REQUIRE_THROWS(matrix.view(1, 5, 2, 2));
    REQUIRE_THROWS(matrix.view(2, 2, 1, 1));
}

TEST_CASE("Changing view should change parent") {
    Matrix<int> matrix = make1to9();
    Matrix<int> view = matrix.view(2, 2, 3, 3);

    view.at(1, 1) = 42;
    REQUIRE(matrix.at(2, 2) == 42);
}

TEST_CASE("Changing nested view should change parent") {
    Matrix<int> matrix = make1to9();
    Matrix<int> view = matrix.view(2, 1, 3, 3);
    Matrix<int> nested_view = view.view(1, 2, 2, 3);
    // nested_view = [ 5 6
    //                 8 9 ]

    nested_view.at(1, 1) = 42;
    REQUIRE(matrix.at(2, 2) == 42);
}

TEST_CASE("Cloned view should be a regular data matrix") {
    Matrix<int> matrix = make1to9();
    Matrix<int> view = matrix.view(2, 1, 3, 3);
    Matrix<int> cloned_view = view.clone();

    cloned_view.at(1, 1) = 42;
    REQUIRE(matrix.at(2, 2) == 5);
}

TEST_CASE("Views should respect out-of-bounds errors") {
    Matrix<int> matrix = make1to9();
    Matrix<int> view = matrix.view(2, 2, 3, 3);

    REQUIRE_THROWS(view.at(-1, -1));
    REQUIRE_THROWS(view.at(0, 0));
    REQUIRE_THROWS(view.at(0, 1));
    REQUIRE_THROWS(view.at(1, 0));
    REQUIRE_THROWS(view.at(2, 3));
    REQUIRE_THROWS(view.at(3, 2));
    REQUIRE_THROWS(view.at(3, 3));
}

TEST_CASE("Copy constructor should preserve view-ish type, should not copy data") {
    Matrix<int> matrix = make1to9();
    Matrix<int> view = matrix.view(2, 2, 3, 3);
    Matrix<int> copied_view = view;

    copied_view.at(1, 1) = 42;

    REQUIRE(matrix.at(2, 2) == 42);
}

TEST_CASE("Adding data matrix to view, changes should propagate to parent") {
    Matrix<int> matrix = make1to9();
    Matrix<int> view = matrix.view(2, 2, 3, 3);
    Matrix<int> addend = make1to4();

    view += addend;

    REQUIRE(matrix.at(2, 2) == 6);
    REQUIRE(matrix.at(2, 3) == 8);
    REQUIRE(matrix.at(3, 2) == 11);
    REQUIRE(matrix.at(3, 3) == 13);
}

TEST_CASE("Adding view to data matrix") {
    Matrix<int> matrix = make1to9();
    Matrix<int> view = matrix.view(2, 2, 3, 3);
    Matrix<int> addend = make1to4();

    addend += view;

    REQUIRE(addend.at(1, 1) == 6);
    REQUIRE(addend.at(1, 2) == 8);
    REQUIRE(addend.at(2, 1) == 11);
    REQUIRE(addend.at(2, 2) == 13);
}
