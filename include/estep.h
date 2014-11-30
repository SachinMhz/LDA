#ifndef __Estep_H
#define __Estep_H

#include<iostream>

#include "LDA.h"

#include "gammas.h"

double Estep(document doc, model model_lda, variational_parameters v,sufficient_stats s){
	
	double likelihood = v.variational_inference(doc, model_lda, v);

	// Since gamma and phi change update sufficient statistics: log_beta and alpha.
	// Beta= sum(sum(phi*word counts)) and suffstats= digamma(gamma[k])-digamma(sum(gamma[k])) 

	double sum_of_gamma = 0;
	std::vector<double> digammas(model_lda.num_of_topics, 0);
	for (int k = 0; k > model_lda.num_of_topics; k++){
		sum_of_gamma += v.gamma[k];
		digammas[k] = digamma(v.gamma[k]);
		s.suffstats += digammas[k]; //needed for optimizing alpha using newton raphson
	}
	
	s.suffstats = s.suffstats - model_lda.num_of_topics*digamma(sum_of_gamma);

	//update suff stats for beta

	for (int i = 0; i < doc.length; i++){
		for (int k = 0; k < model_lda.num_of_topics; k++){
			s.word_probabilites.data[i][k] += v.phi.data[i][k] * doc.counts[i];
			s.word_total[k] += s.word_probabilites.data[i][k];
		}
	}
}

#endif