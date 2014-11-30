#include<iostream>

#include "LDA.h"

#include "Estep.h"

// format  [Num_of_topics] [alpha] [directory]
bool check_nonconvergence(double likelihood, double old_likelihood, double ZEPS, int iteration);

void EM(corpus asso, double alpha, int num_of_topics);
class corpus;   //forward class
int main(int argc, char** argv){
	corpus asso;
	int num_of_topics = atoi(argv[1]);
	double alpha=atof(argv[2]);
	asso = read_data(argv[3]);
	EM(asso,alpha,num_of_topics);
}

int MAX_ITER = 100;
double ZEPS = 1e-4;

void EM(corpus asso, double alpha, int num_of_topics){
	document doc;
	model model_lda(num_of_topics, asso.number_of_unique_words, alpha);
	variational_parameters v(asso.max_length, num_of_topics);
	sufficient_stats s(num_of_topics, asso.number_of_unique_words);
	double likelihood = 0;
	double old_likelihood = 0;
	int iteration = 0;
	bool nonconverged = true;
	while (nonconverged){
		iteration++;
		std::cout << "EM Iteration No:" << iteration;
		sufficient_stats s(num_of_topics, asso.number_of_unique_words);

		// E step 

		for (int i = 0; i < asso.num_of_docs; i++){
			likelihood += Estep(asso.docs[i], model_lda, v, s);  // Calculate likelihood for each doc and update sufficient statistics	
		}


		// M step

		max_likelihood_estimate(model_lda, s, asso.num_of_docs);

		nonconverged = check_nonconvergence(likelihood, old_likelihood, ZEPS, iteration);

		old_likelihood = likelihood;

	}


}
bool check_nonconvergence(double likelihood, double old_likelihood, double ZEPS, int iteration) {
		double converegence = fabs(likelihood - old_likelihood) / old_likelihood;
		if (converegence > ZEPS || iteration < MAX_ITER) return true;
		else return false;
	}