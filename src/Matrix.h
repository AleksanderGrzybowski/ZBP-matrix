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

        matrix_iterator(const Matrix& mat, int cur_row, int cur_col) : subject(mat), cur_row(cur_row),
                                                                       cur_col(cur_col) {}

        matrix_iterator(const matrix_iterator& other) : subject(other.subject), cur_row(other.cur_row),
                                                        cur_col(other.cur_col) {}

        matrix_iterator operator++() { // ++x
            if (cur_row == subject.rows() + 1) { // exhausted
                throw new std::runtime_error("Cannot go past the end of iterator");
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
            return cur_row == other.cur_row && cur_col == other.cur_col && (&other.subject == &subject);
        }

        bool operator!=(const matrix_iterator& other) const {
            return !(other == *this);
        }

        T& operator*() { return subject.at(cur_row, cur_col); }

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

    void put(const Matrix& src, int row, int col) {
        bool size_check = row >= 1 && row <= rows() && col >= 1 && col <= cols();
        bool bounds_check = (row + src.rows() - 1 <= rows()) && (col + src.cols() - 1 <= cols());
        if (!(size_check && bounds_check)) {
            throw std::runtime_error("Invalid position to put matrix");
        }

        for (int i = 1; i <= src.rows(); ++i) {
            for (int j = 1; j <= src.cols(); ++j) {
                at(i + row - 1, j + col - 1) = src.at(i, j);
            }
        }
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


    T dot_product(const Matrix<T>& second) {
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
