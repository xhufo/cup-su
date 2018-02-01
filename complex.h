#ifndef COMPLEX_H
#define COMPLEX_H

#ifndef _COMPLEX_
typedef struct
{
	float r; 
	float i; 
}complex;
#endif/* complex */
 

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
 
#endif