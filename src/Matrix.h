#ifndef _MATRIX_H
#define _MATRIX_H

#include <stdexcept>
#include <cstring>
#include <sstream>
#include <iomanip>

template<class T>
class Matrix {
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

public:

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

    int rows() const {
        return parent != nullptr ? (to_row - from_row + 1) : _rows;
    }

    int cols() const {
        return parent != nullptr ? (to_col - from_col + 1) : _cols;
    }

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

    Matrix<T> view(int from_row, int from_col, int to_row, int to_col) {
        bool min_check = from_row >= 1 && to_row >= 1 && from_col >= 1 && to_col >= 1;
        bool max_check = from_row <= rows() && to_row <= rows() && from_col <= cols() && to_col <= cols();
        bool overlap_check = from_row <= to_row && from_col <= to_col;
        if (!(min_check && max_check && overlap_check)) {
            throw new std::runtime_error("Invalid view indices");
        }

        return Matrix(*this, from_row, from_col, to_row, to_col);
    }

    static Matrix<T> zeros(int rows, int cols) {
        if (!(rows > 0 && cols > 0)) {
            throw std::runtime_error("Cannot create matrix with nonpositive dimensions");
        }
        return Matrix<T>(rows, cols);
    }

    static Matrix<T> zeros(int size) {
        return zeros(size, size);
    }

    static Matrix<int> eye(int size) {
        Matrix<T> identity = zeros(size);
        for (int i = 1; i <= size; ++i) {
            identity.at(i, i) = 1;
        }
        return identity;
    }

    // primarily for testing, but useful anyway
    static Matrix<int> natural(int rows, int cols) {
        Matrix<T> nat = zeros(rows, cols);

        for (int i = 1; i <= nat.rows(); ++i) {
            for (int j = 1; j <= nat.cols(); ++j) {
                nat.at(i, j) = j + (i - 1) * nat.cols();
            }
        }
        return nat;
    }

    Matrix<T> clone() {
        Matrix<T> cloned = zeros(rows(), cols());
        for (int i = 1; i <= rows(); ++i) {
            for (int j = 1; j <= cols(); ++j) {
                cloned.at(i, j) = at(i, j);
            }
        }
        return cloned;
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

    Matrix<T> operator+(const Matrix& other) const {
        Matrix<int> result = *this;
        result += other;
        return result;
    }

    Matrix<T> operator*(T factor) const {
        Matrix<int> result = *this;
        result *= factor;
        return result;
    }

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

    Matrix<T>& operator*=(T factor) {
        for (int i = 1; i <= rows(); ++i) {
            for (int j = 1; j <= cols(); ++j) {
                at(i, j) *= factor;
            }
        }
        return *this;
    }

    Matrix<T> operator-(const Matrix& other) const {
        Matrix<T> result = *this;
        result += other * -1;
        return result;
    }

    Matrix<T>& operator-=(const Matrix& other) {
        *this += other * (-1);
        return *this;
    }

    class matrix_iterator {
    public:

        matrix_iterator(const Matrix& mat) : subject(mat), cur_row(1), cur_col(1) {}

        matrix_iterator(const matrix_iterator& other) : subject(other.subject), cur_row(other.cur_row),
                                                        cur_col(other.cur_col) {}

        matrix_iterator operator++() { // ++x
            if (cur_row == subject.rows() && cur_col == subject.cols()) {
                return *this;
            }

            if (cur_col == subject.cols()) {
                cur_row++;
                cur_col = 1;
            } else {
                cur_col++;
            }
            return *this;
        }

        T& operator*() { return subject.at(cur_row, cur_col); }

    private:
        const Matrix& subject;
        int cur_row, cur_col;
    };

    matrix_iterator begin() {
        return matrix_iterator(*this);
    }
};

#endif
