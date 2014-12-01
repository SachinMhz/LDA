#include "corpora/bleicorpus.h"

corpus read_data(char* fname) {
	corpus c;
	std::ifstream infile(fname);
	std::string doc;

	std::cout << "Reading data from " << fname << std::endl;

	int nDoc = 0;
	int nWord = 0;
	int maxLength = 0;

	if (infile.is_open()) {
    	while (std::getline (infile, doc)) {
    		
    		std::istringstream iss(doc);

    		int vocabSize;
      		iss >> vocabSize;
      		document d (vocabSize);
      		//std::cout << d.length << std::endl;

      		std::string t;
      		std::string delim = ":";

      		//std::cout << "Doc " << count << ": " << vocabSize << std::endl;
      		int docLength = 0;
      		while (iss >> t) {
      			int tokenId, tokenCount;
      			auto start = 0U;
      			auto end = t.find(delim);
      			while (end != std::string::npos) {
		        	tokenId = std::stoi(t.substr(start, end - start));
		        	d.index.push_back(tokenId);
		        	if (tokenId >= nWord) { nWord = tokenId + 1; }
		        	start = end + delim.length();
		        	end = t.find(delim, start);
		    	}
		    	tokenCount = std::stoi(t.substr(start, end));
		    	d.counts.push_back(tokenCount);
		    	docLength += tokenCount;
		    	d.total_length += tokenCount;
		    	//std::cout << tokenId << "->" << tokenCount << std::endl;
      		}
      		if (docLength > maxLength) { maxLength = docLength; }
      		nDoc++;

      		c.docs.push_back(d);
      		c.lengths.push_back(docLength);

      		// for (int i = 0; i < d.counts.size(); i++) {
      		// 	std::cout << d.counts[i] << std::endl;
      		// }

      		// std::cout << count << std::endl;
      		// std::cout << d.total_length << std::endl;
    	}
    	infile.close();
  	}

  	c.num_of_docs = nDoc;
  	c.number_of_unique_words = nWord;
  	c.max_length = maxLength;

	return c;
}