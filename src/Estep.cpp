// Sets the variational parameters (E step)
// k Number of Topics

#include <iostream>
#include <vector>
#include "LDA.h"
#include "estimate.h"
#include "gammas.h"

// #include "gammas.h"  // Need to define log_gamma,digamma later in gammas.h

// #include<C:\Users\Yashwanth\Desktop\Courses\lda\Rcpp\inst\include\Rcpp\sugar\functions\math.h>

class document; // Forward class declarations
class model;   

int MAX_ITER = 100;
double ZEPS = 1e-4;


// Defined functions here to avoid duplicate symbol linking error

bool check_nonconvergence(double likelihood, double old_likelihood, double ZEPS, int iteration) {
		double converegence = fabs(likelihood - old_likelihood) / old_likelihood;
		if (converegence > ZEPS || iteration < MAX_ITER) return true;
		else return false;
}
// Taken from http://web.science.mq.edu.au/~mjohnson/code/digamma.c
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
// Taken from Dr.Blei's Code

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

double variational_parameters::variational_inference(document doc, model model_lda, variational_parameters v){
	double phissum;
	int iteration = 0;
	double old_likelihood = 0;
	double likelihood = 0;
	bool notconverged = true;
	std::vector<double> v_digamma(model_lda.num_of_topics,0);
	std::vector<double> phi_subtract(model_lda.num_of_topics,0);
	for (int k = 0; k < model_lda.num_of_topics; k++){
		v.gamma[k] = model_lda.alpha + (doc.total_length / model_lda.num_of_topics);  // Initalizing gamma
		v_digamma[k] = digamma(v.gamma[k]);
	}

	while (notconverged){
		for (int i = 0; i < doc.length; i++){
			phissum = 0;
			for (int k = 0; k < model_lda.num_of_topics; k++){
				phi_subtract[k] = v.phi.data[i][k];
				v.phi.data[i][k] = model_lda.log_beta.data[k][doc.index[i]] + v_digamma[k];
				phissum += v.gamma[k];
			}

			for (int k = 0; k < model_lda.num_of_topics;k++){
				v.phi.data[i][k] = exp(v.phi.data[i][k] - digamma(phissum));    // phi = beta*exp(digamma(gamma)-digamma(sum of gamma over topics)
				v.gamma[k] = v.gamma[k] + doc.counts[i] * (v.phi.data[i][k])-doc.counts[i]*(phi_subtract[k]);

				v_digamma[k] = digamma(v.gamma[k]);    
			}
		}
		iteration++;
		likelihood = likelihood_calculate(doc, model_lda, v);
		notconverged = check_nonconvergence(likelihood, old_likelihood,ZEPS,iteration);
		old_likelihood = likelihood;
		
		}
	return likelihood;
}


double likelihood_calculate(document doc, model model_lda, variational_parameters v){

	std::vector<double> final_gamma;
	double gammasum=0;
	double likelihood = 0;
	for (int k = 0; k < model_lda.num_of_topics; k++){
		gammasum += v.gamma[k];
	}

	likelihood += lgamma(model_lda.num_of_topics*model_lda.alpha)    // 1
		- model_lda.num_of_topics*lgamma(model_lda.alpha)           // 2
		- lgamma(gammasum);                                         //7

	
		for (int k = 0; k < model_lda.num_of_topics; k++){
			likelihood += (model_lda.alpha-1)*(digamma(v.gamma[k]) - digamma(gammasum))    //3
				+ (v.gamma[k] - 1)*(digamma(v.gamma[k]) - digamma(gammasum))          //8
				+lgamma(v.gamma[k]);           //   7
		}
		
		for (int i = 0; i < doc.length; i++){
			for (int k = 0; k < model_lda.num_of_topics; k++){
				if (v.phi.data[i][k] <= 0) continue;
				likelihood += v.phi.data[i][k] * (digamma(v.gamma[k]) - digamma(gammasum))     //4
					+ v.phi.data[i][k] * model_lda.log_beta.data[k][doc.index[i]] * doc.counts[i]   //5
					+ v.phi.data[i][k] * log(v.phi.data[i][k]);                    //9
			}
		}
		return likelihood;
}
