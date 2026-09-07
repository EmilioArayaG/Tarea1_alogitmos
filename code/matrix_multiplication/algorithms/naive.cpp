#include <vector>

/*
 * Referencias:
 * 1. GeeksforGeeks. "C++ Program to Multiply Two Matrices". 
 *    URL: https://www.geeksforgeeks.org/cpp-program-to-multiply-two-matrices/
 */

std::vector<int> matrixMultiplication(const std::vector<int>& A, const std::vector<int>& B, int N){
    std::vector<int> C(N * N, 0);

    for(int i = 0; i < N; i++){
        for(int k = 0; k < N; k++){
            for(int j = 0; j < N; j++){
                C[i * N + j] += A[i * N + k] * B[k * N + j];
            }
        }
    }
    return C;
}
std::vector<int> multiply(const std::vector<int>& A, const std::vector<int>& B, int N) {
    return matrixMultiplication(A, B, N);
}