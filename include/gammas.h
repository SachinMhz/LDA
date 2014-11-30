#ifndef __gammas_H // to avoid multiple inclusion of same headers
#define __gammas_H

#include <assert.h>
#include <math.h>

double digamma(double x) {
	double result = 0, xx, xx2, xx4;
	assert(x > 0);
	for (; x < 7; ++x)
		result -= 1 / x;
	x -= 1.0 / 2.0;
	xx = 1.0 / x;
	xx2 = xx*xx;
	xx4 = xx2*xx2;
	result += log(x) + (1. / 24.)*xx2 - (7.0 / 960.0)*xx4 + (31.0 / 8064.0)*xx4*xx2 - (127.0 / 30720.0)*xx4*xx4;
	return result;
}

double trigamma(double x)
{
	double p;
	int i;

	x = x + 6;
	p = 1 / (x*x);
	p = (((((0.075757575757576*p - 0.033333333333333)*p + 0.0238095238095238)
		*p - 0.033333333333333)*p + 0.166666666666667)*p + 1) / x + 0.5*p;
	for (i = 0; i<6; i++)
	{
		x = x - 1;
		p = 1 / (x*x) + p;
	}
	return(p);
}

#endif