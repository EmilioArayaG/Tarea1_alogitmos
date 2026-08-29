CXX = g++
CXXFLAGS = -std=c++17 -O3 -Wall

all: merge quick patience std

merge: sorting.cpp algorithms/mergesort.cpp
	$(CXX) $(CXXFLAGS) sorting.cpp algorithms/mergesort.cpp -o sorting_merge

quick: sorting.cpp algorithms/quicksort.cpp
	$(CXX) $(CXXFLAGS) sorting.cpp algorithms/quicksort.cpp -o sorting_quick

patience: sorting.cpp algorithms/patiencesort.cpp
	$(CXX) $(CXXFLAGS) sorting.cpp algorithms/patiencesort.cpp -o sorting_patience

std: sorting.cpp algorithms/sort.cpp
	$(CXX) $(CXXFLAGS) sorting.cpp algorithms/sort.cpp -o sorting_std

clean:
	rm -f sorting_merge sorting_quick sorting_patience sorting_std