#include <iostream>
#include <vector>
#include <stdexcept>
#include <initializer_list>

class Matrix {
private:
    std::vector<std::vector<double>> data;
    size_t rows, cols;

    //Determinant of a matrix
    double determinant(const std::vector<std::vector<double>>& mat) const {
        if (mat.size() == 1) return mat[0][0];
        if (mat.size() == 2) return mat[0][0] * mat[1][1] - mat[0][1] * mat[1][0];

        double det = 0;
        for (size_t p = 0; p < mat[0].size(); ++p) {
            std::vector<std::vector<double>> subMat(mat.size() - 1, std::vector<double>(mat[0].size() - 1));
            for (size_t i = 1; i < mat.size(); ++i) {
                size_t colIndex = 0;
                for (size_t j = 0; j < mat[i].size(); ++j) {
                    if (j == p) continue;
                    subMat[i - 1][colIndex] = mat[i][j];
                    ++colIndex;
                }
            }
            det += mat[0][p] * determinant(subMat) * (p % 2 == 0 ? 1 : -1);
        }
        return det;
    }

    //Cofactor matrix
    std::vector<std::vector<double>> cofactorMatrix() const {
        std::vector<std::vector<double>> cofactors(rows, std::vector<double>(cols));
        for (size_t i = 0; i < rows; ++i) {
            for (size_t j = 0; j < cols; ++j) {
                std::vector<std::vector<double>> subMat(rows - 1, std::vector<double>(cols - 1));
                for (size_t m = 0; m < rows; ++m) {
                    if (m == i) continue;
                    for (size_t n = 0; n < cols; ++n) {
                        if (n == j) continue;
                        subMat[m < i ? m : m - 1][n < j ? n : n - 1] = data[m][n];
                    }
                }
                cofactors[i][j] = determinant(subMat) * ((i + j) % 2 == 0 ? 1 : -1);
            }
        }
        return cofactors;
    }

public:
    Matrix(size_t r, size_t c) : rows(r), cols(c), data(r, std::vector<double>(c, 0)) {}
    
    Matrix(std::initializer_list<std::initializer_list<double>> initList) {
        rows = initList.size();
        cols = initList.begin()->size();
        data.resize(rows);
        size_t i = 0;
        for (const auto& row : initList) {
            data[i] = row;
            ++i;
        }
    }
    
    Matrix(const Matrix& other) : rows(other.rows), cols(other.cols), data(other.data) {}
    
    Matrix(Matrix&& other) noexcept : rows(other.rows), cols(other.cols), data(std::move(other.data)) {
        other.rows = 0;
        other.cols = 0;
    }
    
    Matrix& operator=(const Matrix& other) {
        if (this != &other) {
            rows = other.rows;
            cols = other.cols;
            data = other.data;
        }
        return *this;
    }
    
    Matrix& operator=(Matrix&& other) noexcept {
        if (this != &other) {
            rows = other.rows;
            cols = other.cols;
            data = std::move(other.data);
            other.rows = 0;
            other.cols = 0;
        }
        return *this;
    }

    //Addition
    Matrix operator+(const Matrix& other) const {
        if (rows != other.rows || cols != other.cols) {
            throw std::invalid_argument("Matrices must have the same dimensions for addition");
        }
        Matrix result(rows, cols);
        for (size_t i = 0; i < rows; ++i) {
            for (size_t j = 0; j < cols; ++j) {
                result.data[i][j] = data[i][j] + other.data[i][j];
            }
        }
        return result;
    }

    //Subtraction
    Matrix operator-(const Matrix& other) const {
        if (rows != other.rows || cols != other.cols) {
            throw std::invalid_argument("Matrices must have the same dimensions for subtraction");
        }
        Matrix result(rows, cols);
        for (size_t i = 0; i < rows; ++i) {
            for (size_t j = 0; j < cols; ++j) {
                result.data[i][j] = data[i][j] - other.data[i][j];
            }
        }
        return result;
    }

    //Multiplication
    Matrix operator*(const Matrix& other) const {
        if (cols != other.rows) {
            throw std::invalid_argument("Matrices cannot be multiplied");
        }
        Matrix result(rows, other.cols);
        for (size_t i = 0; i < rows; ++i) {
            for (size_t j = 0; j < other.cols; ++j) {
                for (size_t k = 0; k < cols; ++k) {
                    result.data[i][j] += data[i][k] * other.data[k][j];
                }
            }
        }
        return result;
    }

    //Transposition
    Matrix transpose() const {
        Matrix result(cols, rows);
        for (size_t i = 0; i < rows; ++i) {
            for (size_t j = 0; j < cols; ++j) {
                result.data[j][i] = data[i][j];
            }
        }
        return result;
    }

    //Determinant
    double determinant() const {
        if (rows != cols) {
            throw std::invalid_argument("Determinant can only be calculated for square matrices");
        }
        return determinant(data);
    }

    //Inversion
    Matrix inverse() const {
        double det = determinant();
        if (det == 0) {
            throw std::invalid_argument("Matrix is singular and cannot be inverted");
        }
        std::vector<std::vector<double>> cofactors = cofactorMatrix();
        Matrix adjugate(cols, rows);
        for (size_t i = 0; i < rows; ++i) {
            for (size_t j = 0; j < cols; ++j) {
                adjugate.data[j][i] = cofactors[i][j];
            }
        }
        return adjugate * (1.0 / det);
    }

    //Scalar multiplication
    Matrix operator*(double scalar) const {
        Matrix result(rows, cols);
        for (size_t i = 0; i < rows; ++i) {
            for (size_t j = 0; j < cols; ++j) {
                result.data[i][j] = data[i][j] * scalar;
            }
        }
        return result;
    }

    //Output
    friend std::ostream& operator<<(std::ostream& os, const Matrix& mat) {
        for (const auto& row : mat.data) {
            for (const auto& elem : row) {
                os << elem << " ";
            }
            os << "\n";
        }
        return os;
    }
};

int main() {
    Matrix matrix1{{1, 2}, {3, 4}};
    Matrix matrix2{{5, 6}, {7, 8}};

    std::cout << "Matrix 1:\n" << matrix1 << "\n";
    std::cout << "Matrix 2:\n" << matrix2 << "\n";
    std::cout << "Addition:\n" << matrix1 + matrix2 << "\n";
    std::cout << "Subtraction:\n" << matrix1 - matrix2 << "\n";
    std::cout << "Multiplication:\n" << matrix1 * matrix2 << "\n";
    std::cout << "Transpose:\n" << matrix1.transpose() << "\n";
    std::cout << "Determinant: " << matrix1.determinant() << "\n";
    std::cout << "Inverse:\n" << matrix1.inverse() << "\n";

    return 0;
}