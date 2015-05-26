#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>
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
    u32 i;

    if(G == NULL)
    {
        return 0;
    }
    
    for(i = 0; i < G->vertex_count; i++)
    {
        free(G->vertex_array[i].vecinos);
    }

    free(G->vertex_array);

    free(G);

    return 1;
    // LIBERA MEMORIA ALOCADA DE LA ESTRUCTURA
}


void SHOW(GrapfP G)
{
    u32 j, t;
    printf("-----------------------------------------\n");
    for(j = 0; j < G->vertex_count; j++)
    {
        printf("Vertice: '%u' ==> Grado = %u\n", G->vertex_array[j].id, G->vertex_array[j].grado);
        for(t = 0; t < G->vertex_array[j].grado; t++)
        {
            printf("    Los vecinos de el vertice son '%u': %u\n", G->vertex_array[j].id, G->vertex_array[G->vertex_array[j].vecinos[t]].id);
        }
    }
    printf("-----------------------------------------\n");
}


u32 contador = 0; // Variable Global que me dice hasta cuanto esta lleno el arreglo vertex_array


void add_vertex_id_color_grado(GrapfP G, u32 vertex)
{
    bool existe = false;
    u32 i = 0;
    
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
    u32 i = 0;
    u32 j = 0;
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
// static inline char *_non_empty_line(FILE *fd)
// {
//     assert(fd != NULL);
//     char *line = readline(fd);
//     while (strlen(line) == 0)
//     {
//         free(line);
//         line = readline(fd);
//     }

//     return(line);
// }

int LeerGrafo(GrapfP G) 
{
    u32 vertex_count = 0, edges_count = 0; // Varibles con vertices y aristas
    u32 scan_result;
    char line; 
    u32 i = 0;
    u32 j;
    u32 k = 0;
    u32 left, right;

// --------------------------PRIMERA RECORRIDA ----------------------------
    while (fscanf(stdin, "%c", &line) != EOF && line != 'p')
    {
        while (fscanf(stdin, "%c", &line) != EOF && line != '\n');
    }

    scan_result = fscanf(stdin, "%*s %u %u\n", &vertex_count, &edges_count);

    if (scan_result != 2)
    {
        return -1;
    }

    G->vertex_count = vertex_count;
    G->edges_count = edges_count;
    G->color_count = vertex_count;

    G->vertex_array = calloc(vertex_count, sizeof(Vertex)); // Tamaño del arreglo de Vertex

    while (i < edges_count && scan_result == 2)
    {
        left = 0;
        right = 0;

        scan_result = fscanf(stdin, "\ne %u %u", &left, &right);

        if (left == right || scan_result != 2)
        {
            return -1;
        }
        else
        {
            add_vertex_id_color_grado(G, left);
            add_vertex_id_color_grado(G, right);
        }

        i++;
    }

    for(j = 0; j < G->vertex_count; j++)
    {
        G->vertex_array[j].vecinos = calloc(G->vertex_array[j].grado, sizeof(u32));
    }
// -----------------------------------------------------------------------

    fseek(stdin, 0, 0);

// --------------------------SEGUNDA RECORRIDA ----------------------------
    while (fscanf(stdin, "%c", &line) != EOF && line != 'p')
    {
        while (fscanf(stdin, "%c", &line) != EOF && line != '\n');
    }

    scan_result = fscanf(stdin, "%*s %u %u\n", &vertex_count, &edges_count);

    if (scan_result != 2)
    {
        return -1;
    }

    while (k < edges_count && scan_result == 2)
    {
        left = 0;
        right = 0;

        scan_result = fscanf(stdin, "\ne %u %u", &left, &right);

        add_vecino(G, left, right);

        k++;
    }
// -----------------------------------------------------------------------

    return vertex_count;
}

int ImprimirGrafo(GrapfP G)
{
    u32 i;
    u32 k;
    u32 grado_aux = 0;

    printf("p edge %u %u\n", G->vertex_count, G->edges_count);
    
    for(i = 0; i < G->vertex_count; i++)
    {
        grado_aux = G->vertex_array[i].grado;
        
        for(k = 0; k < grado_aux; k++)
        {
            if(G->vertex_array[i].vecinos[k] > i)
            {
                printf("e %u %u\n", G->vertex_array[i].id, G->vertex_array[G->vertex_array[i].vecinos[k]].id);
            }
        }
    }

    return 1;
}


u32 CantidadDeColores(GrapfP G)
{
    return G->color_count;
}


u32 NumeroVerticesDeColor(GrapfP G, u32 i){

    u32 cant_color = 0;
    u32 j;

    for(j = 0; j<G->vertex_count; j++)
    {
        if(G->vertex_array[j].color == i)
        {
            cant_color ++;
        }
    }
    return cant_color;
}


u32 ImprimirColor(GrapfP G, u32 i)
{
    u32 iterator;
    u32 cantidad_vertex_color = 0;
    bool find = false;

    for (iterator = 0; iterator < G->vertex_count; iterator++)
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



u32 Greedy(GrapfP G)
{
    u32 i = 0;
    u32 j = 0;
    u32 color_actual = 1;
    u32 grado_aux = 0;
    u32 max_color = 0;

    G->vertex_array[0].color = 1;

    for(i = 1; i < G->vertex_count; i++)
    {
        G->vertex_array[i].color = 0;
    }

    for(i = 1; i < G->vertex_count; i++)
    {
        j = 0;
        color_actual = 1;
        grado_aux = G->vertex_array[i].grado;

        while(j < grado_aux)
        {
            j++;

            if(color_actual == G->vertex_array[G->vertex_array[i].vecinos[j-1]].color)
            {
                color_actual++;
                j = 0;
            }
        }

        G->vertex_array[i].color = color_actual;

        if(max_color < color_actual)
        {
            max_color = color_actual;
        }
    }

    G->color_count = max_color;

    return max_color;
}

u32 DSATUR(GrapfP G){

    u32 i,j,k = 0;
    u32 max_dsatur, dsatur_aux = 0;
    u32 dsatur[G->vertex_count];
    u32 max_grado, grado_aux = 0;
    u32 empate_dsatur, por_colorear = 0;
    u32 color_actual, color_max = 0;
    u32 vecino_j = 0;
    bool falta_colorear = true;
    bool no_actualizar_dsatur = false;

    for(i = 0; i < G->vertex_count; i++){
        dsatur[i] = 0;
        G->vertex_array[i].color = 0;
        if(G->vertex_array[i].grado > grado_aux)
        {
            max_grado = i;
            grado_aux = G->vertex_array[i].grado;
        }
    }

    G->vertex_array[max_grado].color = 1;
    for(j=0;j<G->vertex_array[max_grado].grado;j++){
        dsatur[G->vertex_array[max_grado].vecinos[j]]++;
    }

    while(falta_colorear){

        dsatur_aux = 0;
        for(i = 0;i < G->vertex_count;i++){
            if(G->vertex_array[i].color == 0){
                if(dsatur[i] > dsatur_aux){
                    max_dsatur = i;
                    dsatur_aux = dsatur[i];
                }
            }
        }

        grado_aux = 0;
        for(i=0;i < G->vertex_count;i++){
            if(G->vertex_array[i].color == 0){
                if(dsatur[i] == dsatur_aux){
                    empate_dsatur++;
                    if(G->vertex_array[i].grado > grado_aux){
                        grado_aux = G->vertex_array[i].grado;
                        max_grado = i;
                    }
                }
            }
        }

        if(empate_dsatur >= 2){
            por_colorear = max_grado;
        } else{
            por_colorear = max_dsatur;
        }

        color_actual = 1;
        grado_aux = G->vertex_array[por_colorear].grado;
        j = 0;

        while(j < grado_aux)
        {
            j++;
            if(color_actual == G->vertex_array[G->vertex_array[por_colorear].vecinos[j-1]].color){
                color_actual++;
                j = 0;
            }
        }

        for(j=0;j<grado_aux;j++){
            vecino_j = G->vertex_array[por_colorear].vecinos[j];
            if(G->vertex_array[vecino_j].color == 0){
                k = 0;
                while(k<G->vertex_array[vecino_j].grado && no_actualizar_dsatur){
                    i = G->vertex_array[G->vertex_array[vecino_j].vecinos[k]].color;
                    no_actualizar_dsatur = no_actualizar_dsatur || (color_actual == i);
                    k++;
                }
                if(!no_actualizar_dsatur){
                    dsatur[vecino_j]++;
                }
            }
        }

        i = 0;
        falta_colorear = false;
        while(i<G->vertex_count && !falta_colorear){
            falta_colorear = falta_colorear || (G->vertex_array[i].color == 0);
            i++;
        }
        G->vertex_array[por_colorear].color = color_actual;

        if(color_max < color_actual){
            color_max = color_actual;
        }
    }

    G->color_count = color_max;

    return color_max;
}

void swap(GrapfP G, u32 i, u32 j)
{
    Vertex tmp;

    tmp = G->vertex_array[i];
    G->vertex_array[i] = G->vertex_array[j];
    G->vertex_array[j] = tmp;
}

void Bubble_Sort(GrapfP G)
{
    u32 i, j;
    bool swapped;

    swapped = true;
    i = 0;

    while (swapped && (i + 1 < G->vertex_count))
    {
        swapped = false;
        
        for (j = G->vertex_count - 1; j > 0; j--)
        {
            if (G->vertex_array[j].grado > G->vertex_array[j - 1].grado)
            {
                swap(G, j, j - 1);
                swapped = true;
            }
        }
        i++;
    }
}


void OrdenWelshPowell(GrapfP G)
{
    SHOW(G);
    Bubble_Sort(G);
    SHOW(G);
}