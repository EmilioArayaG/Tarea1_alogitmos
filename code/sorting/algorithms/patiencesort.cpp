#include <vector>
#include <stack>
#include <queue>
#include <utility>

std::vector<int> sortArray(std::vector<int>& arr){
    if (arr.empty()) return arr;

    std::vector<std::stack<int>> pilas;
    for (int current : arr) {
        int izquierda = 0;
        int derecha = (int)pilas.size();
        //busqueda binaria para optimizar la formacion de pilas
        while (izquierda < derecha){
            int medio = izquierda + (derecha - izquierda) / 2;
            if (pilas[medio].top() >= current) {
                derecha = medio;
            } else {
                izquierda = medio + 1;
            }
        }
        if (izquierda == (int)pilas.size()){
            std::stack<int> nueva_pila;
            nueva_pila.push(current);
            pilas.push_back(nueva_pila);
        } else {
            pilas[izquierda].push(current);
        }
    }
    //Se crea una cola de prioridad (min-heap): guarda pares de datos (valor, indice pila)
    std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<std::pair<int, int>>> min_heap;
    for(size_t i = 0; i < pilas.size(); i++){
        min_heap.push({pilas[i].top(), i});
    }
    for (size_t i = 0; i < arr.size(); i++){
        auto top_item = min_heap.top();
        min_heap.pop();
        arr[i] = top_item.first;
        int indice_pila = top_item.second;
        pilas[indice_pila].pop();
        if(!pilas[indice_pila].empty()) {
            min_heap.push({pilas[indice_pila].top(), indice_pila});
        }
    }
    return arr;
}