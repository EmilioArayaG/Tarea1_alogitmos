CXX = g++
CXXFLAGS = -std=c++17 -O3 -Wall

TARGET_NAIVE = matrix_naive
TARGET_STRASSEN = matrix_strassen

MAIN = matrix_multiplication.cpp

.PHONY: all clean run

all: $(TARGET_NAIVE) $(TARGET_STRASSEN)

$(TARGET_NAIVE): $(MAIN) algorithms/naive.cpp
	$(CXX) $(CXXFLAGS) $(MAIN) algorithms/naive.cpp -o $(TARGET_NAIVE)

$(TARGET_STRASSEN): $(MAIN) algorithms/strassen.cpp
	$(CXX) $(CXXFLAGS) $(MAIN) algorithms/strassen.cpp -o $(TARGET_STRASSEN)

clean:
	rm -f $(TARGET_NAIVE) $(TARGET_STRASSEN)

run: all
	@for file1 in data/matrix_input/*_1.txt; do \
		base=$$(basename $$file1 _1.txt); \
		file2="data/matrix_input/$${base}_2.txt"; \
		./matrix_naive $$file1 $$file2 data/matrix_output/$${base}_naive_out.txt data/measurements/$${base}_naive_meas.txt; \
		./matrix_strassen $$file1 $$file2 data/matrix_output/$${base}_strassen_out.txt data/measurements/$${base}_strassen_meas.txt; \
	done
