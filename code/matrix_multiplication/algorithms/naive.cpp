#include <vector>

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