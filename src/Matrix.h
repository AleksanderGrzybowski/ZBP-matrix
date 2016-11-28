#ifndef _MATRIX_H
#define _MATRIX_H

#include <stdexcept>
#include <cstring>
#include <sstream>
#include <iomanip>

template<class T>
class Matrix {
public:
    virtual T& at(int row, int col) const = 0;

    virtual int rows() const = 0;

    virtual int cols() const = 0;

    virtual Matrix<T>* clone() = 0;

    virtual std::string to_string() const = 0;
};

template<class T>
class DataMatrix : public Matrix<T> {
private:

    int _rows, _cols;
    T* _data;

    DataMatrix(int rows, int cols) : _rows(rows), _cols(cols) {
        _data = new T[rows * cols];
        memset(_data, 0, sizeof(T) * (rows * cols)); // why this is required?
    }

public:

    DataMatrix(Matrix<T>& other) {
        _rows = other.rows();
        _cols = other.cols();
        _data = new T[_rows * _cols];
        for (int i = 1; i <= other.rows(); ++i) {
            for (int j = 1; j <= other.cols(); ++j) {
                at(i, j) = other.at(i, j);
            }
        }
    }

    int rows() const {
        return _rows;
    }

    static DataMatrix<T>* zeros(int rows, int cols) {
        if (!(rows > 0 && cols > 0)) {
            throw std::runtime_error("Cannot create matrix with nonpositive dimensions");
        }
        return new DataMatrix<T>(rows, cols);
    }

    static DataMatrix<T>* zeros(int size) {
        return zeros(size, size);
    }

    int cols() const {
        return _cols;
    }

    T& at(int row, int col) const {
        return _data[(row - 1) * _rows + (col - 1)];
    }

    static Matrix<int>* eye(int size) {
        Matrix<T>* m = zeros(size);
        for (int i = 1; i <= size; ++i) {
            m->at(i, i) = 1;
        }
        return m;
    }

    Matrix<T>* clone() {
        Matrix<T>* c = zeros(rows(), cols());
        for (int i = 1; i <= rows(); ++i) {
            for (int j = 1; j <= cols(); ++j) {
                c->at(i, j) = at(i, j);
            }
        }
        return c;
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
};

#endif
