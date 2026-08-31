#include <iostream>
#include <vector>
#include <fstream>
#include <chrono>
#include <sys/resource.h>
#include <string>
#include <cmath>

std::vector<int> multiply(const std::vector<int>& A, const std::vector<int>& B, int N);

std::vector<int> leerMatrix(const std::string& filename) {
    std::ifstream infile(filename);
    if (!infile.is_open()) {
        std::cerr << "Error al abrir el archivo: " << filename << "\n";
        exit(1);
    }
    std::vector<int> matrix;
    int num;
    while (infile >> num) {
        matrix.push_back(num);
    }
    infile.close();
    return matrix;
}

int main(int argc, char* argv[]) {
    if (argc < 5) {
        std::cerr << "Uso: " << argv[0] << " <matriz_A.txt> <matriz_B.txt> <output.txt> <measurements.txt>\n";
        return 1;
    }

    std::string file_A = argv[1];
    std::string file_B = argv[2];
    std::string output_file = argv[3];
    std::string measure_file = argv[4];

    std::vector<int> A = leerMatrix(file_A);
    std::vector<int> B = leerMatrix(file_B);

    if (A.size() != B.size() || A.empty()) {
        std::cerr << "Error: Las matrices no tienen el mismo tamaño o estan vacias.\n";
        return 1;
    }
    
    int N = std::sqrt(A.size());
    if (N * N != (int)A.size()) {
        std::cerr << "Error: La matriz no es cuadrada.\n";
        return 1;
    }

    auto start = std::chrono::high_resolution_clock::now();
    
    std::vector<int> C = multiply(A, B, N);
    
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> duration = end - start;

    struct rusage usage;
    getrusage(RUSAGE_SELF, &usage);
    long memory_kb = usage.ru_maxrss;

    std::ofstream outfile(output_file);
    if (!outfile.is_open()) {
        std::cerr << "Error al abrir el archivo de salida: " << output_file << "\n";
        return 1;
    }
    
    for (size_t i = 0; i < C.size(); ++i) {
        outfile << C[i];
        if (i < C.size() - 1) outfile << " ";
    }
    outfile.close();

    std::ofstream measfile(measure_file);
    if (!measfile.is_open()) {
        std::cerr << "Error al abrir el archivo de mediciones: " << measure_file << "\n";
        return 1;
    }
    
    measfile << duration.count() << " " << memory_kb << "\n";
    measfile.close();

    return 0;
}