
/*
 * Adnan Rahin
 * Safe Matrix
 * CSCI381 - Advanced C++
 * Prof. Waxman.
 *
 */
#include <iostream>
#include <cassert>

using namespace std;

template<class T>
class Matrix {
private:
    int rows;
    int cols;
    T **Mat;

public:
    Matrix(const int &rows, const int &cols);

    Matrix(const Matrix &other);

    ~Matrix();

    int *&operator[](const int &index) const;

    Matrix<T> &operator=(const Matrix<T> &matrix);

    Matrix<T> operator*(const Matrix<T> &matrix) const;

    Matrix<T> operator+(const Matrix<T> &matrix) const;

    int getMatrixRows(const Matrix<T> &matrix) { return matrix.rows; }

    int getMatrixCols(const Matrix<T> &matrix) { return matrix.cols; }

    friend ostream &operator<<(ostream &os, const Matrix<T> &m) {
        for (int i = 0; i < m.rows; ++i) {
            for (int j = 0; j < m.cols; ++j) {
                os << m.Mat[i][j] << "  ";
            }
            os << '\n';
        }
        return os;
    }

};

template<class T>
Matrix<T>::Matrix(const int &n_rows, const int &n_cols) {
    rows = n_rows;
    cols = n_cols;
    Mat = new int *[cols];
    assert(Mat);
    for (int i = 0; i < rows; i++) {
        Mat[i] = new int[cols];
        assert(Mat[i]);
    }
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            Mat[i][j] = 0;
        }
    }
}

template<class T>
Matrix<T>::Matrix(const Matrix<T> &matrix) {
    cols = matrix.cols;
    rows = matrix.rows;
    Mat = new int *[matrix.rows];
    assert(Mat);
    for (int i = 0; i < matrix.rows; i++) {
        Mat[i] = new int[matrix.cols];
        assert(Mat[i]);
    }
    for (int i = 0; i < matrix.rows; i++) {
        for (int j = 0; j < matrix.cols; j++) {
            Mat[i][j] = matrix[i][j];
        }
    }
}

template<typename T>
int *&Matrix<T>::operator[](const int &index) const {
    return Mat[index];
}

template<typename T>
Matrix<T> &Matrix<T>::operator=(const Matrix<T> &matrix) {
    if (Mat != matrix.Mat && cols == matrix.cols && rows == matrix.rows) {
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                Mat[i][j] = matrix.Mat[i][j];
            }
        }
    }
}

template<typename T>
Matrix<T> Matrix<T>::operator+(const Matrix<T> &matrix) const {
    if (rows != matrix.rows || cols != matrix.cols) {
        throw logic_error("First Matrix Row and Second Matrix Column is Not Equal");
    }

    Matrix<T> temp(rows, cols);

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            temp.Mat[i][j] = Mat[i][j] + matrix.Mat[i][j];
        }
    }

    return temp;
}

template<typename T>
Matrix<T> Matrix<T>::operator*(const Matrix<T> &matrix) const {
    if (cols != matrix.rows) {
        throw logic_error("First Matrix Row and Second Matrix Column is Not Equal");
    } else {
        Matrix<T> temp(rows, matrix.cols);
        for (int i = 0; i < rows; i++)
            for (int j = 0; j < matrix.cols; j++) {
                temp[i][j] = 0;
                for (int k = 0; k < matrix.rows; k++) {
                    temp.Mat[i][j] = temp.Mat[i][j] + (Mat[i][k] * matrix.Mat[k][j]);
                }
            }

        return temp;
    }

}

template<typename T>
Matrix<T>::~Matrix() {
    for (int i = 0; i < rows; i++)
        delete[] Mat[i];
    delete[] Mat;
}

int main() {
    Matrix<int> a(3, 3);
    Matrix<int> b(3, 3);


    a[0][0] = 1;
    a[0][1] = 2;
    a[0][2] = 3;
    a[1][0] = 4;
    a[1][1] = 5;
    a[1][2] = 6;
    a[2][0] = 7;
    a[2][1] = 8;
    a[2][2] = 9;
    cout << "Matrix A: \n" << a << endl;

    b[0][0] = 2;
    b[0][1] = 5;
    b[0][2] = 4;
    b[1][0] = 3;
    b[1][1] = 2;
    b[1][2] = 2;
    b[2][0] = 1;
    b[2][1] = 2;
    b[2][2] = 3;
    cout << "Matrix B: \n" << b << endl;
    Matrix<int> ans = a * b;
    cout << "A X B = \n" << ans << endl;

    Matrix<int> c(2, 3);
    Matrix<int> d(3, 2);

    c[0][0] = 1;
    c[0][1] = 2;
    c[0][2] = 3;
    c[1][0] = 4;
    c[1][1] = 5;
    c[1][2] = 5;


    d[0][0] = 2;
    d[0][1] = 5;
    d[1][0] = 4;
    d[1][1] = 3;
    d[2][0] = 2;
    d[2][1] = 2;

    cout << "Matrix C: \n" << c << endl;

    cout << "Matrix D: \n" << d << endl;
    Matrix<int> ans2 = c * d;
    cout << "C X D = \n" << ans2 << endl;


    Matrix<int> e(1, 3);
    Matrix<int> f(3, 1);

    e[0][0] = 1;
    e[0][1] = 2;
    e[0][2] = 3;


    f[0][0] = 1;
    f[1][0] = 2;
    f[2][0] = 3;

    cout << "Matrix E: \n" << e << endl;

    cout << "Matrix F: \n" << f << endl;
    Matrix<int> ans3 = e * f;
    cout << "C X D = \n" << ans3 << endl;


    return 0;
}