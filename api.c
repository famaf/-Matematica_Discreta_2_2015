#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include "helpers.h"
#include "api.h"

struct Vertex_Data
{
    u32 id;
    u32 grado; // Grado del vertice
    u32 *vecinos; // Arreglo de vecinos
    u32 color; // Color del vertice
};

struct GrafoPlus
{
    u32 vertex_count; // Cantidad de vertices del grafo
    u32 edges_count; // Cantidad de lados del grafo
    u32 color_count; // Cantidad de colores del grafo --> "X(G)"
    //u32 orden_ingresado[vertex_count]; // Orden en que se ingresaron los vertices
    //u32 grado_x_vertice[vertex_count]; // Grado (cantidad de vecinos) por vertice
    Vertex *vertex_array; // Estructura que contiene el ID del vertice, sus vecinos
                                               // en un arreglo, y el color del vertice.
} GrafoSt;


u32 id_count = 0;

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
    G -> vertex_array = NULL;

    // ASIGNA TODOS LOS CAMPOS DE LA ESTRUCTURA

    return G;
}


int DestruirGraf(GrapfP G)
{
    u32 i = G->vertex_count;
    u32 j = 0;

    if(G == NULL)
    {
        return 0;
    }
    for(i;i>0;i--){
        free(G->vertex_array[i].vecinos);
    }
    free(G->vertex_array);
    free(G);

    return 1;
    // LIBERA MEMORIA ALOCADA DE LA ESTRUCTURA
}

u32 add_vertex_id(GrapfP G, u32 vertex)
{
    bool exist = false;
    int i = 0;

    while(i<id_count && !exist)
    {
        exist = (G->vertex_array[i].id == vertex);
        i++;
    }

    if(!exist)
    {
        G->vertex_array[i].id = vertex;
        printf("acabo de agregar id\n");
        G->vertex_array[i].grado = 0;
        G->vertex_array[i].color = i;
        id_count += 1;
        return -1;
    }
    else
    {
        return (i-1);
    }
}

void add_neighbor(GrapfP G, u32 neighbor, int pos)
{
    printf("chequeo grado %u\n", G->vertex_array[pos].grado);
    if (G->vertex_array[pos].grado == 0)
    {
        printf("entro if\n");
        G->vertex_array[pos].vecinos = calloc(1, sizeof(u32));
    }
    else
    {
        u32 grado_aux = G->vertex_array[pos].grado;
        G->vertex_array[pos].vecinos = realloc(G->vertex_array[pos].vecinos, (grado_aux+1)*sizeof(u32));
    }
    
    G->vertex_array[pos].vecinos[G->vertex_array[pos].grado] = neighbor;
    G->vertex_array[pos].grado += 1;
    printf("listo agregueee!!!\n");
}



//-----------------------------------------------------------------------------
//                          ESTRUCTURA DIMACS (Falta Modificar)
//-----------------------------------------------------------------------------
static inline char *_non_empty_line(FILE *fd)
{
    assert(fd != NULL);
    char *line = readline(fd);
    while (strlen(line) == 0)
    {
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
    u32 pos1 = 0;
    u32 pos2 = 0;
    u32 vertex_count = 0, edges_count = 0;

    line = _non_empty_line(fd); // line es un buffer, sscanf lee los elemento del buffer

    /* Primera(s) Linea: Si empieza con 'c' se ignora y se pasa a la siguiente */
    while (line[0] == 'c')
    {
        free(line);
        line = _non_empty_line(fd);
    }

    /* Segunda Linea: Debe contener cantidad de vértices y lados */

    scan_result = sscanf(line, "p edge %u %u\n", &vertex_count, &edges_count);

    G->vertex_array = calloc(vertex_count, sizeof(Vertex));

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
        }
        else
        {
            pos1 = add_vertex_id(G, left);
            
            if(pos1 == -1)
            {
                pos1 = id_count-1;
            }
            
            pos2 = add_vertex_id(G, right);
            
            if(pos2 == -1)
            {
                pos2 = id_count-1;
            }
            
            printf("pos1 %i\n", pos1);
            printf("pos2 %i\n", pos2);
            add_neighbor(G, right, pos1);
            add_neighbor(G, left, pos2);
            
            }
    }

    free(line);

    G->vertex_count = vertex_count;
    G->edges_count = edges_count;
    G->color_count = vertex_count;

    return vertex_count;
}
//-----------------------------------------------------------------------------

int ImprimirGrafo(GrapfP G)
{
    u32 i = G->vertex_count;
    u32 grado_aux;
    printf("p edge %u %u\n", i, G->edges_count);
    for(i;i>0;i--){
        grado_aux = G->vertex_array[i].grado;
        for(grado_aux;grado_aux>0;grado_aux--){
            printf("e %u %u\n", G->vertex_array[i].id, G->vertex_array[i].vecinos[grado_aux]);
        }
    }
}

u32 CantidadDeColores(GrapfP G)
{
    return G->color_count;
}

u32 NumeroVerticesDeColor(GrapfP G, u32 i){

    u32 cant_color = 0;
    u32 j = 0;

    for(j;j<G->vertex_count;j++){
        if(G->vertex_array[j].color == i){
            cant_color += 1;
        }
    }
    return cant_color;
}


int ImprimirColor(GrapfP G, u32 i){

}


u32 Greedy(GrapfP G){
    u32 current_color = 1;
    
}











