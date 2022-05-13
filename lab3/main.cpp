#include <iostream>
#include <cmath>

#define tolx 1e-12
#define tolf 1e-12
#define max_iter 30

void metoda_picarda_a();
void metoda_picarda_b();
void metoda_bisekcji_fa();
void metoda_bisekcji_fb();
void metoda_newtona_a();
void metoda_newtona_b();
void metoda_siecznych_a();
void metoda_siecznych_b();

int main() {

    std::cout << "\nmetoda picarda dla funkcji fa\n";
    metoda_picarda_a();
    std::cout << "\nmetoda picarda dla funkcji fb\n";
    metoda_picarda_b();

    std::cout << "\nmetoda bisekcji dla funkcji fa\n";
    metoda_bisekcji_fa();
    std::cout << "\nmetoda bisekcji dla funkcji fb\n";
    metoda_bisekcji_fb();

    std::cout << "\nmetoda Newtona dla funkcji fa\n";
    metoda_newtona_a();
    std::cout << "\nmetoda Newtona dla funkcji fb\n";
    metoda_newtona_b();

    std::cout << "\nmetoda siecznych dla funkcji fa\n";
    metoda_siecznych_a();
    std::cout << "\nmetoda siecznych dla funkcji fb\n";
    metoda_siecznych_b();

    return 0;
}

double fa(double x) {
    return pow(sin(x/4.0),2) - x;
}

double derivfa(double x) {
    return 0.25*sin(x/2.0)-1.0;
}

double FIa(double x) {
    return pow(sin(x/4.0),2);
}

double derivFIa(double x) {
    return 0.25 * sin(x/2.0);
}

double fb(double x) {
    return (tan(2.0*x) - x - 1.0);
}

double derivfb(double x) {
    return -1.0 + 2.0/pow(cos(2.0*x),2);
}

double FIb(double x) {
    return tan(2.0*x) - 1.0;
}

double derivFIb(double x) {
    return 2.0/pow(cos(2.0*x),2);
}

void metoda_picarda_a() {
    int i=1;
    double akt_przybl, estymator, reziduum;
    double x=1.0;
    akt_przybl = x;

    if(fabs(derivFIa(x)) > 1.0) {
        std::cout << "Rozbieznosc!\n";
        return;
    }
    std::cout << "nr.it\takt_przybl\t\testymator\t\treziduum\n";
    while(true) {
        akt_przybl = FIa(akt_przybl);

        estymator = fabs(akt_przybl-x);
        reziduum = fabs(fa(akt_przybl));
        x = akt_przybl;

        printf("%d.\t%.12e\t%.12e\t%.12e\n", i, akt_przybl,estymator,reziduum);
        i++;
        if(i > max_iter) {
            std::cout << "\nmaksymalna liczba iteracji.\n";
            break;
        } else if(estymator < tolx) {
            std::cout << "\nosiagnieto tolx.\n";
            break;
        } else if(reziduum < tolf) {
            std::cout << "\nosiagnieto tolf.\n";
            break;
        }
    }
}

void metoda_picarda_b() {
    int i=1;
    double akt_przybl, estymator, reziduum;
    double x=1.0;
    akt_przybl = x;

    if(fabs(derivFIb(x)) > 1.0) {
        std::cout << "Rozbieznosc!\n";
        return;
    }
    std::cout << "nr.it\takt_przybl\t\testymator\t\treziduum\n";
    while(true) {
        akt_przybl = FIb(akt_przybl);

        estymator = fabs(akt_przybl-x);
        reziduum = fabs(fb(akt_przybl));
        x = akt_przybl;

        printf("%d.\t%.12e\t%.12e\t%.12e\n", i, akt_przybl, estymator, reziduum);
        i++;
        if(i > max_iter) {
            std::cout << "\nmaksymalna liczba iteracji.\n";
            break;
        } else if(estymator < tolx) {
            std::cout << "\nosiagnieto tolx.\n";
            break;
        } else if(reziduum < tolf) {
            std::cout << "\nosiagnieto tolf.\n";
            break;
        }
    }
}

