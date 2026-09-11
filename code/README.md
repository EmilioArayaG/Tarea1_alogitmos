# Documentación del código

Este directorio contiene las implementaciones y herramientas utilizadas en la Tarea 1 de **INF-221 Algoritmos y Complejidad**, correspondiente al semestre 2026-2.

El proyecto estudia experimentalmente cuatro algoritmos de ordenamiento y dos algoritmos de multiplicación de matrices. Para cada implementación se mide el tiempo de ejecución y la memoria residente máxima del proceso.

## Requisitos

- Sistema Linux o Windows Subsystem for Linux 2 (WSL2).
- `g++` con soporte para C++17.
- GNU Make.
- Python 3.
- Bibliotecas de Python: `numpy`, `pandas` y `matplotlib`.

Los programas en C++ se compilan con las opciones:

```text
-std=c++17 -O3 -Wall
```

Las dependencias de Python se pueden instalar mediante:

```bash
python3 -m pip install numpy pandas matplotlib
```

## Estructura

```text
code/
├── matrix_multiplication/
│   ├── algorithms/
│   ├── data/
│   │   ├── matrix_input/
│   │   ├── matrix_output/
│   │   ├── measurements/
│   │   └── plots/
│   ├── scripts/
│   ├── makefile
│   └── matrix_multiplication.cpp
├── sorting/
│   ├── algorithms/
│   ├── data/
│   │   ├── array_input/
│   │   ├── array_output/
│   │   ├── measurements/
│   │   └── plots/
│   ├── scripts/
│   ├── makefile
│   └── sorting.cpp
└── README.md
```

## Multiplicación de matrices

Se implementaron los algoritmos Naive y Strassen. Ambos multiplican matrices cuadradas de enteros de dimensión `N × N` y se compilan como programas independientes.

Las matrices se almacenan por filas en un único `std::vector<int>` de largo `N²`. El elemento ubicado en la fila `i` y columna `j` se encuentra en la posición `i * N + j`. Ambas implementaciones proporcionan la función `multiply(A, B, N)`, que es invocada por el mismo programa principal.

### Algoritmos

- `algorithms/naive.cpp`: implementa la multiplicación tradicional mediante tres ciclos anidados, con complejidad temporal `O(N³)`. Los ciclos siguen el orden `i-k-j` para favorecer el acceso secuencial a las matrices almacenadas por filas.
- `algorithms/strassen.cpp`: implementa el algoritmo de Strassen mediante división y conquista, con complejidad temporal teórica aproximada `O(N^2.81)`. Cada matriz se divide en cuatro bloques y se calculan siete productos recursivos. La implementación evaluada utiliza recursión pura hasta alcanzar matrices de `1 × 1`; no emplea un umbral híbrido con el algoritmo tradicional. Se supone que `N` es una potencia de dos, condición que cumplen todos los casos de prueba de la tarea.

### Programa principal

`matrix_multiplication.cpp` recibe cuatro argumentos:

```bash
./matrix_naive <matriz_A.txt> <matriz_B.txt> <salida.txt> <medicion.txt>
```

También puede ejecutarse la versión de Strassen:

```bash
./matrix_strassen <matriz_A.txt> <matriz_B.txt> <salida.txt> <medicion.txt>
```

El programa realiza las siguientes operaciones:

1. Lee las dos matrices de entrada.
2. Verifica que contengan la misma cantidad de elementos y que representen matrices cuadradas.
3. Deduce `N` a partir de la cantidad de elementos.
4. Mide la ejecución de `multiply(A, B, N)` mediante `<chrono>`.
5. Obtiene la memoria residente máxima del proceso mediante `getrusage()`.
6. Escribe la matriz resultante y el archivo de medición.

La lectura de las matrices y la escritura de los resultados quedan fuera del intervalo cronometrado. Cada archivo de medición contiene una línea con el siguiente formato:

```text
tiempo_ms memoria_kb
```

### Compilación y ejecución

Desde `code/matrix_multiplication/`:# Documentación

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
