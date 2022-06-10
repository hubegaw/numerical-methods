#include <cmath>
#include <iostream>
#include <fstream>

using namespace std;

double fun(double tk) {
    return 1.0 - exp(-10.0 * (tk + atan(tk)));
}

double temp(double tk) {
    return (10.0 * tk * tk + 20.0) / (tk * tk + 1.0);
}

double BME(double dt, double tk, double yk) {
    return yk + dt * (temp(tk) * (1 - yk));
}

double PME(double dt, double tk, double yk) {
    return(yk + dt * temp(tk + dt)) / (1 + dt * temp(tk + dt));
}

double PMT(double dt, double tk, double yk) {
    double temp_tk = temp(tk);
    double temp_tk_dt = temp(tk + dt);
    return ((-dt / 2.0) * ((yk - 1) * temp_tk - temp_tk_dt) + yk) / ((dt / 2.0) * temp_tk_dt + 1);
}

double errorBME(double dt) {
    double y = 0.0, yk, maxError = 0.0, error, tk = 0.0;
    while(tk < 1.0) {
        yk = BME(dt,tk,y);
        error = fabs(fun(tk) - y);
        if(error > maxError) {
            maxError=error;
        }
        tk += dt;
        y = yk;
    }
    return maxError;
}

double errorPME(double dt) {
    double y = 0.0, yk, maxError = 0.0, error, tk = 0.0;
    while(tk < 1.0) {
        yk = PME(dt, tk, y);
        error = fabs(fun(tk) - y);
        if(error > maxError) {
            maxError = error;
        }
        tk += dt;
        y = yk;
    }
    return maxError;
}

double errorPMT(double dt) {
    double y = 0.0, yk, maxError = 0.0, error, tk = 0.0;
    while(tk < 1.0) {
        yk = PMT(dt, tk, y);
        error = fabs(fun(tk) - y);
        if(error > maxError) {
            maxError = error;
        }
        tk += dt;
        y = yk;
    }
    return maxError;
}

int main() {
    double bme = 0.0, pme = 0.0, pmt = 0.0, dt, tk;
    ofstream stableBME, unstableBME, funcPME, funcPMT, func, errorsBME, errorsPME, errorsPMT;
    stableBME.open("stableBME.txt");
    unstableBME.open("unstableBME.txt");
    funcPME.open("funcPME.txt");
    funcPMT.open("funcPMT.txt");
    func.open("func.txt");
    errorsBME.open("errorsBME.txt");
    errorsPME.open("errorsPME.txt");
    errorsPMT.open("errorsPMT.txt");

    dt = 0.001;
    while(dt > 1e-10) {
        bme = log10(errorBME(dt));
        pme = log10(errorPME(dt));
        pmt = log10(errorPMT(dt));
        errorsBME << log10(dt) << " " << bme << endl;
        errorsPME << log10(dt) << " " << pme  << endl;
        errorsPMT << log10(dt) << " " << pmt << endl;
        dt = dt / 2;
    }

    dt = 0.001;
    bme = 0.0;
    tk = 0.0;
    while(tk < 1.0) {
        bme = BME(dt, tk, bme);
        stableBME << tk << " " << bme << endl;
        tk += dt;
    }

    dt = 0.3;
    tk = 0;
    bme = 0.0;
    while(tk < 5.0) {
        bme = BME(dt, tk, bme);
        func << tk << " " << fun(tk) << endl;
        unstableBME << tk << " " << bme << endl;
        tk += dt;
    }

    dt = 0.001;
    pme = 0.0;
    tk = 0.0;
    while(tk < 1.0) {
        pme = PME(dt, tk, pme);
        funcPME << tk << " " << pme << endl;
        tk += dt;
    }

    dt = 0.001;
    pmt = 0.0;
    tk = 0.0;
    while(tk < 1.0) {
        pmt = PMT(dt, tk, pmt);
        funcPMT << tk << " " << pmt << endl;
        tk += dt;
    }

    errorsBME.close();
    errorsPME.close();
    errorsPMT.close();
    stableBME.close();
    funcPME.close();
    funcPMT.close();
    unstableBME.close();
    func.close();
    return 0;
}