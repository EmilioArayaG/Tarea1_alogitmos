#include <vector>
#include <utility>

/*
 * Referencias:
 * 1. GeeksforGeeks. "QuickSort Algorithm". 
 *    URL: https://www.geeksforgeeks.org/quick-sort/
 * 2. GeeksforGeeks. "Hoare's vs Lomuto partition scheme in QuickSort".
 *    URL: https://www.geeksforgeeks.org/hoares-vs-lomuto-partition-scheme-quicksort/
 */

int particion(std::vector<int>& arr, int izq, int der) {
    int pivot = arr[izq + (der - izq) / 2];
    
    int i = izq - 1;
    int j = der + 1;

    while (true) {
        do {
            i++;
        } while (arr[i] < pivot);

        do {
            j--;
        } while (arr[j] > pivot);

        if (i >= j) {
            return j;
        }

        std::swap(arr[i], arr[j]);
    }
}

void quickSort(std::vector<int>& arr, int izq, int der) {
    if (izq < der) {
        int pi = particion(arr, izq, der);
        
        quickSort(arr, izq, pi);
        quickSort(arr, pi + 1, der);
    }
}

std::vector<int> sortArray(std::vector<int>& arr) {
    if (!arr.empty()) {
        quickSort(arr, 0, arr.size() - 1);
    }
    return arr;
}