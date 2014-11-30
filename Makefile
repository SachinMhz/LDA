CPP = g++
RM = rm -f
SRCDIR = ./src
INCLUDEDIR = -I./include
			
all:	lda	

lda:	estep.o estimatealpha.o mstep.o lda_main.o
	$(CPP) -o lda estep.o estimatealpha.o mstep.o lda_main.o

bleicorpus.o:	$(SRCDIR)/corpora/bleicorpus.cpp
	$(CPP) -c $(SRCDIR)/corpora/bleicorpus.cpp $(INCLUDEDIR)

lda_main.o:	$(SRCDIR)/main.cpp
	$(CPP) -c $(SRCDIR)/main.cpp $(INCLUDEDIR)

estep.o:	$(SRCDIR)/Estep.cpp
	$(CPP) -c $(SRCDIR)/Estep.cpp $(INCLUDEDIR)


estimatealpha.o:	$(SRCDIR)/estimatealpha.cpp
	$(CPP) -c $(SRCDIR)/estimatealpha.cpp $(INCLUDEDIR)


mstep.o:	$(SRCDIR)/Mstep.cpp
	$(CPP) -c $(SRCDIR)/Mstep.cpp $(INCLUDEDIR)

utils.o:	$(SRCDIR)/utils.cpp
	$(CPP) -c $(SRCDIR)/utils.cpp $(INCLUDEDIR)

clean:
	$(RM) lda estep.o estimatealpha.o mstep.o lda_main.o 
