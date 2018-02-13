/*
Для 0=<x<=2 с шагом  h=0.2  вычислить значения функции  f(x)
с использованием программы  QUANC8, где  f(x)=0-1|exp(t) * sin(t) .
По полученным точкам построить сплайн-функцию и полином Лагранжа 10-й степени.
Сравнить значения сплайн-функции и полинома с точным значением  f(x)
(вычислить интеграл аналитически) в точках  xk=(k - 0.5)*h  для  k=1,2,…10.
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
    //QUANC8(функция, нижняя,верхняя,ABSERR,RELERR,результат, погрешность, кол-во вычислений функции, флаг)
    //Данные для QUANC8
    const int down=0,up=1;
    const double abserr = 1.0e-12, relerr = 0;
    double errest, flag;
    int nofun[nodeDigit];
    double x[nodeDigit], y[nodeDigit];
    //Значения функции в заданных точках
    for (int i = 0; i < nodeDigit; ++i) {
        x[i] = h * i;
        quanc8(Function(x[i]),down,up,abserr,relerr,&y[i],&errest,nofun,&flag);
    }


}
