#include <iostream>
#include <cmath>
#include <fstream>

const double p = 1.0, q = 0.0, r = -4.0;
const double alfa = 0.0, beta = 1.0, gamma = -1.0;
const double phi = 0.0, psi = 1.0, theta = 0.0;
double begin = 0.0, end = 1.0;

double fun(double x) {
    return (exp( 2.0-2.0*x) - 4.0*exp(4.0 - x * 2.0)+ 4.0*exp(x * 2.0) - exp(2.0 + 2.0*x) - x + x*exp(4.0)) / ( 4.0 - 4.0*exp(4.0));
}

void thomas_algorithm(double *l, double *d, double *u, double *b, double *x, int N) {
    double *tempB = new double[N], *tempD = new double[N];
    tempD[0] = d[0];
    tempB[0] = b[0];

    for (int i = 1; i < N; i++) {
        tempD[i] = d[i] - l[i - 1] * (u[i - 1] /tempD[i - 1]);
    }
    for (int i = 1; i < N; i++){
        tempB[i] = b[i] - l[i - 1] * tempB[i - 1] / tempD[i - 1];
    }
    x[N - 1] = tempB[N - 1] / tempD[N - 1];
    for (int i = N - 2; i >= 0; i--){
        x[i] = (tempB[i] - u[i] * x[i + 1]) / tempD[i];
    }
}

double max_elem(double *error, int N) {
    double max = fabs(error[0]);
    for (int i = 0; i < N; i++)
        if (fabs(error[i]) > max){
            max = fabs(error[i]);
        }
    return max;
}

double numerow( double h, int N ) {
    double *l, *d, *u, *b, *x, *error;
    double xp = begin;

    l = new double[N], d = new double[N], u = new double[N], b = new double[N],
    x = new double[N], error = new double[N];

    d[0] = beta - alfa / h;
    u[0] = alfa / h;
    b[0] = -gamma;

    for(int i = 1; i < N - 1; i++) {
        l[i - 1] = p / (h * h) + r / 12.0;
        d[i] = (-2.0 * p) / (h * h) + r * (10.0 / 12.0);
        u[i] = p / (h * h) + r / 12.0;
        b[i] = (xp + i * h);
    }

    l[N - 2] = -phi / h;
    d[N - 1] = -phi / h + psi;
    b[N - 1] = -theta;

    thomas_algorithm(l, d, u, b, x, N);

    if(N==1002) {
        xp = begin;
        std::fstream fileNumerow, fileFun;
        fileNumerow.open( "resNumerow.txt", std::ios::out);
        fileFun.open( "resFun.txt", std::ios::out);
        fileFun.precision(12);
        fileNumerow.precision(12);
        for (int i = 0; i < N; i++) {
            fileNumerow << xp << "\t" << x[i] << "\t" << std::endl;
            fileFun << xp << "\t" << fun(xp) << std::endl;
            xp += h;
        }
        fileFun.close();
        fileNumerow.close();
    }

    for (int i = 0; i < N; i++) {
        error[i] = fabs( x[i] - fun(xp) );
        xp += h;
    }

    double maxError = max_elem(error, N); //znajdujemy największy błąd

    return maxError;
}
double konwFunc(double h, int N) {
    double *l, *d, *u, *b, *x, *error;
    double xp = begin;

    l = new double[N], d = new double[N], u = new double[N], b = new double[N], x = new double[N], error = new double[N];

    u[0] = alfa / h;
    d[0] = beta - alfa / h;
    b[0] = -gamma;

    for(int i = 1; i < N - 1; i++) {
        l[i - 1] = p / (h * h) - q / (2.0 * h);
        d[i] = (-2.0 * p) / (h * h) + r;
        u[i] = p / (h * h) + q / (2.0 * h);
        b[i] = (xp + i * h);
    }

    l[N - 2] = -phi / h;
    d[N - 1] = -phi / h + psi;
    b[N - 1] = -theta;

    thomas_algorithm(l, d, u, b, x, N);

    if(N==1002) {
        xp = begin;
        std::fstream fileKonw;
        fileKonw.open( "resKonw.txt", std::ios::out);
        fileKonw.precision(12);
        for (int i = 0; i < N; i++){
            fileKonw << xp << "\t" << x[i] << std::endl;
            xp += h;
        }
        fileKonw.close();
    }

    for (int i = 0; i < N; i++) {
        error[i] = fabs(x[i] - fun(xp));
        xp += h;
    }

    double maxError = max_elem(error, N);

    return maxError;
}

int main() {
    double h, errorNumerow, errorKonw;
    int N;

    std::fstream fileKonw, fileNumerow;
    fileKonw.open( "errorKonw.txt", std::ios::out );
    fileNumerow.open( "errorNumerow.txt", std::ios::out );
    fileKonw.precision(12);
    fileNumerow.precision(12);

    for (N = 2 ; N < 100000; N += 100){
        h = (end - begin) / (N-1);
        errorKonw = konwFunc(h, N);
        errorNumerow = numerow(h, N);
        fileKonw << log10(h) << "\t" << log10(errorKonw) << std::endl;
        fileNumerow << log10(h) << "\t" << log10(errorNumerow) << std::endl;
    }

    fileNumerow.close();
    fileKonw.close();

    return 0;
}