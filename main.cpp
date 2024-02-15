#include <iostream>
#include <cmath>


template <typename T, size_t N, size_t M>
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
        for(size_t i = 0; i < M; i++){
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

    Matrix<T, N, M>& operator=(const Matrix<T, N, M>& other) {
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

    Matrix<T, N, M>& operator+=(const Matrix<T, N, M>& other) {
        for(size_t i = 0; i < M; i++){
            for(size_t j = 0; j < N; j++) {
                _matrix[i][j] += other._matrix[i][j];
            }
        }

        return *this;
    }

    template <size_t H>
    Matrix<T, N, H> operator*=(const Matrix<T, M, H>& other) {
        Matrix<T, N, H> result{};

        for(size_t i = 0; i < M; i++){
            for(size_t j = 0; j < N; j++) {
                for(size_t k = 0; k < H; k++) {
                    _matrix[i][j] * other._matrix[i];
                }
            }
        }

        *this = result;  // WTF

        return *this;
    }

    Matrix<T, N, M> operator+(const Matrix<T, N, M>& other) {
        Matrix copy(*this);
        copy += other;

        return copy;
    }

    template <size_t H>
    Matrix<T, N, H> operator*(const Matrix<T, M, H>& other) {
        Matrix copy(*this);
        copy *= other;

        return copy;
    }

    long long det() {
        if (N != M){
            exit(1);
        }

        long long sum = 0;
        for(size_t j = 0; j < N; j++) {
            sum += (
                (long long)pw(j) * _matrix[0][j]
                * get_additional_minor<N-1>(0, j)
            );

        }
        return sum;
    }

    short pw(size_t x) {
        if (x%2 == 0) return 1;
        else return -1;
    }

    template<size_t K>
    size_t get_additional_minor(size_t delete_i, size_t delete_j) {
        Matrix<T, K, K> result{};

        size_t dynamic_i = 0;
        size_t dynamic_j = 0;
        for(size_t i = 0; i < N; i++){
            if (i == delete_i) continue;

            for(size_t j = 0; j < N; j++) {
                if (j == delete_j) continue;

                result(dynamic_i, dynamic_j) = _matrix[i][j];

                dynamic_j++;
            }
            dynamic_i++;
        }

        std::cout << result << std::endl;

        return result.det();
    }

    template<>
    size_t get_additional_minor<0>(size_t delete_i, size_t delete_j) {
        return _matrix[0][0];
    }

    void randomize() {
        for (size_t i = 0; i < N; ++i) {
            for (size_t j = 0; j < M; ++j) {
                _matrix[i][j] = (rand() % 9) + 1;
            }
        }
    }
};

template <typename T, size_t N, size_t M>
std::ostream& operator<<(std::ostream& out, Matrix<T, N, M>& matrix) {
    for(size_t i = 0; i < M; i++){
        for(size_t j = 0; j < N; j++) {
            out << matrix(i, j) << " ";
        }
        out << std::endl;
    }
    return out;
}


template <typename T, size_t N, size_t M>
std::istream& operator>>(std::istream& in, Matrix<T, N, M>& matrix) {
    for(size_t i = 0; i < M; i++){
        for(size_t j = 0; j < N; j++) {
            std::cin >> matrix(i, j);
        }
    }
    return in;
}


int main() {
    Matrix<int, 3, 3> matrix{};
    matrix.randomize();
    std::cout << matrix << std::endl;
    std::cout << matrix.det() << std::endl;
//    std::cin >> matrix;
//    matrix++;
//    std::cout << matrix;

    return 0;
}
