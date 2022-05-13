#include <iostream>
#include <cmath>

void Newton(double x, double y, double z);

int main() {
    Newton(1.0, 3.0, 2.0);

    return 0;
}

double f1(double x, double y, double z) {
    return x*x + y*y + z*z - 2.0;
}

double f2(double x, double y) {
    return x*x + y*y - 1.0;
}

double f3(double x, double y) {
    return x*x - y;
}

double **Jacobi_odwr(double x, double y, double z) {
    double **macierz = new double *[3];
    for(int i = 0; i < 3; i++)
        macierz[i] = new double[3];
    macierz[0][0] = 0.0;
    macierz[0][1] = 1.0/(2.0*x+4.0*x*y);
    macierz[0][2] = y/(x+2.0*x*y);
    macierz[1][0] = 0.0;
    macierz[1][1] = 1.0/(2.0*y+1.0);
    macierz[1][2] = -1.0/(2.0*y+1.0);
    macierz[2][0] = 1/(2.0*z);
    macierz[2][1] = -1.0/(2.0*z);
    macierz[2][2] = 0.0;
    return macierz;
}

double norma_max(double x, double y, double z) {
    double max = x;
    if(y > max) {
        max = y;
    }
    if(z > max) {
        max = z;
    }
    return max;
}

bool sprawdz_xyz(double x, double y, double z) {
    if(x==0.0 || (1.0+2.0*y)==0.0 || z==0.0)
        return false;
    return true;
}

void Newton(double x, double y, double z) {
    double max_iter = 30, tolf = 10e-10, tolx = 10e-10;
    double estymator, reziduum;
    double wektorD[3], wektorF[3], **jakobian_odwr;
    int i = 1;

    std::cout << "nr.it\tx\t\ty\t\tz\t\t\testymator\t\treziduum\n";

    wektorF[0] = f1(x,y,z);
    wektorF[1] = f2(x,y);
    wektorF[2] = f3(x,y);

    while(1) {
        if (!sprawdz_xyz(x, y, z)) {
            std::cout << "Dzielenie przez zero!\n";
            return;
        }

        jakobian_odwr = Jacobi_odwr(x,y,z);

        for(double & k : wektorD) {
            k=0;
        }

        for(int i = 0; i < 3; i++) {
            for(int j = 0; j < 3; j++) {
                wektorD[i] = wektorD[i] + (wektorF[j]*jakobian_odwr[i][j]);
            }
        }

        x = x - wektorD[0];
        y = y - wektorD[1];
        z = z - wektorD[2];

        wektorF[0] = f1(x,y,z);
        wektorF[1] = f2(x,y);
        wektorF[2] = f3(x,y);

        estymator = norma_max(fabs(wektorD[0]),fabs(wektorD[1]),fabs(wektorD[2]));
        reziduum = norma_max(fabs(wektorF[0]),fabs(wektorF[1]),fabs(wektorF[2]));

        printf("%d.\t%.7e\t%.7e\t%.7e\t\t%.7e\t\t%.7e\n", i, x, y, z, estymator, reziduum);
        i++;

        if(i > max_iter) {
            std::cout << "\nmaksymalna liczba iteracji.\n";
            break;
        } else if(estymator < tolx && reziduum < tolf) {
            std::cout << "\nosiagnieto tolx.\n";
            break;
        }
    }
}