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
	std::vector<int> counts;
	std::vector<int> index;
	document () {};
	document(int vocabSize) { 
		length = vocabSize;
		total_length = 0;
	};
};

class corpus {
public:
	std::vector<document> docs;
	std::vector<int> lengths;
	int num_of_docs;
	int max_length;
	int number_of_unique_words;
	corpus() {
		num_of_docs = 0;
		max_length = 0;
		number_of_unique_words = 0;
	};
	// corpus(int num_of_docs, document docs) :num_of_docs(num_of_docs), lengths(num_of_docs);
};

#endif