CPP = g++
RM = rm -f
SRCDIR = ./src
INCLUDEDIR = -I./include
			
all:	lda	

lda:	bleicorpus.o estep.o estimatealpha.o mstep.o main.o
	$(CPP) -o lda bleicorpus.o estep.o estimatealpha.o mstep.o main.o

bleicorpus.o:	$(SRCDIR)/corpora/bleicorpus.cpp
	$(CPP) -c $(SRCDIR)/corpora/bleicorpus.cpp $(INCLUDEDIR)

main.o:	$(SRCDIR)/main.cpp
	$(CPP) -c $(SRCDIR)/main.cpp $(INCLUDEDIR)

estep.o:	$(SRCDIR)/Estep.cpp
	$(CPP) -c $(SRCDIR)/Estep.cpp $(INCLUDEDIR)

estimatealpha.o:	$(SRCDIR)/estimatealpha.cpp
	$(CPP) -c $(SRCDIR)/estimatealpha.cpp $(INCLUDEDIR)

mstep.o:	$(SRCDIR)/Mstep.cpp
	$(CPP) -c $(SRCDIR)/Mstep.cpp $(INCLUDEDIR)

clean:
	$(RM) lda bleicorpus.o estep.o estimatealpha.o mstep.o main.o 
