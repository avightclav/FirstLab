/*
��� 0=<x<=2 � �����  h=0.2  ��������� �������� �������  f(x)
� �������������� ���������  QUANC8, ���  f(x)= .
�� ���������� ������ ��������� ������-������� � ������� �������� 10-� �������.
�������� �������� ������-������� � �������� � ������ ���������  f(x)
(��������� �������� ������������) � ������  xk=(k - 0.5) h  ���  k=1,2,�10.
*/
#include <stdio.h>
#include "quanc8.h"
#include "lagrange.h"
#include "SPLINES.H"
#include <math.h>
#include <iostream>


// �������� �������
double Function(double t) {
    return exp(t) * sin(t);
}

using namespace std;

int main() {
    //�������� ������
    const double min_x = 0,max_x=2,h=0.2;
    int nodeDigit = (max_x-min_x)/h;
    double x[nodeDigit], y[nodeDigit];
    //�������� ������� � �������� ������
    for (int i = 0; i < nodeDigit; ++i) {
        x[i] = h * i;
        y[i] = Function(x[i]);
    }

    //�����������
    double b[nodeDigit-1], c[nodeDigit-1], d[nodeDigit-1];

    spline(nodeDigit-1, x, y, b, c, d);


    //��� ������� ��� �����������
    double resultDefault[nodeDigit];
    double resultLagrange[nodeDigit];
    double resultSpline[nodeDigit];
    //� ����� ������� ����� ����� ���������
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
