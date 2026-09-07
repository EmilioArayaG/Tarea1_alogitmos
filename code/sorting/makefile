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


run: all
	@echo "Ejecutando las pruebas"
	@for file in data/array_input/*.txt; do \
		base=$$(basename $$file .txt); \
		echo "======================================"; \
		echo "Procesando: $$base"; \
		echo "-> MergeSort..."; ./sorting_merge $$file data/array_output/$${base}_merge_out.txt data/measurements/$${base}_merge_meas.txt; \
		echo "-> QuickSort..."; ./sorting_quick $$file data/array_output/$${base}_quick_out.txt data/measurements/$${base}_quick_meas.txt; \
		echo "-> PatienceSort..."; ./sorting_patience $$file data/array_output/$${base}_patience_out.txt data/measurements/$${base}_patience_meas.txt; \
		echo "-> StdSort..."; ./sorting_std $$file data/array_output/$${base}_std_out.txt data/measurements/$${base}_std_meas.txt; \
	done
	@echo "Todas las mediciones fueron guardadas en data/measurements/"