#include <iostream>
#include <cmath>


template <typename T, size_t M, size_t N>
class Matrix {
    T** _matrix;

    void _create_matrix() {
        _matrix = new T*[M];
        for(size_t i = 0; i < M; i++) {
            _matrix[i] = new T[N]();
        }
    }

    void _delete_matrix() {
        for(size_t i = 0; i < M; i++) {
            delete[] _matrix[i];
        }
        delete[] _matrix;
    }

    void _copy_matrix_from(T** matrix) {
        for(size_t i = 0; i < M; i++) {
            for(size_t j = 0; j < N; j++) {
                _matrix[i][j] = matrix[i][j];
            }
        }
    }

public:
    Matrix() {
        _create_matrix();
    }

    ~Matrix() {
        _delete_matrix();
    }

    Matrix(const Matrix& other) : Matrix() {
        _copy_matrix_from(other._matrix);
    }

    Matrix& operator=(const Matrix& other) {
        if (this == &other) {
            return *this;
        }

        _copy_matrix_from(other._matrix);

        return *this;
    }

    T& operator()(size_t i, size_t j){
        return _matrix[i][j];
    }

    void operator++(int){
        for(size_t i = 0; i < M; i++){
            for(size_t j = 0; j < N; j++) {
                _matrix[i][j]++;
            }
        }
    }

    Matrix& operator+=(const Matrix& other) {
        for(size_t i = 0; i < M; i++){
            for(size_t j = 0; j < N; j++) {
                _matrix[i][j] += other._matrix[i][j];
            }
        }

        return *this;
    }

    Matrix operator*=(T number) {
        for(size_t i = 0; i < M; i++){
            for(size_t j = 0; j < N; j++) {
                _matrix[i][j] *= number;
            }
        }

        return *this;
    };

    template <size_t H>
    Matrix<T, M, H> operator*(Matrix<T, N, H>& other) {
        Matrix<T, M, H> new_matrix;

        for(size_t k = 0; k < H; k++) {
            for(size_t i = 0; i < M; i++) {
                T item{};
                for(size_t j = 0; j < N; j++) {
                    item += _matrix[i][j] * other(j, k);
                }
                new_matrix(i, k) = item;
            }
        }

        return new_matrix;
    }

    Matrix operator+(const Matrix& other) {
        Matrix copy(*this);
        copy += other;

        return copy;
    }

    int64_t det() {
        if (M != N){
            std::cerr << "The matrix is not square" << std::endl;
            exit(1);
        }
        if (M > 3){
            std::cerr << "The method is not implemented for matrices of this size" << std::endl;
            exit(1);
        }

        if (M == 1) {
            return _matrix[0][0];
        }
        else if (M == 2) {
            return (
                (_matrix[0][0] * _matrix[1][1])
                - (_matrix[0][1] * _matrix[1][0])
            );
        }
        else {
            return (
                  (_matrix[0][0] * _matrix[1][1] * _matrix[2][2])
                - (_matrix[0][0] * _matrix[1][2] * _matrix[2][1])
                - (_matrix[0][1] * _matrix[1][0] * _matrix[2][2])
                + (_matrix[0][1] * _matrix[1][2] * _matrix[2][0])
                + (_matrix[0][2] * _matrix[1][0] * _matrix[2][1])
                - (_matrix[0][2] * _matrix[1][1] * _matrix[2][0])
            );
        }
    }

    void randomize() {
        for (size_t i = 0; i < M; i++) {
            for (size_t j = 0; j < N; j++) {
                _matrix[i][j] = (rand() % 9) + 1;
            }
        }
    }
};

template <typename T, size_t M, size_t N>
std::ostream& operator<<(std::ostream& out, Matrix<T, M, N>& matrix) {
    for(size_t i = 0; i < M; i++) {
        for(size_t j = 0; j < N; j++) {
            out << matrix(i, j) << " ";
        }

        if (i != M-1) out << std::endl;
    }
    return out;
}


template <typename T, size_t M, size_t N>
std::istream& operator>>(std::istream& in, Matrix<T, M, N>& matrix) {
    for(size_t i = 0; i < M; i++){
        for(size_t j = 0; j < N; j++) {
            std::cin >> matrix(i, j);
        }
    }
    return in;
}


int main() {
    Matrix<int, 2, 3> matrix1{};
    matrix1.randomize();

    Matrix<int, 3, 3> matrix2{};
    matrix2.randomize();

    std::cout << matrix1 << std::endl;
    std::cout << std::endl;
    std::cout << matrix2 << std::endl;
    std::cout << std::endl;
    std::cout << matrix2 << std::endl;
    std::cout << std::endl;


    std::cout << "Multiply (*)" << std::endl;
    Matrix<int, 2, 3> matrix3 = matrix1 * matrix2;
    std::cout << matrix3 << std::endl;
    std::cout << std::endl;

    std::cout << "Det" << std::endl;
    std::cout << matrix2.det() << std::endl;
    std::cout << std::endl;

    std::cout << "Operators" << std::endl;
    matrix1 += matrix3;
    std::cout << matrix1 << std::endl;
    std::cout << std::endl;
    matrix1++;
    std::cout << matrix1 << std::endl;
    std::cout << std::endl;
    matrix1 *= 2;
    std::cout << matrix1 << std::endl;
    std::cout << std::endl;

    std::cout << "Get and write" << std::endl;
    matrix1(0, 0) = 0;
    std::cout << matrix1(0, 0) << " " << matrix1(1, 0) << std::endl;

    return 0;
}
