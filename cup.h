#ifndef CUP_H
#define CUP_H


#include <mbstring.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "malloc.h"
#include "math.h"
#ifndef PI
#define PI (3.141592653589793)
#endif

/* define string comparision */
#define	STREQ(s,t) (strcmp(s,t) == 0)
#define	STRLT(s,t) (strcmp(s,t) < 0)
#define	STRGT(s,t) (strcmp(s,t) > 0)

#define NINT(x) ((int)((x)>0.0?(x)+0.5:(x)-0.5))
#define SQR(a) ((a)*(a))
#define ISODD(n) ((n) & 01)



#ifndef _COMPLEX_
typedef struct
{
	float r; //实部
	float i; //虚部
}complex;
#endif/* complex */

#ifndef MAX
#define	MAX(x,y) ((x) > (y) ? (x) : (y))
#endif
#ifndef MIN
#define	MIN(x,y) ((x) < (y) ? (x) : (y))
#endif
/*Function Prototypes:*/
/*alloc for memory*/
void *alloc1 (size_t n1, size_t size);
void *realloc1 (void *v, size_t n1, size_t size);
void free1 (void *p);
void **alloc2 (size_t n1, size_t n2, size_t size);
void free2 (void **p);
void ***alloc3 (size_t n1, size_t n2, size_t n3, size_t size);
void free3 (void ***p);
void ****alloc4 (size_t n1, size_t n2, size_t n3, size_t n4, size_t size);
void free4 (void ****p);
void *****alloc5 (size_t n1, size_t n2, size_t n3, size_t n4, size_t n5, size_t size);
void free5 (void *****p);
void ******alloc6 (size_t n1, size_t n2, size_t n3, size_t n4, size_t n5, size_t n6, 
				   size_t size);
void free6 (void ******p);
int *alloc1int (size_t n1);
int *realloc1int (int *v, size_t n1);
void free1int (int *p);
int **alloc2int (size_t n1, size_t n2);
void free2int (int **p);
int ***alloc3int (size_t n1, size_t n2, size_t n3);
void free3int (int ***p);
float *alloc1float (size_t n1);
float *realloc1float (float *v, size_t n1);
void free1float (float *p);
float **alloc2float (size_t n1, size_t n2);
void free2float (float **p);
float ***alloc3float (size_t n1, size_t n2, size_t n3);
void free3float (float ***p);
float ****alloc4float (size_t n1, size_t n2, size_t n3, size_t n4);
void free4float (float ****p);
float *****alloc5float (size_t n1, size_t n2, size_t n3, size_t n4, size_t n5);
void free5float (float *****p);
float ******alloc6float (size_t n1, size_t n2, size_t n3, size_t n4, size_t n5, 
                         size_t n6);
void free6float (float ******p);
int ****alloc4int (size_t n1, size_t n2, size_t n3, size_t n4);
void free4int (int ****p);
int *****alloc5int (size_t n1, size_t n2, size_t n3, size_t n4, size_t n5);
void free5int (int *****p);
unsigned char *****alloc5uchar(size_t n1,size_t n2,size_t n3,size_t n4,
							   size_t n5);
void free5uchar(unsigned char *****p);
unsigned short *****alloc5ushort(size_t n1,size_t n2,size_t n3,size_t n4,
								 size_t n5);
void free5ushort(unsigned short *****p);
unsigned short ******alloc6ushort(size_t n1,size_t n2,size_t n3,size_t n4,
								  size_t n5,size_t n6);
void free6ushort(unsigned short ******p);
double *alloc1double (size_t n1);
double *realloc1double (double *v, size_t n1);
void free1double (double *p);
double **alloc2double (size_t n1, size_t n2);
void free2double (double **p);
double ***alloc3double (size_t n1, size_t n2, size_t n3);
void free3double (double ***p);
complex *alloc1complex (size_t n1);
complex *realloc1complex (complex *v, size_t n1);
void free1complex (complex *p);
complex **alloc2complex (size_t n1, size_t n2);
void free2complex (complex **p);
complex ***alloc3complex (size_t n1, size_t n2, size_t n3);
void free3complex (complex ***p);

/*end of alloc for memory*/

/* begin of complex maths */
/* part 1 */
complex cadd (complex a, complex b);
complex csub (complex a, complex b);
complex cmul (complex a, complex b);
complex cdiv (complex a, complex b);
float rcabs (complex z);
complex cmplx (float re, float im);
complex conjg (complex z);
complex cneg (complex z);
complex cinv (complex z);
complex csqrt (complex z);
complex cexp (complex z);
complex crmul (complex a, float x);
/* part 2 */
complex cipow(complex a, int p);
complex crpow(complex a, float p);
complex rcpow(float a, complex p);
complex ccpow (complex a, complex p);
complex ccos(complex a);
complex csin(complex a);
complex ccosh(complex a);
complex csinh(complex a);
complex cexp1(complex a);
complex clog(complex a);
/* end of complex maths */

/* su fft begin */
int npfa (int nmin);
int npfao (int nmin, int nmax);
int npfar (int nmin);
int npfaro (int nmin, int nmax);
void pfacc (int isign, int n, complex z[]);
void pfacr (int isign, int n, complex cz[], float rz[]);
void pfarc (int isign, int n, float rz[], complex cz[]);
void pfamcc (int isign, int n, int nt, int k, int kt, complex z[]);
void pfa2cc (int isign, int idim, int n1, int n2, complex z[]);
void pfa2cr (int isign, int idim, int n1, int n2, complex cz[], float rz[]);
void pfa2rc (int isign, int idim, int n1, int n2, float rz[], complex cz[]);
/* su fft end */


/* general signal processing */
void conv (int lx, int ifx, float *x, int ly, int ify, float *y,
	int lz, int ifz, float *z);

/* other linear system solvers */
void stoepd (int n, double r[], double g[], double f[], double a[]);
void stoepf (int n, float r[], float g[], float f[], float a[]);

/*  PC byte swapping -- su swapbyte */
void swap_short_2(short *tni2);
void swap_u_short_2(unsigned short *tni2);
void swap_int_4(int *tni4);
void swap_u_int_4(unsigned int *tni4);
void swap_long_4(long *tni4);
void swap_u_long_4(unsigned long *tni4);
void swap_float_4(float *tnf4);
void swap_double_8(double *tndd8);

/* segy <--> su -- by xh*/
void segy2su(char *segyin,char *suout);
void su2segy(char *suin,char *segyout);

/* scd pkdge */
void scd_m1();
void scd_m2();
void scd_m3();

int minphase(FILE *fpr, FILE *fpw);
#endif /* CUP_H */