#ifndef _MATRIX_H
#define _MATRIX_H

#include <stdexcept>
#include <cstring>
#include <sstream>
#include <iomanip>
#include <iostream>

template<class T>
class Matrix {
public:

    /**
     * Returns number of rows (view-aware)
     */
    int rows() const {
        return parent != nullptr ? (to_row - from_row + 1) : _rows;
    }

    /**
     * Returns number of columns (view-aware)
     */
    int cols() const {
        return parent != nullptr ? (to_col - from_col + 1) : _cols;
    }

    /**
     * Gets element at the specific coordinates (view-aware).
     */
    T& at(int row, int col) const {
        if (row <= 0 || col <= 0) {
            throw std::runtime_error("Invalid element access");
        }

        if (parent != nullptr) {
            return parent->at(row + from_row - 1, col + from_col - 1);
        } else {
            if (row > _rows || col > _cols) {
                throw std::runtime_error("Invalid element access");
            }
            return _data[(row - 1) * _cols + (col - 1)];
        }
    }

    /**
     * Creates MxN matrix filled with zeros.
     */
    static Matrix<T> zeros(int rows, int cols) {
        if (!(rows > 0 && cols > 0)) {
            throw std::runtime_error("Cannot create matrix with nonpositive dimensions");
        }

        return Matrix<T>(rows, cols);
    }

    /**
     * Creates MxM matrix filled with zeros.
     */
    static Matrix<T> zeros(int size) {
        return zeros(size, size);
    }

    /**
     * Creates MxM identity matrix (1-s on diagonal and 0-s elsewhere)
     */
    static Matrix<int> eye(int size) {
        Matrix<T> identity = zeros(size);
        for (int i = 1; i <= size; ++i) {
            identity.at(i, i) = 1;
        }
        return identity;
    }

    /**
     * Creates MxN matrix filled with natural numbers increasing.
     * Used mainly for testing and visualisation.
     */
    static Matrix<int> natural(int rows, int cols) {
        Matrix<T> nat = zeros(rows, cols);

        for (int i = 1; i <= nat.rows(); ++i) {
            for (int j = 1; j <= nat.cols(); ++j) {
                nat.at(i, j) = j + (i - 1) * nat.cols();
            }
        }
        return nat;
    }

    /**
     * Clones matrix and copies all internal data structures to a new matrix.
     */
    Matrix<T> clone() const {
        Matrix<T> cloned = zeros(rows(), cols());
        for (int i = 1; i <= rows(); ++i) {
            for (int j = 1; j <= cols(); ++j) {
                cloned.at(i, j) = at(i, j);
            }
        }
        return cloned;
    }

    /**
     * Returns transposed matrix, that is, matrix with every element (i,j) moved to (j,i).
     */
    Matrix<T> transpose() const {
        Matrix<T> transposed = zeros(cols(), rows());
        for (int i = 1; i <= rows(); ++i) {
            for (int j = 1; j <= cols(); ++j) {
                transposed.at(j, i) = at(i, j);
            }
        }

        return transposed;
    }

    /**
     * Returns a view (sub-matrix) of specified coordinates. Any mutations made to the view
     * will propagate down to base matrix with all necessary reindexing and bound checking.
     * Destructing view will not do any harm to base matrix.
     * If unsure, clone the result to avoid confusion.
     */
    Matrix<T> view(int from_row, int from_col, int to_row, int to_col) {
        bool min_check = from_row >= 1 && to_row >= 1 && from_col >= 1 && to_col >= 1;
        bool max_check = from_row <= rows() && to_row <= rows() && from_col <= cols() && to_col <= cols();
        bool overlap_check = from_row <= to_row && from_col <= to_col;
        if (!(min_check && max_check && overlap_check)) {
            throw std::runtime_error("Invalid view indices");
        }

        return Matrix(*this, from_row, from_col, to_row, to_col);
    }

    /**
     * Pastes the content of source matrix into destination matrix at the provided coordinates, replacing
     * existing elements.
     */
    void put(const Matrix& source, int row, int col) {
        bool size_check = row >= 1 && row <= rows() && col >= 1 && col <= cols();
        bool bounds_check = (row + source.rows() - 1 <= rows()) && (col + source.cols() - 1 <= cols());
        if (!(size_check && bounds_check)) {
            throw std::runtime_error("Invalid position to put matrix");
        }

        for (int i = 1; i <= source.rows(); ++i) {
            for (int j = 1; j <= source.cols(); ++j) {
                at(i + row - 1, j + col - 1) = source.at(i, j);
            }
        }
    }

