# Documentación

## Entrega

La entrega se realiza vía **aula.usm.cl** en formato `.zip`.

## Multiplicación de matrices

Algoritmos: Naive, Strassen.

Ambos multiplican dos matrices cuadradas de enteros de N x N y se compilan por separado. Las matrices se guardan en un único `std::vector<int>` de largo N^2 ordenado por filas, de modo que el elemento (i,j) está en la posición `i * N + j`. Cada algoritmo entrega la misma función `multiply(A, B, N)`, y el programa principal se enlaza con uno u otro.

- `algorithms/naive.cpp`: triple ciclo anidado, O(N^3). Los ciclos se recorren en orden `i-k-j` para leer ambas matrices por filas y aprovechar la caché.
- `algorithms/strassen.cpp`: método recursivo de división y conquista, O(N^2.81). Divide cada matriz en cuatro bloques, calcula los siete productos M1, ..., M7 y recompone el resultado. Por debajo de N = 64 cambia al método tradicional, porque a esa escala el costo de crear las submatrices es mayor que el ahorro de una multiplicación. Asume que N es potencia de 2, lo que se cumple para todos los casos de prueba.

### Programa principal

`matrix_multiplication.cpp` recibe cuatro argumentos: las dos matrices de entrada, el archivo de salida y el archivo de mediciones.

```bash
./matrix_naive <matriz_A.txt> <matriz_B.txt> <output.txt> <measurements.txt>
```

Lee ambas matrices, deduce N a partir de la cantidad de números leídos, verifica que la matriz sea cuadrada y llama a `multiply()`. El cronómetro (`<chrono>`) mide **solo** esa llamada: la lectura y la escritura de archivos quedan fuera. Luego registra la memoria residente máxima del proceso con `getrusage()`, escribe la matriz resultante en `data/matrix_output/` y una línea `tiempo_ms memoria_kb` en `data/measurements/`.

Compilación y ejecución con el `makefile`:

```bash
make          # genera los ejecutables matrix_naive y matrix_strassen
make run      # ejecuta ambos algoritmos sobre todos los pares de data/matrix_input/
make clean    # borra los ejecutables
```

### Scripts

Ambos se ejecutan desde el directorio `scripts/`, ya que usan rutas relativas.

- `matrix_generator.py`: genera los 144 archivos de entrada en `data/matrix_input/`, con el formato `{n}_{t}_{d}_{m}_1.txt` y `{n}_{t}_{d}_{m}_2.txt`, donde `n` ∈ {16, 64, 256, 1024}, `t` ∈ {densa, dispersa, diagonal}, `d` ∈ {D0, D10} y `m` ∈ {a, b, c}. Las matrices dispersas tienen cerca de un 10% de elementos no nulos y las diagonales solo la diagonal principal.
- `plot_generator.py`: lee todos los archivos de `data/measurements/`, promedia las tres muestras de cada configuración y guarda 12 gráficos PNG en `data/plots/`: `tiempo_{t}_{d}.png` y `memoria_{t}_{d}.png`. Ambos ejes en escala logarítmica.

## Ordenamiento de arreglo unidimensional

Algoritmos: MergeSort, QuickSort, PatienceSort, std::sort.

Cada algoritmo está en su propio archivo y entrega la misma función `sortArray(arr)` sobre un `std::vector<int>`, de modo que el programa principal se enlaza con uno u otro.

- `algorithms/mergesort.cpp`: divide el arreglo por la mitad, ordena cada mitad y las fusiona usando dos vectores auxiliares. O(N log N) en todos los casos.
- `algorithms/quicksort.cpp`: partición de **Hoare** con pivote central. Se usa este esquema y no el de Lomuto porque, con arreglos de muchos elementos repetidos (dominio D1 con N = 10^7), Lomuto deja todos los valores iguales al pivote en una sola partición, degenera a O(N^2) y desborda la pila de recursión.
- `algorithms/patiencesort.cpp`: reparte los elementos en pilas mediante búsqueda binaria sobre los topes y luego fusiona todas las pilas con una cola de prioridad. Su costo depende del número de pilas que genere la entrada, no solo de N.
- `algorithms/sort.cpp`: llamada directa a `std::sort` de la STL, incluida como referencia de comparación.

### Programa principal

`sorting.cpp` recibe tres argumentos: el arreglo de entrada, el archivo de salida y el archivo de mediciones.

```bash
./sorting_merge <input.txt> <output.txt> <measurements.txt>
```

Funciona igual que el de matrices: lee el arreglo, cronometra **solo** la llamada a `sortArray()`, registra la memoria residente máxima con `getrusage()`, escribe el arreglo ordenado en `data/array_output/` y una línea `tiempo_ms memoria_kb` en `data/measurements/`.

Compilación y ejecución con el `makefile`:

```bash
make          # genera sorting_merge, sorting_quick, sorting_patience y sorting_std
make run      # ejecuta los cuatro algoritmos sobre todos los archivos de data/array_input/
make clean    # borra los ejecutables
```

### Scripts

Ambos se ejecutan desde el directorio `scripts/`, ya que usan rutas relativas.

- `array_generator.py`: genera los 72 archivos de entrada en `data/array_input/`, con el formato `{n}_{t}_{d}_{m}.txt`, donde `n` ∈ {10, 10^3, 10^5, 10^7}, `t` ∈ {ascendente, descendente, aleatorio}, `d` ∈ {D1, D7} y `m` ∈ {a, b, c}. D1 usa valores en {0, ..., 9} y D7 en {0, ..., 10^7}.
- `plot_generator.py`: lee todos los archivos de `data/measurements/`, promedia las tres muestras de cada configuración y guarda 12 gráficos PNG en `data/plots/`: `tiempo_{t}_{d}.png` y `memoria_{t}_{d}.png`. Ambos ejes en escala logarítmica.

## Dependencias

- **C++**: `g++` con soporte para C++17 (se compila con `-std=c++17 -O3 -Wall`).
- **Python 3**: `numpy`, `pandas` y `matplotlib`.

```bash
pip install numpy pandas matplotlib
```

## Orden de ejecución

```bash
cd sorting/scripts && python3 array_generator.py   # genera las entradas
cd .. && make run                                  # mide tiempo y memoria
cd scripts && python3 plot_generator.py            # genera los gráficos
```

El mismo orden aplica a `matrix_multiplication/` usando `matrix_generator.py`.
