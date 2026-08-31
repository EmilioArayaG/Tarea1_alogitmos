#include <vector>

std::vector<int> sumaMatrix(const std::vector<int>& A, const std::vector<int>& B){
    int total_elem = A.size();
    std::vector<int> C(total_elem);
    for (int i = 0; i < total_elem; i++){
        C[i] = A[i] + B[i];
    }
    return C;
}

std::vector<int> restaMatrix(const std::vector<int>& A, const std::vector<int>& B){
    int total_elem = A.size();
    std::vector<int> C(total_elem);
    for (int i = 0; i < total_elem; i++){
        C[i] = A[i] - B[i];
    }
    return C;
}

std::vector<int> naiveFallback(const std::vector<int>& A, const std::vector<int>& B, int N) {
    std::vector<int> C(N * N, 0);
    for (int i = 0; i < N; ++i) {
        for (int k = 0; k < N; ++k) {
            for (int j = 0; j < N; ++j) {
                C[i * N + j] += A[i * N + k] * B[k * N + j];
            }
        }
    }
    return C;
}

std::vector<int> strassen(const std::vector<int>& A, const std::vector<int>& B, int N) {
    if (N <= 64) {
        return naiveFallback(A, B, N);
    }

    int mitad = N / 2;
    int new_size = mitad * mitad;

    std::vector<int> A11(new_size), A12(new_size), A21(new_size), A22(new_size);
    std::vector<int> B11(new_size), B12(new_size), B21(new_size), B22(new_size);

    for (int i = 0; i < mitad; ++i) {
        for (int j = 0; j < mitad; ++j) {
            int index = i * mitad + j;
            A11[index] = A[i * N + j];
            A12[index] = A[i * N + (j + mitad)];
            A21[index] = A[(i + mitad) * N + j];
            A22[index] = A[(i + mitad) * N + (j + mitad)];

            B11[index] = B[i * N + j];
            B12[index] = B[i * N + (j + mitad)];
            B21[index] = B[(i + mitad) * N + j];
            B22[index] = B[(i + mitad) * N + (j + mitad)];
        }
    }

    std::vector<int> M1 = strassen(sumaMatrix(A11, A22), sumaMatrix(B11, B22), mitad);
    std::vector<int> M2 = strassen(sumaMatrix(A21, A22), B11, mitad);
    std::vector<int> M3 = strassen(A11, restaMatrix(B12, B22), mitad);
    std::vector<int> M4 = strassen(A22, restaMatrix(B21, B11), mitad);
    std::vector<int> M5 = strassen(sumaMatrix(A11, A12), B22, mitad);
    std::vector<int> M6 = strassen(restaMatrix(A21, A11), sumaMatrix(B11, B12), mitad);
    std::vector<int> M7 = strassen(restaMatrix(A12, A22), sumaMatrix(B21, B22), mitad);
    std::vector<int> C11 = sumaMatrix(restaMatrix(sumaMatrix(M1, M4), M5), M7);
    std::vector<int> C12 = sumaMatrix(M3, M5);
    std::vector<int> C21 = sumaMatrix(M2, M4);
    std::vector<int> C22 = sumaMatrix(restaMatrix(sumaMatrix(M1, M3), M2), M6);

    std::vector<int> C(N * N);
    for (int i = 0; i < mitad; ++i) {
        for (int j = 0; j < mitad; ++j) {
            int index = i * mitad + j;
            C[i * N + j] = C11[index];
            C[i * N + (j + mitad)] = C12[index];
            C[(i + mitad) * N + j] = C21[index];
            C[(i + mitad) * N + (j + mitad)] = C22[index];
        }
    }

    return C;
}
std::vector<int> multiply(const std::vector<int>& A, const std::vector<int>& B, int N) {
    return strassen(A, B, N);
}