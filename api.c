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
    u32 id; // Nombre del Vertice
    u32 grado; // Grado del vertice
    u32 color; // Color del vertice
    u32 *vecinos; // Arreglo de vecinos
};

struct GrafoPlus
{
    u32 vertex_count; // Cantidad de vertices del grafo
    u32 edges_count; // Cantidad de lados del grafo
    u32 color_count; // Cantidad de colores del grafo --> "X(G)"
    Vertex *vertex_array; // Arreglo de Estructura Vertex
} GrafoSt;


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
    u32 i = 0;
    u32 j = 0;

    if(G == NULL)
    {
        return 0;
    }
    
    for(i; i < G->vertex_count; i++)
    {
        free(G->vertex_array[i].vecinos);
    }

    free(G->vertex_array);

    free(G);

    return 1;
    // LIBERA MEMORIA ALOCADA DE LA ESTRUCTURA
}

unsigned int contador = 0; // Variable Global que me dice hasta cuanto esta lleno el arreglo vertex_array

void add_vertex_id_color_grado(GrapfP G, u32 vertex)
{
    bool existe = false;
    unsigned int i = 0;
    
    while(i < contador && existe == false)
    {
        if (vertex == G->vertex_array[i].id) // Vertice esta en el array => aumento grado
        {
            G->vertex_array[i].grado ++;
            existe = true;
        }

        i++;
    }

    if(existe == false) // Si el vertice no esta en el array
    {
        G->vertex_array[i].id = vertex;
        G->vertex_array[i].grado = 1;
        G->vertex_array[i].color = (i + 1);

        contador ++;
    }
}

// Guardamos en vecinos la posición en donde está el vértice vecino.
void add_vecino(GrapfP G, u32 vertex_1, u32 vertex_2)
{
    bool existe = false;
    bool find1 = false;
    bool find2 = false;
    unsigned int i = 0;
    unsigned int j = 0;
    u32 pos1 = 0;
    u32 pos2 = 0;

    while (i < G->vertex_count && !(find1 && find2))
    {
        if (G->vertex_array[i].id == vertex_1)
        {
            pos1 = i;
            find1 = true;
        }
        if(G->vertex_array[i].id == vertex_2)
        {
            pos2 = i;
            find2 = true;
        }
        i++;
    }

    while (j < G->vertex_array[pos1].grado && !existe)
    {
        if (G->vertex_array[pos1].vecinos[j] == 0)
        {
            G->vertex_array[pos1].vecinos[j] = pos2;
            existe = true;
        }
        j++;
    }

    j = 0;
    existe = false;
    while (j < G->vertex_array[pos2].grado && !existe)
    {
        if (G->vertex_array[pos2].vecinos[j] == 0)
        {
            G->vertex_array[pos2].vecinos[j] = pos1;
            existe = true;
        }
        j++;
    }
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
    u32 vertex_count = 0, edges_count = 0;

//---------------------PRIMERA RECORIDA ----------------------------------

    line = _non_empty_line(fd); // line es un buffer, sscanf lee los elemento del buffer

    /* Primera(s) Linea: Si empieza con 'c' se ignora y se pasa a la siguiente */
    while (line[0] == 'c')
    {
        free(line);
        line = _non_empty_line(fd);
    }

    /* Segunda Linea: Debe contener cantidad de vértices y lados */

    scan_result = sscanf(line, "p edge %u %u\n", &vertex_count, &edges_count);

    G->vertex_count = vertex_count;
    //printf("G->vertex_count = %u\n", G->vertex_count);
    G->edges_count = edges_count;
    //printf("G->edges_count = %u\n", G->edges_count);
    G->color_count = vertex_count;
    //printf("G->color_count = %u\n", G->color_count);

    //printf("Calloc para el tamaño del array de vertice\n");
    G->vertex_array = calloc(vertex_count, sizeof(Vertex)); // Tamaño del arreglo de Vertex

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
            add_vertex_id_color_grado(G, left);
            add_vertex_id_color_grado(G, right);
        }
    }

    // Asigno memoria a cada vertice segun su grado;
    for(unsigned int j = 0; j < G->vertex_count; j++)
    {
        G->vertex_array[j].vecinos = calloc(G->vertex_array[j].grado, sizeof(u32));
    }
