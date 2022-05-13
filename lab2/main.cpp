#include <iostream>
#include <math.h>
#include <fstream>
#include <iomanip>

using namespace std;

double f(double x);
double taylor(double x);
double rel_error(double approx_result, double exact_result);

int main() {
    double x, exact_result, approx_result, log_result, error, log_error;
    fstream data, results_fun, results;

    data.open("data.txt", ios::in);
    results_fun.open("results_fun.txt", ios::out);
    results.open("results.txt", ios::out);

    if(!data.good() || !results_fun.good() || !results.good()) {
        return -1;
    }

    results_fun << setprecision(20);
    results_fun << scientific;
    results << setprecision(20);
    results << scientific;

    while(!data.eof()) {
        data >> log_result;
        data >> x;
        data >> exact_result;

        if(log_result >= -0.5) {
            /***************************************************************
             * Obliczanie wartości funkcji z zadania oraz błędu względnego *
             ***************************************************************/
            approx_result = f(x);
            error = rel_error(approx_result, exact_result);     //wyliczenie błędu względnego
            log_error = log10(error);   //zależność logarytmu dziesiętnego z bezwzględnej wartości błędu względnego
            results_fun << log_result << "\t" << log_error << "\n";
            results << log_result << "\t" << log_error << "\n";
        } else {
            /***********************************************************************
             * Obliczanie wartości funkcji z szeregu Taylora oraz błędu względnego *
             ***********************************************************************/
            approx_result = taylor(x);
            error = rel_error(approx_result, exact_result);
            log_error = log10(error);
            results << log_result << "\t" << log_error << "\n";
        }
    }

    data.close();
    results_fun.close();
    results.close();

    return 0;
}

double f(double x) {
    return (1.0 - exp(-x))/x;
}

double taylor(double x) {
    double sign = -1, result = 1, step = 1;
    for(int i = 2; i < 30; i++) {
        step *= x/i;
        result += sign * step;
        sign = -sign;
    }
    return result;
}

double rel_error(double approx_result, double exact_result) {
    return (abs(approx_result - exact_result)/exact_result);
}