#include<iostream>
#include <cmath>
#include <iomanip>

using namespace std;

double **create_matrix(int n) {
    double **matrix;
    matrix = new double *[n];
    for (int i = 0; i < n; i++)
        matrix[i] = new double[n];
    return matrix;
}

double** matrix_A(int n) {
    double** A = create_matrix(n);
    A[0][0] = 1.0; A[0][1] = -20.0; A[0][2] = 30.0; A[0][3] = -4.0;
    A[1][0] = 2.0; A[1][1] = -40.0; A[1][2] = -6.0; A[1][3] = 50.0;
    A[2][0] = 9.0; A[2][1] = -180.0; A[2][2] = 11.0; A[2][3] = -12.0;
    A[3][0] = -16.0; A[3][1] = 15.0; A[3][2] = -140.0; A[3][3] = 13.0;
    return A;
}

void delete_matrix(double **matrix, int n) {
    for (int i = 0; i < n; i++)
        delete[]matrix[i];
    delete[]matrix;
}

void print_vector(double *b, int n, int *index) {
    for (int i = 0; i < n; i++)
        cout << b[index[i]] << endl;
}

void print_matrix(double **matrix, int n, int *index) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++)
            cout << setw(8) << matrix[index[i]][j] << "\t";
        cout << endl;
    }
}

int choose_pivot(double **matrix, int c, int n, int *index) {
    int row, i;
    for(i = c; i < n; i++) {
        if(fabs(matrix[index[i]][c]) < fabs(matrix[index[i + 1]][c])) {
            row = index[i + 1];
        }
        else {
            row = index[i];
        }
    }
    return row;
}

void gauss_method(double **matrix, int *index, int n) {
    int row, i, j, k;
    double reset;
    for(i = 0; i < n-1; i++) {
        if (matrix[index[i]][i] == 0.0) {
            row = choose_pivot(matrix, index[i], n-1, index);
            index[row] = index[i];
            index[i] = row;
        }
        for(j = i + 1; j < n; j++) {
            reset = matrix[index[j]][i]; // element zerowany poniżej diagonalii
            for(k = i + 1; k < n; k++)
                matrix[index[j]][k] = matrix[index[j]][k] - matrix[index[i]][k] * (reset / matrix[index[i]][i]); // wyliczanie wartości macierzy U
            matrix[index[j]][i] = reset / matrix[index[i]][i];
        }
    }
}

void calculate_y(double **L, double *b, int *index, int n) {// Ly = b:
    double sum = 0.0;
    int i,j;
    for(i = 0; i <= n; i++) {
        for(j = 0; j < i; j++)
            sum = sum + L[index[i]][j] * b[index[j]];
        b[index[i]] = (b[index[i]] - sum) / 1.0; //dzielę przez 1, bo macierz L ma jedynki na przekątnej
        sum = 0.0;
    }
}

void calculate_x(double **U, double *b, int *index, int n) {// Ux = y:
    double sum = 0.0;
    int i,j;
    for(i = n; i >= 0; i--) {
        for(j = i + 1; j <= n; j++)
            sum = sum + U[index[i]][j] * b[index[j]];
        b[index[i]] = (b[index[i]] - sum) / U[index[i]][i];
        sum = 0.0;
    }
}

int main() {
    int n = 4;
    double** A = matrix_A(n);
    int index[4] = { 0, 1, 2, 3 };
    double b[4] = { 35.0, 104.0, -366.0, -354.0 };

    cout << "Macierz A:\n";
    print_matrix(A, n, index);
    cout << "\n\nWektor b:\n";
    print_vector(b, n, index);

    gauss_method(A, index, n);
    cout << "\nMacierz A po dekompozycji LU:\n";
    print_matrix(A, n, index);

    calculate_y(A, b, index, n - 1);
    cout << "\nrozwiazanie Ly = b\nwektor y:\n";
    print_vector(b, n, index);

    calculate_x(A, b, index, n - 1);
    cout << "\nrozwiazanie Ux = y\nwektor x\n";
    print_vector(b, n, index);

    delete_matrix(A, n);

    return 0;
}