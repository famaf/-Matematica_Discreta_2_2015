#ifndef API_H
#define API_H


/**************************************************
            API de coloreo de grafos
Integrantes:
------------

    * Mario Ferreyra
      E-mail: marioezequiel.ferreyra@yahoo.com.ar

    * Alan Bracco
      E-mail: internetagb@gmail.com

**************************************************/


#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>


/**************************************************
                    REFERENCIAS                    
* A < B : A es menor a B
* A > B : A es mayor a B
* A <= B : A es menor o igual a B
* A >= B : A es mayor o igual a B

**************************************************/


typedef uint32_t u32; // Especifica un entero sin signo de 32 bits 


typedef struct GrafoPlus *GrafP; // Puntero a la estructura del Grafo


typedef struct Vertex_Data *Vertex; // Puntero a la estructura de cada vertice


GrafP NuevoGraf();
/*
    Aloca memoria e inicializa la estructura del grafo y devuelve un puntero a esta.
    En caso de error, la funcion devolvera un puntero a NULL.
*/


int DestruirGraf(GrafP G);
/*
    Destruye la estructura del grafo y libera la memoria alocada.
    Retorna 1 si todo anduvo bien y 0 si no.
*/


int LeerGrafo(GrafP G);
/*
    Lee un grafo desde standard input en el formato DIMACS.
    Devuelve la cantidad de vertices del grafo si la lectura se completa sin problema y -1 si no.
*/


int ImprimeGrafo(GrafP G);
/*
    Imprime en standard output una serie de lineas de acuerdo al formato DIMACS que describan el grafo.
    Devuelve 1 si todo anduvo bien, 0 si hubo algun problema.
*/


u32 NumeroVerticesDeColor(GrafP G, u32 i);
/*
    Retorna el numero de vertices de color 'i'.
*/


u32 ImprimirColor(GrafP G, u32 i);
/*
    Imprime una linea que dice “Vertices de Color i:” y a continuacion una lista de los vertices que
    tienen el color 'i', separados por comas y con un punto luego del ultimo color.

    Por ejemplo: Vertices de Color 3: 15,17,1.

    Los vertices no tienen porque estar ordenados.
    Si no hay vertices de color i imprime “No hay vertices de color i”
    Retorna el numero de vertices de color i.
*/


u32 CantidadDeColores(GrafP G);
/*
    Devuelve la cantidad de colores usados en el coloreo del grafo.
*/


u32 Greedy(GrafP G);
/*
    Corre greedy en el grafo con el orden que se tiene.
    Devuelve el numero de colores que se obtiene.
*/


void OrdenWelshPowell(GrafP G);
/*
    Ordena los vertices del grafo de acuerdo con el orden Welsh-Powell
*/


u32 DSATUR(GrafP G);
/*
    Corre DSATUR en el grafo.
    Devuelve el numero de colores que se obtiene.
*/


void GrandeChico(GrafP G);
/*
    Si G esta coloreado con r colores y W1 son los vertices coloreados con 1, W2 los coloreados con 2, etc,
    entonces esta funcion ordena los vertices poniendo primero los vertices de Wj1 (en algun orden)
    luego los de Wj2 (en algun orden), etc, donde j1, j2, ... son tales que |Wj1| >= |Wj2| >= ... >= |Wjr|.
*/


void ChicoGrande(GrafP G);
/*
    Si G esta coloreado con r colores y W1 son los vertices coloreados con 1, W2 los coloreados con 2, etc,
    entonces esta funcion ordena los vertices poniendo primero los vertices de Wj1 (en algun orden)
    luego los de Wj2 (en algun orden), etc, donde j1, j2, ... son tales que |Wj1| <= |Wj2| <= ... <= |Wjr.
*/


void Revierte(GrafP G);
/*
    Si G esta coloreado con r colores y W1 son los vertices coloreados con 1, W2 los coloreados con 2, etc,
    entonces esta funcion ordena los vertices poniendo primero los vertices de Wr (en algun orden)
    luego los de Wr−1 (en alg´un orden), etc.
*/


void OrdenAleatorio(GrafP G);
/*
    Si G esta coloreado con r colores y W1 son los vertices coloreados con 1, W2 los coloreados con 2, etc,
    entonces esta funcion ordena los vertices poniendo primero los vertices de Wj1 (en algun orden)
    luego los de Wj2 (en algun orden), etc, donde j1, j2, ... son aleatorios (pero distintos).
*/


#endif
