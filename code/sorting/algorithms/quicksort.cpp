#include <vector>
#include <utility>

int particion(std::vector<int>& arr, int izq, int der){
    int pivot = arr[der];
    int i = izq - 1;
    for (int j = izq; j < der; j++){
        if (arr[j] <= pivot){
            i++;
            std::swap(arr[i], arr[j]);
        }
    }
    std::swap(arr[i + 1], arr[der]);
    return i + 1;
}
void quickSort (std::vector<int>& arr, int izq, int der){
    if (izq < der){
        int pivotIndex = particion(arr, izq, der);
        quickSort(arr, izq, pivotIndex - 1);
        quickSort(arr, pivotIndex + 1, der);
    }
}

std::vector<int> sortArray(std::vector<int>& arr){
    if (!arr.empty()){
        quickSort(arr, 0, arr.size() - 1);
    }
    return arr;
}