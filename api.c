#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "helpers.h"
#include "api.h"


struct GrafoPlus
{
    u32 vertex_count; // Cantidad de vertices del grafo
    u32 edges_count; // Cantidad de lados del grafo
    u32 color_count; // Cantidad de colores del grafo --> "X(G)"
    //u32 orden_ingresado[vertex_count]; // Orden en que se ingresaron los vertices
    //u32 grado_x_vertice[vertex_count]; // Grado (cantidad de vecinos) por vertice
    CamAux content[vertex_count]; // Estructura que contiene el ID del vertice, sus vecinos
                                               // en un arreglo, y el color del vertice.
} GrafoSt;


struct Campos_Auxiliares
{
    u32 grado; // Grado del vertice
    u32 *vecinos; // Arreglo de vecinos
    u32 color; // Color del vertice
} CamAux;


//-----------------------------------------------------------------------------
GrapfP NuevoGraf()
{
    GrapfP G = calloc(1, sizeof(GrafoSt));

    if (G == NULL)
    {
        return NULL;
    }

    G -> vertex_count = 0;
    G -> edges_count  = 0;
    G -> color_count = 0;

    // ASIGNA TODOS LOS CAMPOS DE LA ESTRUCTURA

    return G;
}


int DestruirGraf(GrapfP G)
{
    if(G == NULL)
    {
        return 0;
    }

    free(G);

    return 1;
    // LIBERA MEMORIA ALOCADA DE LA ESTRUCTURA
}


u32 *translation_table;
uint table_count = 0;
int add_translation_table(u32 vertex){
    bool exist = false;
    int i = 0;
    if(translation_table == NULL)
    {
        translation_table=malloc(1, vertex_count*sizeof(u32));
    }
    while(i<table_count && !exist) {
        exist = (translation_table[i] == vertex);
        i++;
    }
    if(!exist){
        translation_table[table_count] = vertex;
        table_count += 1;
        return table_count - 1;
    }else{
        return i;
    }
}

void add_neighbor(u32 vertex, u32 neighbor, int pos){
    u32 grado_aux = G->content[pos]->grado;
    if (G->content[pos]->vecinos == NULL) {
        G->content[pos]->vecinos = malloc(1, sizeof(u32));
    }else{
        G->content[pos]->vecinos = realloc(G->content[pos]->vecinos[grado_aux], (grado_aux+1)*sizeof(u32));
    }
    G->content[pos]->vecinos[grado_aux] = neighbor;
    G->content[pos]->grado += 1;
}

//-----------------------------------------------------------------------------
//                          ESTRUCTURA DIMACS (Falta Modificar)
//-----------------------------------------------------------------------------
static inline char *_non_empty_line(FILE *fd) {
    assert(fd != NULL);
    char *line = readline(fd);
    while (strlen(line) == 0){
        free(line);
        line = readline(fd);
    }
    return(line);
}


int LeerGrafo(GrapfP G) 
{
    //assert(fd != NULL);
    FILE *fd = NULL;
    fd = stdin;
    int scan_result = 0;
    char *line = NULL;
    int pos1 = 0;
    int pos2 = 0;
    unsigned int vertex_count = 0, edges_count = 0;

    line = _non_empty_line(fd); // line es un buffer, sscanf lee los elemento del buffer

    /* Primera(s) Linea: Si empieza con 'c' se ignora y se pasa a la siguiente */
    while (line[0] == 'c')
    {
        free(line);
        line = _non_empty_line(fd);
    }

    /* Segunda Linea: Debe contener cantidad de vértices y lados */

    scan_result = sscanf(line, "p edge %u %u\n", &vertex_count, &edges_count);
    
    free(line);
    
    if (scan_result != 2)
    {
        return -1;
    }

    /* siguiente linea edges_count debe ser aristas */
    for (unsigned int i = 0; i < edges_count; i++)
    {
        unsigned int left = 0, right = 0;

        line = _non_empty_line(fd);

        scan_result = sscanf(line, "e %u %u", &left, &right);

        if (left == right || scan_result != 2)
        {
            return -1;
        }else{
            pos1 = add_translation_table(left);
            pos2 = add_translation_table(right);
            add_neighbor(right, pos1);
            add_neighbor(left, pos2);
            }
        }

        free(line);


    }

    G -> vertex_count = vertex_count;
    G -> edges_count = edges_count;

    return vertex_count;
}
//-----------------------------------------------------------------------------

/*int ImprimirGrafo(GrapfP G)
{
    // IMPLEMENTAR
}


int ImprimirColor(GrapfP G, u32 i)
{
    // IMPLEMENTAR
}


u32 CantidadDeColores(GrapfP G)
{

}*/
//-----------------------------------------------------------------------------

