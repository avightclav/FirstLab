/*
��� 0=<x<=2 � �����  h=0.2  ��������� �������� �������  f(x)
� �������������� ���������  QUANC8, ���  f(x)=0-1|exp(x*t) * sin(t) .
�� ���������� ������ ��������� ������-������� � ������� �������� 10-� �������.
�������� �������� ������-������� � �������� � ������ ���������  f(x)
(��������� �������� ������������) � ������  xk=(k - 0.5)*h  ���  k=1,2,�10.
*/
#include <stdio.h>
#include "quanc8.h"
#include "lagrange.h"
#include "SPLINES.H"
#include <math.h>
#include <iostream>

double current_x;

// �������� �������
double Function(double t) {
    return exp(current_x * t) * sin(t);
}

using namespace std;

int main() {
    //�������� ������
    const double min_x = 0, max_x = 2, h = 0.2;
    const int firstNodeDigit = 1 + (max_x - min_x) / h;//����� �� ������� ������ ��������
    const int secondNodeDigit = 10;//����� � ������� ���������

    //QUANC8(�������, ������,�������,ABSERR,RELERR,���������, �����������, ���-�� ���������� �������, ����)
    //������ ��� QUANC8
    const int down = 0, up = 1;
    const double abserr = 1.0e-12, relerr = 0;
    double errest, flag;
    int nofun[firstNodeDigit];
    double x[firstNodeDigit], y[firstNodeDigit];//���� � �������� ������� � �����
    for (int i = 0; i < firstNodeDigit; ++i) {
        x[i] = h * i;
        current_x = x[i];
        quanc8(Function, down, up, abserr, relerr, &y[i], &errest, nofun, &flag);
    }

    //�������� ������ ������� � ������� ��������
    double splineFunction[secondNodeDigit], b[secondNodeDigit], c[secondNodeDigit], d[secondNodeDigit];
    double lagrangeFunction[secondNodeDigit];
    double defaultFunction[secondNodeDigit];

    spline(secondNodeDigit, x, y, b, c, d);

    for (int k = 0; k < secondNodeDigit; ++k) {
        double xk = ((k + 1) - 0.5) * h;
        current_x = xk;
        quanc8(Function, down, up, abserr, relerr, &defaultFunction[k], &errest, nofun, &flag);
        lagrangeFunction[k] = lagrange(secondNodeDigit, x, y, xk);
        splineFunction[k] = seval(secondNodeDigit, &xk, x, y, b, c, d);
    }


    printf("-----------------------------------------------------\n");
    printf("k |  xk   |    Values    |   Lagrange   |    Spline\n");
    printf("-----------------------------------------------------\n");
    for (int k = 0; k < secondNodeDigit; ++k) {
        printf("%-*.d| ", 2, k + 1);
        printf("%.2f | ", ((k + 1) - 0.5) * h);
        printf("%.10f | ", defaultFunction[k]);
        printf("%.10f | ", lagrangeFunction[k]);
        printf("%.10f", splineFunction[k]);
        printf("\n");
    }

    //�������� �����������
    for (int i = 0; i < secondNodeDigit; ++i) {
        double acceptValue = 0.1;
        if (abs(defaultFunction[i] - lagrangeFunction[i]) > acceptValue ||
            abs(defaultFunction[i] - splineFunction[i])>acceptValue) {
            printf("Error in point k=" ,i);
            printf("\n");
        }

    }

}