void metoda_bisekcji_fa() {
    double a = -2, b = 1;
    double akt_przybl, estymator, reziduum;
    int i = 1;

    std::cout << "nr.it\takt_przybl\t\testymator\t\treziduum\t\t a\t\t\tb\n";

    while(true) {
        akt_przybl = (a+b)/2.0;
        if((fa(a) < 0 && fa(akt_przybl) > 0) || (fa(a) > 0 && fa(akt_przybl) < 0)) {
            b = akt_przybl;
        } else if((fa(akt_przybl) < 0 && fa(b) > 0) || (fa(akt_przybl) > 0 && fa(b) < 0)){
            a = akt_przybl;
        } else {
            std::cout << "Brak pierwiastka w tym przedziale!\n";
            return;
        }

        estymator = fabs((b-a)/2.0);
        reziduum = fabs(fa(akt_przybl));

        printf("%d.\t%.12e\t%.12e\t%.12e\t%.12lf\t\t%.12lf\n", i, akt_przybl,estymator,reziduum,a,b);
        i++;

        if(i > max_iter) {
            std::cout << "\nmaksymalna liczba iteracji.\n";
            break;
        } else if(estymator < tolx) {
            std::cout << "\nosiagnieto tolx.\n";
            break;
        } else if(reziduum < tolf) {
            std::cout << "\nosiagnieto tolf.\n";
            break;
        }
    }
}
void metoda_bisekcji_fb() {
    double a = -2, b = 3;
    double akt_przybl, estymator, reziduum;
    int i = 1;

    std::cout << "nr.it\takt_przybl\t\testymator\t\treziduum\t\ta\t\t\tb\n";

    while(true) {
        akt_przybl = (a+b)/2.0;
        if((fb(a) < 0 && fb(akt_przybl) > 0) || (fb(a) > 0 && fb(akt_przybl) < 0)) {
            b = akt_przybl;
        } else if((fb(akt_przybl) < 0 && fb(b) > 0) || (fb(akt_przybl) > 0 && fb(b) < 0)){
            a = akt_przybl;
        } else {
            std::cout << "Brak pierwiastka w tym przedziale!\n";
            return;
        }

        estymator = fabs((b-a)/2);
        reziduum = fabs(fb(akt_przybl));

        printf("%d.\t%.12e\t%.12e\t%.12e\t%.12lf\t\t%.12lf\n", i, akt_przybl,estymator,reziduum,a,b);
        i++;

        if(i > max_iter) {
            std::cout << "\nmaksymalna liczba iteracji.\n";
            break;
        } else if(estymator < tolx) {
            std::cout << "\nosiagnieto tolx.\n";
            break;
        } else if(reziduum < tolf) {
            std::cout << "\nosiagnieto tolf.\n";
            break;
        }
    }
}

void metoda_newtona_a() {
    int i=1;
    double akt_przybl, estymator, reziduum;
    double x=0.5;

    std::cout << "nr.it\takt_przybl\t\testymator\t\treziduum\n";
    while(true) {
        akt_przybl = x - (fa(x)/ derivfa(x));

        estymator = fabs((akt_przybl-x));
        reziduum = fabs(fa(akt_przybl));
        x = akt_przybl;

        printf("%d.\t%.12e\t%.12e\t%.12e\n", i, akt_przybl,estymator,reziduum);
        i++;

        if(i > max_iter) {
            std::cout << "\nmaksymalna liczba iteracji.\n";
            break;
        } else if(estymator < tolx) {
            std::cout << "\nosiagnieto tolx.\n";
            break;
        } else if(reziduum < tolf) {
            std::cout << "\nosiagnieto tolf.\n";
            break;
        }
    }
}

void metoda_newtona_b() {
    int i=1;
    double akt_przybl, estymator, reziduum;
    double x=0.5;

    std::cout << "nr.it\takt_przybl\t\testymator\t\treziduum\n";
    while(true) {
        akt_przybl = x - (fb(x)/ derivfb(x));

        estymator = fabs((akt_przybl-x));
        reziduum = fabs(fb(akt_przybl));
        x = akt_przybl;

        printf("%d.\t%.12e\t%.12e\t%.12e\n", i, akt_przybl,estymator,reziduum);
        i++;

        if(i > max_iter) {
            std::cout << "\nmaksymalna liczba iteracji.\n";
            break;
        } else if(estymator < tolx) {
            std::cout << "\nosiagnieto tolx.\n";
            break;
        } else if(reziduum < tolf) {
            std::cout << "\nosiagnieto tolf.\n";
            break;
        }
    }
}

void metoda_siecznych_a() {
    int i=1;
    double akt_przybl, estymator, reziduum;
    double x1=0.3, x=0.8;

    std::cout << "nr.it\takt_przybl\t\testymator\t\treziduum\n";
    while(true) {

        akt_przybl = x1 - fa(x1)/((fa(x1)-fa(x))/(x1-x));
        estymator = fabs((akt_przybl-x));
        reziduum = fabs(fa(akt_przybl));

        x = x1;
        x1 = akt_przybl;

        printf("%d.\t%.12e\t%.12e\t%.12e\n", i, akt_przybl,estymator,reziduum);
        i++;

        if(i > max_iter) {
            std::cout << "\nmaksymalna liczba iteracji.\n";
            break;
        } else if(estymator < tolx) {
            std::cout << "\nosiagnieto tolx.\n";
            break;
        } else if(reziduum < tolf) {
            std::cout << "\nosiagnieto tolf.\n";
            break;
        }
    }
}

void metoda_siecznych_b() {
    int i=1;
    double akt_przybl, estymator, reziduum;
    double x1=0.4, x=0.2;

    std::cout << "nr.it\takt_przybl\t\testymator\t\treziduum\n";
    while(true) {

        akt_przybl = x1 - fb(x1)/((fb(x1)-fb(x))/(x1-x));
        estymator = fabs((akt_przybl-x));
        reziduum = fabs(fb(akt_przybl));

        x = x1;
        x1 = akt_przybl;

        printf("%d.\t%.12e\t%.12e\t%.12e\n", i, akt_przybl,estymator,reziduum);
        i++;

        if(i > max_iter) {
            std::cout << "\nmaksymalna liczba iteracji.\n";
            break;
        } else if(estymator < tolx) {
            std::cout << "\nosiagnieto tolx.\n";
            break;
        } else if(reziduum < tolf) {
            std::cout << "\nosiagnieto tolf.\n";
            break;
        }
    }
}