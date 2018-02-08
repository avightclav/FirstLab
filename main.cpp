//Пример: считаем  в точках 0.1+0.2*к при пом. QUANC8,затем при пом.п. Лагранжа
#include <stdio.h>
#include "quanc8.h"
#include "lagrange.h"
#include <math.h>
#include <iostream>

double x=0;
double h=0.2;
double t;

// Функция (для Quanc8)
double Function (double t)
{
	return exp(x*t)*sin(t);
}

using namespace std;

int main( void )
{
	double a=0, b=1, abserr=1.0e-12, relerr=0, errest, flag;
	int nofun;

	// считаем при помощи QUANC8
	x=0;

	double ResultQUANC8[11];
	for (int i=0; i<11; i++)
	{
		quanc8(Function, a, b, abserr, relerr, &ResultQUANC8[i], &errest, &nofun, &flag);
		x+=h;
	}
	x=0;

	// вычисл.Х[i],Y[i] для полинома Лагранжа
	double lagrangeX[11], lagrangeY[11];
	double ResultsLagr[30];
	double j=0;
	
	for (int i=0; i<=10; i++)
	{
		lagrangeX[i]=j;
		j+=h;
	}
	for (int i=0; i<=10; i++)
	{
		quanc8(Function, a, b, abserr, relerr, &lagrangeY[i], &errest, &nofun, &flag);
		x+=h;
	}
	//считаем при помощи полинома Лагранжа
	double tr=0;
	for (int i=0; i<11; i++)
	{
		ResultsLagr[i]=lagrange(10, lagrangeX, lagrangeY, tr);
		tr+=h;
	}

	//Вычислим через Spline и Seval
	double xs[11],ys[11],bs[11],cs[11],ds[11];



//вывод 
	cout<<"      QUANC8    Lagrange    Spline"<<endl;
	double n=0;
	for (int i=0; i<=10; i++)
	{
		cout<<n<<"  "<<ResultQUANC8[i]<<"  "<<ResultsLagr[i]<<"  "<<ResultsLagr[i]<<endl;;
		n += h;
	}

    return 0;
}
