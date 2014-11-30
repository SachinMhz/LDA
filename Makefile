CPP = g++
RM = rm -f
SRCDIR = ./src
INCLUDEDIR = -I./include
			
all:	lda	

lda:	bleicorpus.o utils.o lda_main.o
	$(CPP) -o lda bleicorpus.o utils.o lda_main.o

bleicorpus.o:	$(SRCDIR)/corpora/bleicorpus.cpp
	$(CPP) -c $(SRCDIR)/corpora/bleicorpus.cpp $(INCLUDEDIR)

lda_main.o:	$(SRCDIR)/lda_main.cpp
	$(CPP) -c $(SRCDIR)/lda_main.cpp $(INCLUDEDIR)

utils.o:	$(SRCDIR)/utils.cpp
	$(CPP) -c $(SRCDIR)/utils.cpp $(INCLUDEDIR)

clean:
	$(RM) lda bleicorpus.o utils.o lda_main.o  
