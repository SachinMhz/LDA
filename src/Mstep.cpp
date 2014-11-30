#include "LDA.h"
#include "estimate.h"

class model;
class sufficient_stats;

void max_likelihood_estimate(model model_lda, sufficient_stats s, int D){
	for (int k = 0; k < model_lda.num_of_topics; k++){
		for (int v = 0; v < model_lda.num_of_unique_words; v++){
			model_lda.log_beta.data[k][v] = log(s.word_probabilites.data[k][v]) - log(s.word_total[k]);
		}
	}

	model_lda.alpha = Newton_alpha(model_lda, s, D);
}