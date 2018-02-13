/*
��� 0=<x<=2 � �����  h=0.2  ��������� �������� �������  f(x)
� �������������� ���������  QUANC8, ���  f(x)=0-1|exp(t) * sin(t) .
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


// �������� �������
double Function(double t) {
    return exp(t) * sin(t);
}


using namespace std;

int main() {
    //�������� ������
    const double min_x = 0,max_x=2,h=0.2;
    int nodeDigit = (max_x-min_x)/h;
    //QUANC8(�������, ������,�������,ABSERR,RELERR,���������, �����������, ���-�� ���������� �������, ����)
    //������ ��� QUANC8
    const int down=0,up=1;
    const double abserr = 1.0e-12, relerr = 0;
    double errest, flag;
    int nofun[nodeDigit];
    double x[nodeDigit], y[nodeDigit];
    //�������� ������� � �������� ������
    for (int i = 0; i < nodeDigit; ++i) {
        x[i] = h * i;
        quanc8(Function(x[i]),down,up,abserr,relerr,&y[i],&errest,nofun,&flag);
    }


}
