/* Copyright (c) Colorado School of Mines, 2005.*/
/* All rights reserved.                       */

/*********************** self documentation **********************/
/*****************************************************************************
COMPLEX - Functions to manipulate complex numbers

cadd	add two complex numbers
csub	subtract two complex numbers
cmul	multiply two complex numbers
cdiv	divide two complex numbers
cmplx	make a complex number from two real numbers
conjg	complex conjugate of a complex number 
cneg	negate a complex number
cinv	invert a complex number
csqrt	complex square root of a complex number
cexp	complex exponential of a complex number
crmul	multiply a complex number by a real number 
rcabs	real magnitude of a complex number

******************************************************************************
Structure:
typedef struct _complexStruct {  complex number
	float r,i;
} complex;

******************************************************************************
Function Prototypes:
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

******************************************************************************
Notes:
The function "rcabs" was originally called "fcabs". This produced
a collision on some systems so a new name was chosen.

******************************************************************************
Reference:
Adapted from Press et al, 1988, Numerical Recipes in C (Appendix E).

******************************************************************************
Author:  Dave Hale, Colorado School of Mines, 06/02/89
Modified:  Dave Hale, Colorado School of Mines, 04/26/90
	Added function cinv().
*****************************************************************************/
/**************** end self doc ********************************/


/*********************** self documentation **********************/
/************************************************************************
COMPLEXF  - Subroutines to perform operations on complex numbers.
		This set of functions complement the one in complex.c
		of the CWP library

cipow		raise a complex number to an integer power
crpow		raise a complex number to a real power
rcpow		raise a real number to a complex power
ccpow		raise a complex number to a complex power
ccos		compute the complex cosine of a complex angle
csin		compute the complex sine of a complex angle
ccosh		compute the complex hyperbolic cosine of a complex angle
csinh		compute the complex hyperbolic sine of a complex angle
cexp1		compute the complex exponential of a complex number
clog		compute the complex logarithm of a complex number
************************************************************************
Function Prototypes:
complex cipow(complex a, int p);
complex crpow(complex a, float p);
complex rcpow(float a, complex p);
complex ccpow (complex a, complex p)
complex ccos(complex a);
complex csin(complex a);
complex ccosh(complex a);
complex csinh(complex a);
complex cexp1(complex a);
complex clog(complex a);
************************************************************************
Credits:
	Dave Hale, original version in C++
	Gabriel Alvarez, translation to C
***********************************************************************/
/**************** end self doc ********************************/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "malloc.h"
#include "math.h" 
#include "complex.h" 
/* part 1 */
complex cadd(complex a, complex b)
{
	complex c;
	c.r = a.r+b.r;
	c.i = a.i+b.i;
	return c;
}

complex csub(complex a, complex b)
{
	complex c;
	c.r = a.r-b.r;
	c.i = a.i-b.i;
	return c;
}

complex cmul(complex a, complex b)
{
	complex c;
	c.r = a.r*b.r-a.i*b.i;
	c.i = a.i*b.r+a.r*b.i;
	return c;
}

complex cdiv(complex a, complex b)
{
	complex c;
	float r,den;
	if (fabs(b.r)>=fabs(b.i)) {
		r = b.i/b.r;
		den = b.r+r*b.i;
		c.r = (a.r+r*a.i)/den;
		c.i = (a.i-r*a.r)/den;
	} else {
		r = b.r/b.i;
		den = b.i+r*b.r;
		c.r = (a.r*r+a.i)/den;
		c.i = (a.i*r-a.r)/den;
	}
	return c;
}

complex cmplx(float re, float im)
{
	complex c;
	c.r = re;
	c.i = im;
	return c;
}

complex conjg(complex z)
{
	complex c;
	c.r = z.r;
	c.i = -z.i;
	return c;
}

complex cneg(complex z)
{
	complex c;
	c.r = -z.r;
	c.i = -z.i;
	return c;
}

complex cinv(complex z)
{
	complex c;
	float s;
	s = 1.0/(z.r*z.r+z.i*z.i);
	c.r = z.r*s;
	c.i = -z.i*s;
	return c;
}

