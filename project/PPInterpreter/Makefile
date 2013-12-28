CXX = g++
CXXFLAGS = -Wall -pedantic -std=c++11

SRCDIR =
OUTDIR = bin

EXEC = PP
SOURCES = $(wildcard *.cpp)
OBJECTS = $(SOURCES:%.cpp=$(OUTDIR)/%.o)

all: MKDIR $(EXEC)

MKDIR:
	mkdir -p $(OUTDIR)

$(EXEC): $(OBJECTS)
	$(CXX) $(OBJECTS) -o $(EXEC)

$(OBJECTS): $(OUTDIR)/%.o : %.cpp
	$(CXX) -c $(CXXFLAGS) $< -o $@

clean:
	rm -rf $(OUTDIR)
	rm -rf PP

.PHONY: clean
