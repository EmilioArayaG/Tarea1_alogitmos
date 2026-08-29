#include <vector>
// La funcion merge es la que mezcla las dos mitades
void merge(std::vector<int>& arr, int izq, int med, int der){
    int a1 = med - izq + 1;
    int a2 = der - med;

    std::vector<int> L(a1);
    std::vector<int> R(a2);

    for(int i = 0; i < a1; i++){
        L[i] = arr[izq + i];
    }
    for(int j = 0; j < a2; j++){
        R[j] = arr[med + 1 + j];
    }

    int i = 0;
    int j = 0;
    int k = izq;

    while (i < a1 && j < a2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < a1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < a2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}
//mergesort hace la division de los arreglos recursiva
void mergesort(std::vector<int>& arr, int izq, int der){
    if (izq >= der){
        return;
    }
    int med = izq + (der - izq) / 2;
    mergesort(arr, izq, med);
    mergesort(arr, med + 1, der);
    merge(arr, izq, med, der);
}
std::vector<int> sortArray(std::vector<int>& arr) {
    if (!arr.empty()) {
        mergesort(arr, 0, arr.size() - 1);
    }
    return arr;
}