complex csqrt(complex z)
{
	complex c;
	float x,y,w,r;
	if (z.r==0.0 && z.i==0.0) {
		c.r = c.i = 0.0;
		return c;
	} else {
		x = fabs(z.r);
		y = fabs(z.i);
		if (x>=y) {
			r = y/x;
			w = sqrt(x)*sqrt(0.5*(1.0+sqrt(1.0+r*r)));
		} else {
			r = x/y;
			w = sqrt(y)*sqrt(0.5*(r+sqrt(1.0+r*r)));
		}
		if (z.r>=0.0) {
			c.r = w;
			c.i = z.i/(2.0*w);
		} else {
			c.i = (z.i>=0.0) ? w : -w;
			c.r = z.i/(2.0*c.i);
		}
		return c;
	}
}

complex cexp(complex z)
{
	float a;
	complex c;
	a = exp(z.r);
	c.r = a*cos(z.i);
	c.i = a*sin(z.i);
	return c;
}

complex crmul(complex a, float x)
{
	complex c;
	c.r = x*a.r;
	c.i = x*a.i;
	return c;
}

float rcabs(complex z)
{
	float x,y,ans,temp;
	x = fabs(z.r);
	y = fabs(z.i);
	if (x==0.0)
		ans = y;
	else if (y==0.0)
		ans = x;
	else if (x>y) {
		temp = y/x;
		ans = x*sqrt(1.0+temp*temp);
	} else {
		temp =x/y;
		ans = y*sqrt(1.0+temp*temp);
	}
	return ans;
}

/* part 2 */
complex cipow(complex a, int p)
{
	complex res;
	complex b;

	if (p==0) {
		return cmplx(1.0,0.0);
	} else if (a.r==0.0 && a.i==0.0) {
		return cmplx(0.0,0.0);
	} else {
		res=cmplx(1.0,0.0);
		b=a;
		if (p<0) {
			p = -p;
			b = cinv(b);
		}
		for(;;) {
			if (p&1) res = cmul(res,b);
			if ((p>>=1)==0)
				return res;
			else
				b = cmul(b,b);
		}
	}
}			

complex crpow(complex a, float p)
{
	float ar,ai,amp,phs;

	if (p==0.0) return cmplx(1.0,0.0);
	if (a.r==0.0 && a.i==0.0) return cmplx(0.0,0.0);

	ar = a.r; ai = a.i;
	amp = exp(0.5*p*log(ar*ar+ai*ai));
	phs = p*atan2(ai,ar);

	return cmplx(amp*cos(phs),amp*sin(phs));	
}

complex rcpow(float a, complex p)
{
	float pr,pi,loga,amp,phs;

	if (p.r==0.0 && p.i==0.0) return cmplx(1.0,0.0);
	if (a==0.0) return cmplx(0.0,0.0);
	pr = p.r; pi = p.i;
	loga = 0.5*log(a*a);
	amp = exp(pr*loga);
	phs = pi*loga;

	return cmplx(amp*cos(phs),amp*sin(phs));	
}

complex ccpow (complex a, complex p)
{
	float ar,ai,pr,pi,loga,arga,amp,phs;

	if (p.r==0.0 && p.i==0.0) return cmplx(1.0,0.0);
	if (a.r==0.0 && a.i==0.0) return cmplx(0.0,0.0);

	pr = p.r; pi = p.i; ar = a.r; ai = a.i;
	loga = 0.5*log(ar*ar+ai*ai);
	arga = atan2(ai,ar);
	amp = exp(pr*loga-pi*arga);
	phs = pr*arga+pi*loga;

	return cmplx(amp*cos(phs),amp*sin(phs));
}

complex ccos(complex a)
{
	return cmplx(cos(a.r)*cosh(a.i),-sin(a.r)*sinh(a.i));
}

complex csin(complex a)
{
	return cmplx(sin(a.r)*cosh(a.i),cos(a.r)*sinh(a.i));
}

complex ccosh(complex a)
{
	return cmplx(cos(a.i)*cosh(a.r),sin(a.i)*sinh(a.r));
}

complex csinh(complex a)
{
	return cmplx(cos(a.i)*sinh(a.r),sin(a.i)*cosh(a.r));
}

complex cexp1(complex a)
{
	float r=exp(a.r);
	return cmplx(r*cos(a.i),r*sin(a.i));
}

complex clog(complex a)
{
	float ar=a.r,ai=a.i,h=sqrt(ar*ar+ai*ai);
	return cmplx(log(h),atan2(ai,ar));
}