/*    for(unsigned int j = 0; j < G->vertex_count; j++)
    {
        printf("Vertices que tengo: %u, grado: %u\n", G->vertex_array[j].id, G->vertex_array[j].grado);
    }*/

    free(line);

    printf("Antes de fseek\n");
    fseek(fd, 0, 0); // Vuelvo a principio de archivo
    printf("Despues de fseek\n");
//---------------------SEGUNDA RECORIDA ----------------------------------

    line = _non_empty_line(fd); 

    // Primera(s) Linea: Si empieza con 'c' se ignora y se pasa a la siguiente
    while (line[0] == 'c')
    {
        free(line);
        line = _non_empty_line(fd);
    }

    //free(line);

    // Segunda Linea: Debe contener cantidad de vértices y lados

    scan_result = sscanf(line, "p edge %u %u\n", &vertex_count, &edges_count);

    free(line);

    for (unsigned int i = 0; i < edges_count; i++)
    {
        unsigned int left = 0, right = 0;

        line = _non_empty_line(fd);

        scan_result = sscanf(line, "e %u %u", &left, &right);

        add_vecino(G, left, right);
    }

    // for(unsigned int j = 0; j < G->vertex_count; j++)
    // {
    //     printf("Vertice: '%u', grado = %u\n", G->vertex_array[j].id, G->vertex_array[j].grado);
    //     for(unsigned int t = 0; t < G->vertex_array[j].grado; t++)
    //     {
    //         printf("    los vecinos de el vertice '%u': %u\n", G->vertex_array[j].id, G->vertex_array[G->vertex_array[j].vecinos[t]].id);
    //     }
    // }

    free(line);

    return vertex_count;
}
//-----------------------------------------------------------------------------

int ImprimirGrafo(GrapfP G)
{
    u32 i = 0;
    u32 j = 0;
    u32 k = 0;
    u32 grado_aux;
    bool impreso;

    printf("p edge %u %u\n", G->vertex_count, G->edges_count);
    for(i=0 ;i < G->vertex_count; i++)
    {
        grado_aux = G->vertex_array[i].grado;
        for(k=0;k<grado_aux;k++)
        {
            impreso = false;
            j = 0;
            while(j<i && !impreso)
            {
                if(j == G->vertex_array[i].vecinos[k]){
                    impreso = true;
                }
                j++;
            }
            if(!impreso){
                printf("e %u %u\n", G->vertex_array[i].id, G->vertex_array[G->vertex_array[i].vecinos[k]].id);
            }
        }

    }
}


u32 CantidadDeColores(GrapfP G)
{
    return G->color_count;
}


u32 NumeroVerticesDeColor(GrapfP G, u32 i)
{

    u32 cantidad_vertex_color = 0;
    u32 iterator = 0;

    for(iterator; iterator < G->vertex_count; iterator++)
    {
        if(G->vertex_array[iterator].color == i)
        {
            cantidad_vertex_color ++;;
        }
    }

    return cantidad_vertex_color;
}


u32 ImprimirColor(GrapfP G, u32 i)
{
    u32 iterator = 0;
    u32 cantidad_vertex_color = 0;
    bool find = false;
    for (iterator; iterator < G->vertex_count; iterator++)
    {
        if (G->vertex_array[iterator].color == i)
        {
            if (!find)
            {
                printf("Vertices de Color %u: ", i);
                printf("%u", G->vertex_array[iterator].id);
            }
            else
            {
                printf(", %u", G->vertex_array[iterator].id);
            }
            
            find = true;
            cantidad_vertex_color ++;
        }
    }

    if (!find)
    {
        printf("No hay vertices de color %u", i);
    }

    printf(".\n");

    return cantidad_vertex_color;
}


// u32 Greedy(GrapfP G)
// {
//     u32 current_color = 1;
//     for(i=0;i < G->vertex_count; i++)
//     {
//         for(j=i;j>0;j--)
//         {

//         }
//     }
// }