    /**
     * Joins two matrices together horizontally. Make sure that the number of rows is the same on both matrices.
     */
    Matrix concat_horizontal(const Matrix& right) {
        if (rows() != right.rows()) {
            throw std::runtime_error("Cannot concat matrices, nonmatching dimensions");
        }

        Matrix<T> result = zeros(rows(), cols() + right.cols());
        result.put(*this, 1, 1);
        result.put(right, 1, cols() + 1);

        return result;
    }

    /**
     * Joins two matrices together verically. Make sure that the number of cols is the same on both matrices.
     */
    Matrix concat_vertical(const Matrix& bottom) {
        if (cols() != bottom.cols()) {
            throw std::runtime_error("Cannot concat matrices, nonmatching dimensions");
        }

        Matrix<T> result = zeros(rows() + bottom.rows(), cols());
        result.put(*this, 1, 1);
        result.put(bottom, rows() + 1, 1);

        return result;
    }

    /**
     * Adds matrices (mutating).
     */
    Matrix<T>& operator+=(const Matrix& other) {
        if (!(other.rows() == rows() && other.cols() == cols())) {
            throw std::runtime_error("Incompatible dimensions");
        }

        for (int i = 1; i <= rows(); ++i) {
            for (int j = 1; j <= cols(); ++j) {
                at(i, j) += other.at(i, j);
            }
        }

        return *this;
    }

    /**
     * Adds matrices (non-mutating).
     */
    Matrix<T> operator+(const Matrix& other) const {
        Matrix<int> result = *this;
        result += other;
        return result;
    }

    /**
     * Multiplies matrices (mutating).
     */
    Matrix<T>& operator*=(T factor) {
        for (int i = 1; i <= rows(); ++i) {
            for (int j = 1; j <= cols(); ++j) {
                at(i, j) *= factor;
            }
        }

        return *this;
    }

    /**
     * Multiplies matrices by a factor (non-mutating).
     */
    Matrix<T> operator*(T factor) const {
        Matrix<int> result = *this;
        result *= factor;
        return result;
    }

    /**
     * Subtracts matrices (non-mutating).
     */
    Matrix<T> operator-(const Matrix& other) const {
        return (*this + (other * (-1)));
    }

    /**
     * Subtracts matrices (mutating).
     */
    Matrix<T>& operator-=(const Matrix& other) {
        *this += other * (-1);
        return *this;
    }

    // this method returns a new matrix with with some row and col removed
    // should be in fact private, because this is just an implementation detail of det(),
    // but complex enough to require testing
    /**
     * Removes the specified row and column from the matrix. All existing elements will be shifted
     * to accomodate new empty space. This method is an implementation detail of .det and .inverse
     */
    Matrix remove_intersection(int row, int col) const {
        if (!(row >= 1 && row <= rows() && col >= 1 && col <= cols())) {
            throw std::runtime_error("Nonexistent center element to remove intersection");
        }

        if (cols() == 1 || rows() == 1) {
            throw std::runtime_error("Cannot remove intersection from 1x1 matrix");
        }

        Matrix<T> result = Matrix<T>::zeros(cols() - 1, rows() - 1);
        for (int i = 1; i <= rows() - 1; ++i) {
            for (int j = 1; j <= cols() - 1; ++j) {
                result.at(i, j) = at(i >= row ? (i + 1) : i, j >= col ? (j + 1) : j);
            }
        }

        return result;
    }

    /**
     * Matrix multiplication (non-mutating).
     */
    Matrix<T> operator*(Matrix<T>& second) {
        if (cols() != second.rows()) {
            throw std::runtime_error("Cannot multiply, invalid dimensions");
        }

        Matrix<T> result = Matrix<T>::zeros(rows(), second.cols());

        for (int i = 1; i <= result.rows(); ++i) {
            for (int j = 1; j <= result.cols(); ++j) {
                result.at(i, j) = view(i, 1, i, cols()).dot_product(second.view(1, j, second.rows(), j));
            }
        }

        return result;
    }

    /**
     * Calculates matrix determinant.
     */
    T det() const {
        if (rows() != cols()) {
            throw std::runtime_error("Cannot calculate determinant of non-square matrix");
        }

        if (rows() == 1) {
            return at(1, 1);
        } else {
            T result = 0;
            for (int j = 1; j <= cols(); ++j) {
                result += ((j % 2 == 1) ? 1 : -1) * at(1, j) * remove_intersection(1, j).det();
            }
            return result;
        }
    }

