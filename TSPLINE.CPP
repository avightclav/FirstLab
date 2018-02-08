// яЁшьхЁ  SPLINE & SEVAL
#include <stdio.h>
#include <math.h>
#include "splines.h"



int main(void)
{
double x[50],y[50],b[50],c[50],d[50];
double s,u,t,e,zz;
zz=0;
int    i;
  for (i=1;i<=10;i++)
		     {
		       x[i]=zz;
		       y[i]=exp(zz/2)-sin(3.14/zz);
			   zz+=0.1;
		     }
  spline(10,x,y,b,c,d);
  u=0.5;
  printf(" \n\nРезультаты выполнения илллюстpиpующей пpогpаммы \n для SPLINE & SEVAL\n\n");
  printf("    Arg      SEVALs value      Exact value     Rel error\n");
  while (u < 1)
  {
		      s=seval(10,&u,x,y,b,c,d);
		      t=exp(u/2)-sin(3.14/u);
		      e=abs(t-s)/t;
		      printf("\nU=%lf    S=%lf   T=%lf   Err=%lf",u,s,t,e);
		      u=u+0.1;
}
getchar();
	return 0;
}