import os
import pandas as pd
import matplotlib.pyplot as plt

# referencias:
# no se usaron referencias externas para este script

meas_dir = "../data/measurements"
plots_dir = "../data/plots"

datos = []
for archivo in os.listdir(meas_dir):
    if archivo.endswith("_meas.txt"):
        partes = archivo.replace("_meas.txt", "").split("_")
        if len(partes) == 5:
            n = int(partes[0])
            tipo = partes[1]
            dominio = partes[2]
            muestra = partes[3]
            algo = partes[4]

            ruta = os.path.join(meas_dir, archivo)
            try:
                with open(ruta, "r") as f:
                    linea = f.read().strip().split()
                    tiempo = float(linea[0])
                    memoria = float(linea[1])
                    datos.append([n, tipo, dominio, muestra, algo, tiempo, memoria])
            except Exception as e:
                print(f"Error leyendo {archivo}: {e}")

df = pd.DataFrame(datos, columns=["N", "Tipo", "Dominio", "Muestra", "Algoritmo", "Tiempo", "Memoria"])

if df.empty:
    print("No se encontraron datos. Verifica la carpeta measurements.")
    exit()

df_promedio = df.groupby(["N", "Tipo", "Dominio", "Algoritmo"]).mean(numeric_only=True).reset_index()

os.makedirs(plots_dir, exist_ok=True)
tipos = df_promedio["Tipo"].unique()
dominios = df_promedio["Dominio"].unique()

def generar_grafico(subset, metrica, titulo, etiqueta_y, nombre_plot):
    plt.figure(figsize=(10, 6))

    for algo in subset["Algoritmo"].unique():
        data_algo = subset[subset["Algoritmo"] == algo].sort_values("N")
        plt.plot(data_algo["N"], data_algo[metrica], marker='o', linewidth=2, label=algo.capitalize())

    plt.xscale('log')
    plt.yscale('log')
    plt.title(titulo)
    plt.xlabel("Tamaño del Arreglo (N)")
    plt.ylabel(etiqueta_y)
    plt.legend(title="Algoritmos")
    plt.grid(True, which="both", linestyle="--", linewidth=0.5)

    plt.savefig(os.path.join(plots_dir, nombre_plot), bbox_inches='tight')
    plt.close()

for t in tipos:
    for d in dominios:
        subset = df_promedio[(df_promedio["Tipo"] == t) & (df_promedio["Dominio"] == d)]
        if subset.empty: continue

        generar_grafico(subset, "Tiempo",
                        f"Tiempo de Ejecución - Arreglo {t.capitalize()} (Dominio {d})",
                        "Tiempo de Ejecución Promedio (ms)",
                        f"tiempo_{t}_{d}.png")

        generar_grafico(subset, "Memoria",
                        f"Memoria Residente Máxima - Arreglo {t.capitalize()} (Dominio {d})",
                        "Memoria Residente Máxima Promedio (KB)",
                        f"memoria_{t}_{d}.png")
