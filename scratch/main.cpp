#pragma clang diagnostic push
#pragma ide diagnostic ignored "UnusedImportStatement"

#include <iostream>
#include "../src/Matrix.h"

using namespace std;

void header(const string& text) {
    unsigned long top_length = text.size() + 4;

    cout << endl << endl;
    for (int i = 0; i < top_length; ++i) {
        cout << "*";
    }
    cout << endl;

    cout << "* " << text << " *" << endl;

    for (int i = 0; i < top_length; ++i) {
        cout << "*";
    }
    cout << endl;
}

int main() {
    header("Creating matrices:");
    cout << "Zeros:" << endl;
    cout << Matrix<int>::zeros(2, 4).to_string() << endl;
    cout << "Identity:" << endl;
    cout << Matrix<int>::eye(4).to_string() << endl;

    Matrix<int> naturals = Matrix<int>::natural(3, 5);
    header("Iterating over whole matrix");
    cout << naturals.to_string() << endl;
    for (auto& element: naturals) {
        cout << element << " ";
    }
    cout << endl;

    header("Views");
    cout << "Base matrix:" << endl;
    Matrix<int> base = Matrix<int>::natural(3, 5);
    cout << base.to_string() << endl;
    cout << "Subview of it:" << endl;
    Matrix<int> view = base.view(2, 2, 3, 3);
    cout << view.to_string() << endl;
    cout << "Changing one element of view:" << endl;
    view.at(1, 1) = 9999;
    cout << view.to_string() << endl;
    cout << "Change propagated to base matrix:" << endl;
    cout << base.to_string() << endl;

    header("Operations");
    cout << "Matrix: A:" << endl;
    Matrix<int> a = Matrix<int>::natural(3, 3);
    cout << a.to_string() << endl;
    cout << "Matrix: B:" << endl;
    Matrix<int> b = Matrix<int>::natural(3, 3);
    b.at(1, 1) = 5;
    b.at(1, 2) = 8;
    b.at(1, 3) = 4;
    b.at(2, 1) = 0;
    b.at(2, 2) = 4;
    b.at(2, 3) = 2;
    b.at(3, 1) = 3;
    b.at(3, 2) = 8;
    b.at(3, 3) = 1;
    cout << b.to_string() << endl;
    cout << "Sum:" << endl;
    cout << (a + b).to_string() << endl;
    cout << "Difference:" << endl;
    cout << (a - b).to_string() << endl;
    cout << "Product:" << endl;
    cout << (a * b).to_string() << endl;

    header("Inserting matrices");
    cout << "Source matrix:" << endl;
    Matrix<int> src = Matrix<int>::natural(2, 3);
    cout << src.to_string() << endl;
    Matrix<int> dest = Matrix<int>::zeros(5, 5);
    cout << "Destination matrix:" << endl;
    cout << dest.to_string() << endl;
    cout << "After insertion:" << endl;
    dest.put(src, 2, 2);
    cout << dest.to_string() << endl;

    header("Determinant");
    cout << "Determinant of the following matrix:" << endl;
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
    cout << matrix.to_string() << endl;
    cout << "Is " << matrix.det() << endl;

    header("Concatenating matrices");
    Matrix<int> sample = Matrix<int>::natural(3, 3);
    cout << (sample.concat_horizontal(sample)).to_string() << endl;
    cout << (sample.concat_vertical(sample)).to_string() << endl;

    header("Transposing matrices");
    Matrix<int> x = Matrix<int>::natural(4, 4);
    cout << x.to_string() << endl;
    cout << x.transpose().to_string() << endl;

    header("Inverting matrices");
    Matrix<int> first = Matrix<int>::natural(2,2);
    cout << first.to_string() << endl;
    cout << first.inverse().to_string() << endl;
}

#pragma clang diagnostic pop