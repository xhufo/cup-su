/* Note   : 
		
   Date   : 2013-12-11
   Author : xh
   Emal   : xhufoxc@gmail.com
   College of Geophysics and Information Engineering
   China University of Petroleum, Beijing Campus (CUP),2013.
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <io.h>
#include "malloc.h"
#include "cup.h"
void main()
{
	int *t_1int,**t_2int;
	float *t_1float,**t_2float;
	double *t_1double,**t_2double;
	int i,j;
	complex *y;
	int n1=4,n2=3;

	y=alloc1complex(1);
	y[0].r=1;
	y[0].i=1;
//	y[0]=cmplx(1,1);
	printf("%f %f\n",y->r,y->i);
	free1complex(y);

	/* test int alloc */
	t_1int=alloc1int(4);
	for (i=0;i<4;i++)
	{
		t_1int[i]=i;
		printf("t_int[%d]=%d\n",i,t_1int[i]);
	}
	free1int(t_1int);

	t_2int=alloc2int(n1,n2);
	for (i=0;i<n2;i++)
	{
		for (j=0;j<n1;j++)
		{
			t_2int[i][j]=i;
			printf("t_2int[%d,%d]=%d\n",i,j,t_2int[i][j]);
		}
	}
	free2int(t_2int);
	
	/* test float alloc */
	t_1float=alloc1float(4);
	for (i=0;i<4;i++)
	{
		t_1float[i]=i;
		printf("t_float[%d]=%f\n",i,t_1float[i]);
	}

	t_2float=alloc2float(n1,n2);
	for (i=0;i<n2;i++)
	{
		for (j=0;j<n1;j++)
		{
			t_2float[i][j]=(float)i;
		 	printf("t_2float[%d,%d]=%f\n",i,j,t_2float[i][j]);
		}
	}
	free2float(t_2float);

	/* test double alloc */
	t_1double=alloc1double(4);
	for (i=0;i<4;i++)
	{
		t_1double[i]=(double)i;
		printf("t_double[%d]=%f\n",i,t_1double[i]);
	}
	
	t_2double=alloc2double(n1,n2);
	for (i=0;i<n2;i++)
	{
		for (j=0;j<n1;j++)
		{
			t_2double[i][j]=i;
			printf("t_2double[%d]=%f\n",i,t_2double[i][j]);
		}
	}
	free2double(t_2double);

}
