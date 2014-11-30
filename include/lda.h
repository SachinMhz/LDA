#ifndef LDA_H
#define LDA_H

#include <vector>
#include "Matrix615.h"

class model{
public:
	int num_of_topics;
	int num_of_unique_words;
	Matrix615<double> log_beta;
	double alpha;
	model(int k, int V, double alphava) :num_of_topics(k), num_of_unique_words(V), log_beta(k, V, 0), alpha(alphava){ }
};

class document {
public:
	int total_length;
	int length;
	std::vector<double> counts;
	std::vector<double> index;
};

class corpus {
public:
	std::vector<document> docs;
	std::vector<int> lengths;
	int num_of_docs;
	int max_length;
	int number_of_unique_words;
	// corpus(int num_of_docs, document docs) :num_of_docs(num_of_docs), lengths(num_of_docs);
};

#endif