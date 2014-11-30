#ifndef LDA_H
#define LDA_H

#include <vector>
#include <cmath>
#include <math.h>
#include "Matrix615.h"

class model{
public:
	int num_of_topics;
	int num_of_unique_words;
	Matrix615<double> log_beta;
	double alpha;
	model(int k, int V, double alphava) :num_of_topics(k), num_of_unique_words(V), log_beta(k, V, 0), alpha(alphava){ }
};

class document{
public:
	int total_length;
	int length;
	std::vector<double> counts;
	std::vector<double> index;
};

class corpus{
public:
	std::vector<document> docs;
	std::vector<int> lengths;
	int num_of_docs;
	int max_length;
	int number_of_unique_words;
	// corpus(int num_of_docs, document docs) :num_of_docs(num_of_docs), lengths(num_of_docs);
};


class variational_parameters{
public:
	Matrix615<double> phi;
	std::vector<double> gamma;
	double variational_inference(document doc, model model_lda, variational_parameters v);
	variational_parameters(int doc_length, int num_of_topics) :phi(doc_length, num_of_topics, 1 / num_of_topics),gamma(num_of_topics){ }
};

class sufficient_stats{
public:
	Matrix615<double> word_probabilites;
	std::vector<double> word_total;
	int num_of_topics;
	double suffstats;
	int num_of_unique_words;
	sufficient_stats(int num_of_topics, int num_of_unique_words) :num_of_topics(num_of_topics), num_of_unique_words(num_of_unique_words), word_probabilites(num_of_topics, num_of_unique_words, 0),suffstats(0.0){ }
};


double likelihood_calculate(document doc, model model_lda, variational_parameters v);
double Newton_alpha(model model_lda, sufficient_stats s, int D);
void max_likelihood_estimate(model model_lda, sufficient_stats s, int D);
bool check_nonconvergence(double likelihood, double old_likelihood, double ZEPS, int iteration);

#endif