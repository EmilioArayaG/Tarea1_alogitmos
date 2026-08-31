CXX = g++
CXXFLAGS = -std=c++17 -O3 -Wall

TARGET_NAIVE = matrix_naive
TARGET_STRASSEN = matrix_strassen

MAIN = matrix_multiplication.cpp

all: $(TARGET_NAIVE) $(TARGET_STRASSEN)

$(TARGET_NAIVE): $(MAIN) algorithms/naive.cpp
	$(CXX) $(CXXFLAGS) $(MAIN) algorithms/naive.cpp -o $(TARGET_NAIVE)

$(TARGET_STRASSEN): $(MAIN) algorithms/strassen.cpp
	$(CXX) $(CXXFLAGS) $(MAIN) algorithms/strassen.cpp -o $(TARGET_STRASSEN)

clean:
	rm -f $(TARGET_NAIVE) $(TARGET_STRASSEN)