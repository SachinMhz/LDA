#ifndef __gammas_H // to avoid multiple inclusion of same headers
#define __gammas_H

#include <assert.h>
#include <math.h>

double digamma(double x);
double trigamma(double x);
bool check_nonconvergence(double likelihood, double old_likelihood, double ZEPS, int iteration);

#endif