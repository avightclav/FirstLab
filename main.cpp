//Пример: считаем  в точках 0.1+0.2*к при пом. QUANC8,затем при пом.п. Лагранжа
#include <stdio.h>
#include "quanc8.h"
#include "lagrange.h"
#include "SPLINES.H"
#include <math.h>
#include <iostream>

double x = 0;
const double min_x=0;
const double max_x = 2;
const double h = 0.2;
const int nodeDigit = 11;

// Функция (для Quanc8)
double Function(double t) {
    return exp(x * t) * sin(t);
}

using namespace std;

int main(void) {
    double a = 0, b = 1, abserr = 1.0e-12, relerr = 0, errest, flag;
    int nofun;

    // считаем при помощи QUANC8
    double ResultQUANC8[nodeDigit];
    x = min_x;
    for (int i = 0; x < max_x; i++) {
        quanc8(Function, a, b, abserr, relerr, &ResultQUANC8[i], &errest, &nofun, &flag);
        x += h;
    }

    // вычисл.Х[i],Y[i] для полинома Лагранжа
    double lagrangeX[nodeDigit], lagrangeY[nodeDigit];
    double ResultsLagr[nodeDigit];
    x = min_x;
    for (int i = 0; x < max_x; i++) {
        lagrangeX[i] = x;
        x += h;
    }
    //TODO
    x = min_x;
    for (int i = 0; x < max_x; i++) {
        quanc8(Function, a, b, abserr, relerr, &lagrangeY[i], &errest, &nofun, &flag);
        x += h;
    }
    //считаем при помощи полинома Лагранжа
    x = min_x;
    for (int i = 0; x < max_x; i++) {
        ResultsLagr[i] = lagrange(10, lagrangeX, lagrangeY, x);
        x += h;
    }

    //Вычислим через Spline и Seval
    double spl_x[nodeDigit], spl_y[nodeDigit], spl_b[nodeDigit], spl_c[nodeDigit], spl_s[nodeDigit];
    double ResultSpline[nodeDigit];
    for (int i = 0; x < max_x; i++) {
        spl_x[i] = x;
        spl_y[i] = Function(x);
        x += h;
    }
    spline(nodeDigit, spl_x, spl_y, spl_b, spl_c, spl_s);
    x = 0;
    for (int i = 0; x < max_x; i++) {
        ResultSpline[i] = seval(11, &x, spl_x, spl_y, spl_b, spl_c, spl_s);
        x += h;
    }




    //Вывод
    cout << "      QUANC8    Lagrange    Spline" << endl;
    x = 0;

    for (int i = 0; x < max_x; i++) {
        cout << x << "  " << ResultQUANC8[i] << "  " << ResultsLagr[i] << "  " << ResultSpline[i] << endl;;
        x += h;
    }

    return 0;
}
