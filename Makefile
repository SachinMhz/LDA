CPP = g++
RM = rm -f
SRCDIR = ./src
INCLUDEDIR = -I./include
PROGRAMS = bleicorpus

all:	$(PROGRAMS)

bleicorpus:	$(SRCDIR)/corpora/bleicorpus.cpp
	$(CPP) -o $@ $^ $(INCLUDEDIR)

clean:
	$(RM) $(PROGRAMS)  
