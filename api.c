#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <assert.h>
#include "api.h"


struct GrafoPlus
{
    u32 vertex_count;
    u32 edge_count;
    CamAux vecinos[vertex_count];
} GrafoSt;


struct Campos_Auxiliares
{
    u32 identificador;
    u32 *vecinos[]; // ESTE SERIA EL ARREGLO DE VECINOS DE CADA VERTICE, DECLARAR BIEN
    u32 orden_ingresado[vertex_count];
    u32 grado_x_vertice[vertex_count]
} CamAux;


//-----------------------------------------------------------------------------
GrapfP NuevoGraf()
{
    GrapfP G = calloc(1, sizeof(GrafoSt));

    // ASIGNA TODOS LOS CAMPOS DE LA ESTRUCTURA

    return G;
}


int DestruirGraft(Grapfp G)
{
    assert(G != NULL);

    // LIBERA MEMORIA ALOCADA DE LA ESTRUCTURA
}


int LeerGrafo(GrapfP G)
{
    //ESTRUCTURA DIMACS QUE HICIMOS EN TAD dimacs.c
}


int ImprimirGrafo(GrapfP G)
{
    // IMPLEMENTAR
}


int ImprimirColor(GrapfP G, u32 i)
{
    // IMPLEMENTAR
}


u32 CantidadDeColores(GrapfP G)
{

}
//-----------------------------------------------------------------------------

/*
struct ESTRUCTURA
{
    int identificador;
    unsigned  int *vecinos;
    unsigned int orden_ingresado[vertices_count];
    unsigned int grado_x_vertice[vertices_count]
};

typedef struct Grafoplus
{
    unsigned int vertices_count;
    unsigned int edges_count;
    ESTRUCTURA lista_vertices[vertices_count];
} GrafoSt;

*/
