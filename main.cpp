/*
Для 0=<x<=2 с шагом  h=0.2  вычислить значения функции  f(x)
с использованием программы  QUANC8, где  f(x)= .
По полученным точкам построить сплайн-функцию и полином Лагранжа 10-й степени.
Сравнить значения сплайн-функции и полинома с точным значением  f(x)
(вычислить интеграл аналитически) в точках  xk=(k - 0.5) h  для  k=1,2,…10.
*/
#include <stdio.h>
#include "quanc8.h"
#include "lagrange.h"
#include "SPLINES.H"
#include <math.h>
#include <iostream>


// Исходная функция
double Function(double t) {
    return exp(t) * sin(t);
}

using namespace std;

int main() {
    //Исходные данные
    const double min_x = 0,max_x=2,h=0.2;
    int nodeDigit = (max_x-min_x)/h;
    double x[nodeDigit], y[nodeDigit];
    //Значения функции в заданных точках
    for (int i = 0; i < nodeDigit; ++i) {
        x[i] = h * i;
        y[i] = Function(x[i]);
    }

    //Коэфициенты
    double b[nodeDigit-1], c[nodeDigit-1], d[nodeDigit-1];

    spline(nodeDigit-1, x, y, b, c, d);


    //Три массива для результатов
    double resultDefault[nodeDigit];
    double resultLagrange[nodeDigit];
    double resultSpline[nodeDigit];
    //В цикле считаем сразу тремя способами
    for (int i = 0; i < nodeDigit-1; ++i) {
        double point = min_x + i * h;
        resultDefault[i] = Function(point);
        resultLagrange[i] = lagrange(nodeDigit-1, x, y, point);
        resultSpline[i] = seval(nodeDigit-1, &point, x, y, b, c, d);
    }

    printf("-----------------------------------------------------\n");
    printf("# |  x   |    Values    |   Lagrange   |    Spline\n");
    printf("-----------------------------------------------------\n");
    for (int i = 0; i < nodeDigit-1; ++i) {
        printf("%-*.d| ", 2, i + 1);
        printf("%.2f | ", x[i] + h);
        printf("%.10f | ", resultDefault[i]);
        printf("%.10f | ", resultLagrange[i]);
        printf("%.10f", resultSpline[i]);
        printf("\n");
    }
    return 0;
}
