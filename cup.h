#ifndef CUP_H
#define CUP_H


// #include <mbstring.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "malloc.h"
#include "math.h"
#ifndef PI
#define PI (3.141592653589793)
#endif
#ifndef pi
#define pi (3.141592653589793)
#endif
#define ERROR	NULL

/* define string comparision */
#define	STREQ(s,t) (strcmp(s,t) == 0)
#define	STRLT(s,t) (strcmp(s,t) < 0)
#define	STRGT(s,t) (strcmp(s,t) > 0)

#define NINT(x) ((int)((x)>0.0?(x)+0.5:(x)-0.5))
#define SQR(a) ((a)*(a))
#define ISODD(n) ((n) & 01)
 

#ifndef MAX
#define	MAX(x,y) ((x) > (y) ? (x) : (y))
#endif
#ifndef MIN
#define	MIN(x,y) ((x) < (y) ? (x) : (y))
#endif
/*Function Prototypes:*/
 
 

/* other linear system solvers */
void stoepd (int n, double r[], double g[], double f[], double a[]);
void stoepf (int n, float r[], float g[], float f[], float a[]);

 

/* segy <--> su -- by xh*/
void segy2su(char *segyin,char *suout);
void su2segy(char *suin,char *segyout);

/* scd pkdge */
void scd_m1();
void scd_m2();
void scd_m3();

int minphase(FILE *fpr, FILE *fpw);
void hilbert(int n, float x[], float y[]);
/* write dat */
// void WriteDat_1d(FILE *fp, float *data, int nz, int nx);
// void WriteDat_2d(FILE *fp, float **data, int nz, int nx);
#endif /* CUP_H */