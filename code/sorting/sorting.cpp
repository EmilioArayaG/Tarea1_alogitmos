#include <iostream>
#include <vector>
#include <fstream>
#include <chrono>
#include <sys/resource.h>
#include <string>

std::vector<int> sortArray(std::vector<int>& arr);

int main(int argc, char* argv[]) {
    if (argc < 4) {
        std::cerr << "Uso: " << argv[0] << " <input.txt> <output.txt> <measurements.txt>\n";
        return 1;
    }

    std::string input_file = argv[1];
    std::string output_file = argv[2];
    std::string measure_file = argv[3];

    std::ifstream infile(input_file);
    if (!infile.is_open()) {
        std::cerr << "Error al abrir el archivo de entrada: " << input_file << "\n";
        return 1;
    }
    
    std::vector<int> arr;
    int num;
    while (infile >> num) {
        arr.push_back(num);
    }
    infile.close();

    auto start = std::chrono::high_resolution_clock::now();
    
    arr = sortArray(arr);
    
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
    
    for (size_t i = 0; i < arr.size(); ++i) {
        outfile << arr[i];
        if (i < arr.size() - 1) outfile << " ";
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