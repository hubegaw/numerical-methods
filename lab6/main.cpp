#include <iostream>

using namespace std;

void thomas_algorithm_for_matrix(double *u, double *d, double *l, double *n, int size) {
    int i;
    n[0] = d[0];
    for(i = 1; i < size; i++)
        n[i] = d[i] - (l[i] * u[i - 1]) / n[i - 1];
}

void thomas_algorithm_for_vector(double *u, double *b, double *l, double *x, double *n, double *r, int size) {
    int i,j;
    r[0] = b[0];
    for(i = 1; i < size; i++)
        r[i] = b[i] - (l[i] * r[i - 1]) / n[i - 1];

    x[size] = r[size] / n[size];
    for(j = size - 1; j >= 0; j--)
        x[j] = (r[j] - u[j] * x[j + 1]) / n[j];
}

void print_vector(double *vector, int size) {
    int i;
    for(i = 0; i < size; i++)
        cout << vector[i] << endl;
    cout << endl;
}

int main() {
    int size = 6;
    double *u, *d, *l, *b, *x, *n, *r;
    u = new double[size - 1];   // nad przekątną
    d = new double[size];       // na przekątnej
    l = new double[size - 1];   // pod przekątną
    b = new double[size];       // wektor b
    x = new double[size];       // wynik
    n = new double[size];       // eta
    r = new double[size];       // przekształcony wektor b

    u[0] = 1.0 / 2.0; u[1] = 1.0 / 4.0; u[2] = 1.0 / 6.0; u[3] = 1.0 / 8.0; u[4] = 1.0 / 10.0;
    d[0] = 10.0; d[1] = 20.0; d[2] = 30.0; d[3] = 30.0; d[4] = 20.0; d[5] = 10.0;
    l[0] = 1.0 / 3.0; l[1] = 1.0 / 5.0; l[2] = 1.0 / 7.0; l[3] = 1.0 / 9.0; l[4] = 1.0 / 11.0;
    b[0] = 31.0; b[1] = 165.0 / 4.0; b[2] = 917.0 / 30.0; b[3] = 851.0 / 28.0; b[4] = 3637.0 / 90.0; b[5] = 332.0 / 11.0;

    thomas_algorithm_for_matrix(u, d, l, n, size);
    thomas_algorithm_for_vector(u, b, l, x, n, r, size-1);

    cout << "\nWektor u\n";
    print_vector(u, size - 1);
    cout << "Wektor d\n";
    print_vector(d, size);
    cout << "Wektor l\n";
    print_vector(l, size - 1);
    cout << "Wektor b\n";
    print_vector(b, size);

    cout << "Wektor eta\n";
    print_vector(n, size);
    cout << "Wektor r\n";
    print_vector(r, size);
    cout << "Wektor x (wynik)\n";
    print_vector(x, size);

    delete[] u;
    delete[] d;
    delete[] l;
    delete[] b;
    delete[] x;
    delete[] n;
    delete[] r;

    return 0;
}