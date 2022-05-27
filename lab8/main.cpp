#include <iostream>
#include <iomanip>
#include <cmath>
#include <fstream>


template<typename Type>
Type fun(Type x) { return sin(x); }

template<typename Type>
Type deriv(Type x) { return cos(x); }

template<typename Type>
Type forwardDiff2Points(Type x, Type h) { return (fun(x + h) - fun(x))/h; }

template<typename Type>
Type backwardDiff2Points(Type x, Type h) { return (fun(x) - fun(x - h))/h; }

template<typename Type>
Type centralDiff2Points(Type x, Type h) { return (fun(x + h) - fun(x - h))/(2.0 * h); }

template<typename Type>
Type forwardDiff3Points(Type x, Type h) { return (-(3.0/2.0)*fun(x) + 2.0*fun(x + h) - (1.0/2.0)*fun(x + h + h))/h; }

template<typename Type>
Type backwardDiff3Points(Type x, Type h) { return ((1.0/2.0)*fun(x - h - h) - 2.0*fun(x - h) + (3.0/2.0)*fun(x))/h; }

template<typename Type>
Type approximate(const std::string& fileName) {
    std::fstream f;
    f.precision(12);
    f.open(fileName, std::ios::out);
    Type a = 0.0;
    Type b = 3.141592653589 / 2.0;
    Type c = (a + b)/2.0;
    Type h = 0.3, reduce = 1.5;
    Type result, error;

    f << "forward2PointsBegin\n";
    while(h > 1e-12) {
        result = forwardDiff2Points(a, h);
        error = fabs(result - deriv(a));
        std::cout << error << std::endl;
        if(isfinite(log10(error)))
            f << log10(h) << " " << log10(error) << "\n";
        h /= reduce;
    }
    f << std::endl;
    h = 0.3;
    f << "forward2PointsMiddle\n";
    while(h > 1e-12) {
        result = forwardDiff2Points(c, h);
        error = fabs(result - deriv(c));
        if(isfinite(log10(error)))
            f << log10(h) << " " << log10(error) << "\n";
        h /= reduce;
    }
    f << std::endl;
    h = 0.3;
    f << "forward3PointsBegin\n";
    while(h > 1e-12) {
        result = forwardDiff3Points(a, h);
        error = fabs(result - deriv(a));
        if(isfinite(log10(error)))
            f << log10(fabs(h)) << " " << log10(error) << "\n";
        h /= reduce;
    }
    f << std::endl;
    h = 0.3;
    f << "forward3PointsMiddle\n";
    while(h > 1e-12) {
        result = forwardDiff3Points(c, h);
        error = fabs(result - deriv(c));
        if(isfinite(log10(error)))
            f << log10(fabs(h)) << " " << log10(error) << "\n";
        h /= reduce;
    }
    f << std::endl;
    h = 0.3;
    f << "central2Points\n";
    while(h > 1e-12) {
        result = centralDiff2Points(c, h);
        error = fabs(result - deriv(c));
        if(isfinite(log10(error)))
            f << log10(fabs(h)) << " " << log10(error) << "\n";
        h /= reduce;
    }
    f << std::endl;
    h = 0.3;
    f << "backward2PointsEnd\n";
    while(h > 1e-12) {
        result = backwardDiff2Points(b, h);
        error = fabs(result - deriv(b));
        if(isfinite(log10(error)))
            f << log10(fabs(h)) << " " << log10(error) << "\n";
        h /= reduce;
    }
    f << std::endl;
    h = 0.3;
    f << "backward2PointsMiddle\n";
    while(h > 1e-12) {
        result = backwardDiff2Points(c, h);
        error = fabs(result - deriv(c));
        if(isfinite(log10(error)))
            f << log10(fabs(h)) << " " << log10(error) << "\n";
        h /= reduce;
    }
    f << std::endl;
    h = 0.3;
    f << "backward3PointsEnd\n";
    while(h > 1e-12) {
        result = backwardDiff3Points(b, h);
        error = fabs(result - deriv(b));
        if(isfinite(log10(error)))
            f << log10(fabs(h)) << " " << log10(error) << "\n";
        h /= reduce;
    }
    f << std::endl;
    h = 0.3;
    f << "backward3PointsMiddle\n";
    while(h > 1e-12) {
        result = backwardDiff3Points(c, h);
        error = fabs(result - deriv(c));
        if(isfinite(log10(error)))
            f << log10(fabs(h)) << " " << log10(error) << "\n";
        h /= reduce;
    }

    return 0;
}

int main() {
    std::cout<< std::setprecision(12)<< std::fixed;

    approximate<float>("resultsFL.txt");
    approximate<double>("resultsDl.txt");

    return 0;
}
