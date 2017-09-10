#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "API.h"

#define MIN(x, y) x<y?x:y // Macro para calcular el minimo entre dos elementos
#define Nv 10 // Constante que expresa el numero de veces que se ejecutara Greddy


// Funcion que colorea un grafo segun el algoritmo de WelshPowell
u32 WelshPowell(GrafP G) {
    u32 coloreo = 0;

    OrdenWelshPowell(G);

    coloreo = Greedy(G);

    return coloreo;
}


int main() {
    int check = 0; // Variable que chequea si la entrada del grafo es correcta o no
    u32 coloreo = 0; // Varible que guarda el mejor coloreo entre los algoritmos
    u32 coloreo_G = 0; // Variable que contiene el coloreo obtenido con el algoritmo de Greedy
    u32 coloreo_WP = 0; // Variable que contiene el coloreo obtenido con el algoritmo de Welsh Powell
    u32 coloreo_D = 0; // Variable que contiene el coloreo obtenido con el algoritmo de DSATUR
    u32 porcentaje = 0; // Variable que contiene el valor aleatorio, para la eleccion de algun ordenamiento de los vertices
    u32 i; // Varible que aumentara hasta llegar a Nv

    GrafP G = NuevoGraf(); // Creamos un nuevo grafo, nueva estructura.

    check = LeerGrafo(G);

    printf("\n");

    // Chequeamos que si la cantidad de vertices es 0
    if (check == 0) {
        printf("X(G) = 1\n");
        return 0;
    }
    // Si ocurrio un error en la lectura cortamos la execucion del programa
    else if (check == -1) {
        printf("Ocurrio un error en la lectura del grafo\n");
        return 1;
    }

    coloreo_D = DSATUR(G);

    // Si la cantidad de colores es 2, entonces el grafo es bipartito, y terminamos el programa
    if (coloreo_D == 2) {
        printf("Grafo Bipartito\n");
        return 0;
    }

    coloreo_WP = WelshPowell(G);

    printf("WelshPowell: Colores Usados: %u\n", coloreo_WP);

    coloreo_D = DSATUR(G);

    printf("DSATUR: Colores Usados: %u\n", coloreo_D);

    // Si alguno de los coloreos es 3 entonces mostramos eso por stdout y terminamos el programa
    if (coloreo_WP == 3 || coloreo_D == 3) {
        printf("X(G) = 3\n");
        return 0;
    }

    coloreo = MIN(coloreo_WP, coloreo_D); // Guardamos el mejor coloreo entre Welsh Powell y DSATUR

    srand(time(NULL)); // Sirve para que durante las ejecuciones los numeros aleatorios no sean los mismos

    porcentaje = rand() % 101; // Numero aleatorio entre 0 y 100

    for (i = 0; i < Nv; i++) {
        // Si porcentaje esta entre [4 ... 10], se ordenara los vertices de forma aleatoria
        if (porcentaje >= 4 && porcentaje <= 10) {
            OrdenAleatorio(G);
            coloreo_G = Greedy(G);
        }
        // Si porcentaje esta entre [51 ... 75], se ordenara los vertices de acuerdo a ChicoGrande
        else if (porcentaje > 50 && porcentaje <= 75) {
            ChicoGrande(G);
            coloreo_G = Greedy(G);
        }
        // Si porcentaje esta entre [76 ... 100], se ordenara los vertices de acuerdo a GrandeChico
        else if (porcentaje > 75 && porcentaje <= 100) {
            GrandeChico(G);
            coloreo_G = Greedy(G);
        }
        // Si porcentaje esta entre [11 ... 50], se ordenara los vertices de acuerdo a Revierte
        else {
            Revierte(G);
            coloreo_G = Greedy(G);
        }

        coloreo = MIN(coloreo, coloreo_G); // Guardo el mejor coloreo

        porcentaje = rand() % 101; // Calculo un nuevo numero aleatorio entre 0 y 100
    }

    printf("Mejor coloreo con Greedy iterado %u veces es: %u colores\n", Nv, coloreo);

    DestruirGraf(G); // Destruyo el grafo

    printf("\n");

    return 0;
}
