#include <iostream>
#include <iomanip>

#define tolx 1e-12
#define tolf 1e-12
#define max_iter 30

void jacobi_method(double** A, double *b, double* x0, int n);
void gauss_seidel_method(double** A, double *b, double* x0, int n);
void sor_method(double** A, double *b, double* x0, int n);
double** create_matrix(int n);
void print_vector(double* vect, int n);
double max_elem(double *vect, int n);

int main() {
    int n = 4;
    double* x0 = new double[n];
    double* b = new double[n];
    double** A = create_matrix(n);

    A[0][0] = 100.0; A[0][1] = -1.0; A[0][2] = 2.0; A[0][3] = -3.0;
    A[1][0] = 1.0; A[1][1] = 200.0; A[1][2] = -4.0; A[1][3] = 5.0;
    A[2][0] = -2.0; A[2][1] = 4.0; A[2][2] = 300.0; A[2][3] = -6.0;
    A[3][0] = 3.0; A[3][1] = -5.0; A[3][2] = 6.0; A[3][3] = 400.0;

    b[0] = 116.0; b[1] = -226.0; b[2] = 912.0; b[3] = -1174.0;
    x0[0] = 2.0; x0[1] = 2.0; x0[2] = 2.0; x0[3] = 2.0;

    std::cout<< std::setprecision(12)<< std::fixed;

    jacobi_method(A ,b, x0, n);
    //gauss_seidel_method(A ,b, x0, n);
    //sor_method(A ,b, x0, n);

    return 0;
}

void jacobi_method(double** A, double *b, double* x, int n) {
    int i = 0;
    double suma, rez, est;
    double *estymator = new double[n];
    double *reziduum = new double[n];
    double *przyblizenie = new double[n];
    std::cout << "Metoda Jacobiego:\n\n";
    std::cout << "iteracja\tx1\t\tx2\t\tx3\t\tx4\t\testymator\treziduum\n";

    while(true) {
        std::cout << i << "\t\t";
        for(int j = 0; j < n; j++) {
            suma = 0.0;
            for(int k = 0; k < n; k++)
                if(j != k)
                    suma += x[k] * A[j][k];
            // xn = -D^1 * (L + U) * xn-1 + D^-1 * b//
            // xn = (b - (L + U)* xn-1)/D^1
            przyblizenie[j] = (b[j] - suma)/A[j][j];
            printf("%.6e\t", przyblizenie[j]);
        }

        for(int j = 0; j < n; j++) {
            reziduum[j] = 0.0;
            for(int k = 0; k < n; k++) {
                reziduum[j] += A[j][k] * x[k];
            }
            reziduum[j] = fabs(reziduum[j] - b[j]);
            estymator[j] = fabs(przyblizenie[j] - x[j]);
            x[j] = przyblizenie[j];
        }

        est = max_elem(estymator, n);
        rez = max_elem(reziduum, n);

        printf("%.6e\t%.6e\t\n", est, rez);

        if((rez <= tolf && est <= tolx) || i >= max_iter) {
            delete[] reziduum;
            delete[] przyblizenie;
            delete[] estymator;
            return;
        }
        i++;
    }
}

void gauss_seidel_method(double** A, double *b, double* x, int n) {
    int i = 0;
    double suma, rez, est;
    double *estymator = new double[n];
    double *reziduum = new double[n];
    double *przyblizenie = new double[n];
    std::cout << "Metoda Gaussa-Seidela:\n\n";
    std::cout << "iteracja\tx1\t\tx2\t\tx3\t\tx4\t\testymator\treziduum\n";

    while(true) {
        std::cout << i << "\t\t";
        for(int j = 0; j < n; j++) {
            suma = 0.0;
            for (int k = 0; k < n; k++)
                if(j != k) {
                    suma += x[k] * A[j][k];
                }
            przyblizenie[j] = x[j];
            x[j] = (b[j] - suma) / A[j][j];
            printf("%.6e\t", przyblizenie[j]);
        }

        for(int j = 0; j < n; j++) {
            reziduum[j] = 0.0;
            for(int k = 0; k < n; k++) {
                reziduum[j] += A[j][k] * x[k];
            }
            reziduum[j] = fabs(reziduum[j] - b[j]);
            estymator[j] = fabs(przyblizenie[j] - x[j]);
        }

        est = max_elem(estymator, n);
        rez = max_elem(reziduum, n);

        printf("%.6e\t%.6e\t\n", est, rez);

        if(rez <= tolf && est <= tolx || i >= max_iter) {
            delete[] reziduum;
            delete[] przyblizenie;
            delete[] estymator;
            return;
        }
        i++;
    }

}

void sor_method(double** A, double *b, double* x0, int n) {
    int i = 0;
    double suma, rez, est, w = 1.0/2.0;
    double *estymator = new double[n];
    double *reziduum = new double[n];
    double *przyblizenie = new double[n];
    std::cout << "Metoda Gaussa-Seidela:\n\n";
    std::cout << "iteracja\tx1\t\tx2\t\tx3\t\tx4\t\testymator\treziduum\n";

    while(true) {
        std::cout << i << "\t\t";
        for(int j = 0; j < n; j++) {
            suma = 0.0;
            for (int k = 0; k < n; k++)
                if (j != k)
                    suma += x0[k] * A[j][k];
            przyblizenie[j] = (1.0 - w) * x0[j] + (w * (b[j] - suma))/A[j][j];
            printf("%.6e\t", przyblizenie[j]);
        }

        for(int j = 0; j < n; j++) {
            reziduum[j] = 0.0;
            for(int k = 0; k < n; k++) {
                reziduum[j] += A[j][k] * x0[k];
            }
            reziduum[j] = fabs(reziduum[j] - b[j]);
            estymator[j] = fabs(przyblizenie[j] - x0[j]);
            x0[j] = przyblizenie[j];
        }

        est = max_elem(estymator, n);
        rez = max_elem(reziduum, n);

        printf("%.6e\t%.6e\t\n", est, rez);

        if((rez <= tolf && est <= tolx) || i >= max_iter) {
            delete[] reziduum;
            delete[] przyblizenie;
            delete[] estymator;
            return;
        }
        i++;
    }
}

double** create_matrix(int n) {
    double** matrix = new double *[n];
    for (int i = 0; i < n; i++) {
        matrix[i] = new double[n];
    }

    return matrix;
}

double max_elem(double *vect, int n) //funkcja znajdująca największą wartość w wektorze/tablicy
{
    double x = vect[0];
    for (int i = 1; i < n; i++)
        if (vect[i] > x)
            x = vect[i];
    return x;
}

void print_vector(double* vect, int n) {
    for(int i = 0; i < n; i++) {
        std::cout << vect[i] << "\t";
    }
    std::cout << std::endl;
}