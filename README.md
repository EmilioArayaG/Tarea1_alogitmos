# TAREA 1 INF221 2026-2

## Estructura del Repositorio

Este repositorio contiene la documentación, el código fuente y las instrucciones necesarias para la realización de la Tarea 1 de la asignatura *INF221 Algoritmos y Complejidad*.

**Entrega:** archivo `.zip` vía aula.usm.cl

A continuación, se describe la estructura del repositorio:

```bash
├── assignment_statement
├── code
├── report
└── README.md
```

### `assignment_statement`
Contiene el enunciado de la tarea, así como los archivos fuente del enunciado en formato LaTeX (.tex).

### `code`
Contiene la plantilla de los archivos que deberán estar presentes en la entrega de la tarea. En ella, se deben implementar los algoritmos solicitados, los cuales se detallan a continuación:
- `matrix_multiplication`: Algoritmo de Strassen y versión Naive.
- `sorting`: std::sort, merge sort, quick sort, patience sort.

### `report`
En esta carpeta se encuentra la plantilla en LaTeX para la elaboración del mini-informe correspondiente a la tarea.

***Para obtener información más detallada sobre el contenido de cada carpeta, se recomienda revisar los archivos README ubicados dentro de ellas.***

## Adicional: nombre de los archivos de salida

El enunciado especifica que la salida se escriba en `{n}_{t}_{d}_{m}_out.txt`. En este
proyecto se agregó el nombre del algoritmo al final del identificador:

```bash
{n}_{t}_{d}_{m}_{algoritmo}_out.txt    # salidas
{n}_{t}_{d}_{m}_{algoritmo}_meas.txt   # mediciones
```

donde `{algoritmo}` es `merge`, `quick`, `patience` o `std` en ordenamiento, y `naive` o
`strassen` en multiplicación de matrices.

El motivo es que cada entrada se procesa con todos los algoritmos: sin ese sufijo, las
ejecuciones sucesivas de `make run` escribirían sobre el mismo archivo y sólo quedaría la
salida y la medición del último algoritmo ejecutado. Los nombres de los archivos de
**entrada** sí respetan exactamente el formato del enunciado.
