#ifndef BLEICORPUS_H
#define BLEICORPUS_H

#include <vector>


class Document {
    public:
        int* words;
        int* counts;
        int length;
        int total;
};

class Corpus {
    public:
        Document** docs;
        int numDocs;
        int numWords;
};

#endif 