    /**
     * Calculates matrix inverse, if exists.
     */
    Matrix<T> inverse() const {
        T thisDet = det();
        if (thisDet == 0) {
            throw std::runtime_error("Cannot invert non-rectangular matrix");
        }

        Matrix<T> inverted = zeros(rows(), cols());

        if (rows() == 1 && cols() == 1) {
            Matrix<T> result = zeros(1, 1);
            result.at(1, 1) = 1.0 / at(1, 1);
            return result;
        }

        for (int i = 1; i <= rows(); ++i) {
            for (int j = 1; j <= cols(); ++j) {
                inverted.at(i, j) = ((((i + j) % 2 == 0) ? 1 : -1) * (*this).remove_intersection(i, j).det()) / thisDet;
            }
        }

        return inverted.transpose();
    }

    /**
     * Solves a system of linear equations Ax=B.
     */
    static Matrix<T> solve(Matrix<T> a, Matrix<T> b) {
        return a.inverse() * b;
    }

    Matrix(Matrix&& rvalue) {
        _data = rvalue._data;
        _rows = rvalue._rows;
        _cols = rvalue._cols;
        parent = rvalue.parent;
        rvalue._data = nullptr;
    }

    Matrix(const Matrix<T>& other) {
        if (other.parent == nullptr) {
            parent = nullptr;
            _rows = other.rows();
            _cols = other.cols();
            _data = new T[_rows * _cols];
            for (int i = 1; i <= _rows; ++i) {
                for (int j = 1; j <= _cols; ++j) {
                    at(i, j) = other.at(i, j);
                }
            }
        } else {
            parent = other.parent;
            from_row = other.from_row;
            from_col = other.from_col;
            to_row = other.to_row;
            to_col = other.to_col;
        }
    }

    bool operator==(const Matrix& other) const {
        if (!(rows() == other.rows() && cols() == other.cols())) {
            return false;
        }

        for (int i = 1; i <= rows(); ++i) {
            for (int j = 1; j <= cols(); ++j) {
                if (at(i, j) != other.at(i, j)) {
                    return false;
                }
            }
        }

        return true;
    }

    bool operator!=(const Matrix& other) const {
        return !(*this == other);
    }

    std::string to_string() const {
        std::stringstream output;
        output << "[\n";
        for (int i = 1; i <= rows(); ++i) {
            for (int j = 1; j <= cols(); ++j) {
                output << std::setfill(' ') << std::setw(5) << at(i, j) << ", ";
            }
            output << "\n";
        }
        output << "]\n";

        return output.str();
    }

    class matrix_iterator {
    public:

        matrix_iterator(const Matrix& mat, int cur_row, int cur_col) : subject(mat), cur_row(cur_row),
                                                                       cur_col(cur_col) {}

        matrix_iterator(const matrix_iterator& other) : subject(other.subject), cur_row(other.cur_row),
                                                        cur_col(other.cur_col) {}

        matrix_iterator operator++() { // ++x
            if (cur_row == subject.rows() + 1) { // iterator exhausted
                throw std::runtime_error("Cannot go past the end of iterator");
            }

            if (cur_col == subject.cols()) {
                cur_row++;
                cur_col = 1;
            } else {
                cur_col++;
            }

            return *this;
        }

        bool operator==(const matrix_iterator& other) const {
            return cur_row == other.cur_row && cur_col == other.cur_col && &other.subject == &subject;
        }

        bool operator!=(const matrix_iterator& other) const {
            return !(other == *this);
        }

        T& operator*() const {
            return subject.at(cur_row, cur_col);
        }

    private:
        const Matrix& subject;
        int cur_row, cur_col;
    };

    matrix_iterator begin() const {
        return matrix_iterator(*this, 1, 1);
    }

    matrix_iterator end() const {
        return matrix_iterator(*this, rows() + 1, 1);
    }


private:

    // when not a view - real data structure with pointer to elements
    int _rows, _cols;
    T* _data;

    // when view
    Matrix<T>* parent;
    int from_row, from_col, to_row, to_col;

    Matrix(int rows, int cols) : _rows(rows), _cols(cols), parent(nullptr), _data(new T[rows * cols]()) {}

    Matrix(Matrix<T>& parent, int from_row, int from_col, int to_row, int to_col)
            : from_row(from_row), from_col(from_col), to_row(to_row), to_col(to_col), parent(&parent) {}


    /**
     * Calculates dot product of two vectors (1xM / Mx1).
     */
    T dot_product(const Matrix<T>& second) const {
        matrix_iterator it_first = begin();
        matrix_iterator it_second = second.begin();

        T result = 0;

        while (it_first != end()) {
            result += (*it_first) * (*it_second);
            ++it_first;
            ++it_second;
        }

        return result;
    }
};


#endif
