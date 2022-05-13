#include <iostream>
#include <math.h>

using namespace std;

void EFloat() {
    float epsilon = 1.0f;
    float stala = 2.0f;
    int l_bitow = 0;

    float wyrazenie = epsilon/stala + 1.0f;

    while(wyrazenie > 1.0f) {
        epsilon /= stala;
        wyrazenie = epsilon/stala + 1.0f;
        l_bitow++;
    }

    cout << "Float:\n";
    cout << "Liczba bitow mantysy: " << l_bitow << endl;
    cout << "Najwiekszy epsilon: " << epsilon << endl;
}

void EDouble() {
    double epsilon = 1.0;
    double stala = 2.0;
    int l_bitow = 0;

    double wyrazenie = epsilon/stala + 1.0;

    while(wyrazenie > 1.0) {
        epsilon /= stala;
        wyrazenie = epsilon/stala + 1.0;
        l_bitow++;
    }

    cout << "Double:\n";
    cout << "Liczba bitow mantysy: " << l_bitow << endl;
    cout << "Najwiekszy epsilon: " << epsilon << endl;
}


int main() {

    EDouble();
    EFloat();

    return 0;
}