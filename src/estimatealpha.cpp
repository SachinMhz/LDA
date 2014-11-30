#include<iostream>
#include<math.h>

// Estimate alpha using newton raphson

#include "LDA.h"

#include "gammas.h"

double likelihood = 0;
double d_likelihood = 0;
double d2_likelihood = 0;
double like_with_only_alpha(int alpha,int D, int num_of_topics, sufficient_stats s) {
	double likelihood = D*(lgamma(num_of_topics*alpha)-num_of_topics*lgamma(alpha))+(alpha-1)*(s.suffstats);
	return likelihood;
}

double first_derivative(int alpha, int D, int num_of_topics, sufficient_stats s){
	double d_likelihood = D*(num_of_topics*(digamma(num_of_topics*alpha) - digamma(alpha))) + s.suffstats;
	return d_likelihood;
}

double second_derivative(int alpha, int D, int num_of_topics, sufficient_stats s){
	double d2_likelihood = D*(num_of_topics*num_of_topics*trigamma(alpha) - num_of_topics*trigamma(num_of_topics*alpha));
	return d2_likelihood;
}

int MAX_ITER = 1000;
double ZEPS = 1e-5;
int iteration = 0;
double Newton_alpha(model model_lda, sufficient_stats s, int D){

	double alpha,log_alpha;
	double convergence=1;
	alpha = model_lda.alpha;
	log_alpha = log(alpha);
	while (iteration<MAX_ITER && convergence>ZEPS){
		iteration++;
		if (isnan(alpha)){
			alpha = alpha * 10;
			log_alpha = log(alpha);
		}

		likelihood = like_with_only_alpha(alpha, D, model_lda.num_of_topics, s);
		d_likelihood = first_derivative(alpha, D, model_lda.num_of_topics, s);
		d2_likelihood = second_derivative(alpha, D, model_lda.num_of_topics, s);

		log_alpha = log_alpha - (d_likelihood / (alpha*d2_likelihood + d_likelihood));
		convergence = d_likelihood;
	}
	alpha = exp(log_alpha);
	return alpha;
}

