#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include <time.h>
#include "API.h"

// Estructura de cada vertice
struct Vertex_Data
{
    u32 id; // Nombre del Vertice
    u32 grado; // Grado del vertice
    u32 color; // Color del vertice
    u32 *vecinos; // Arreglo de vecinos que contiene sus posiciones en el vertex_array
};


// Estructura del grafo
struct GrafoPlus
{
    u32 vertex_count; // Cantidad de vertices del grafo
    u32 edges_count; // Cantidad de lados del grafo
    u32 color_count; // Cantidad de colores del grafo --> "X(G)"
    u32 *array_orden; // Arreglo que contiene el orden en que los vertices fueron ingresados
    Vertex *vertex_array; // Arreglo de Estructura Vertex
} GrafoSt;


GrafP NuevoGraf()
{
    GrafP G = calloc(1, sizeof(GrafoSt)); // Asigno un espacio para la estructura del grafo

    if (G == NULL)
    {
        return NULL;
    }

    // Asigno los campos de la estrutura.
    G->vertex_count = 0;
    G->edges_count  = 0;
    G->color_count = 0;
    G->vertex_array = NULL;
    G->array_orden = NULL;

    return G;
}


int DestruirGraf(GrafP G)
{
    u32 i; // Indice del arreglo de vertices

    // Si G en NULL no hay nada que liberar, entonces retornamos 0
    if(G == NULL)
    {
        return 0;
    }

    // Libero el arreglo de vecinos de cada vertice
    // Y la estructura que de cada vertice
    for(i = 0; i < G->vertex_count; i++)
    {
        free(G->vertex_array[i]->vecinos);
        free(G->vertex_array[i]);
    }

    free(G->vertex_array); // Libero el arreglo de vertices

    free(G->array_orden); // Libero el arreglo de orden

    free(G); // Libero la estructura del grafo

    return 1;
}


u32 contador = 0; // Variable Global que me dice hasta cuanto esta lleno el arreglo vertices


// Agrego a cada vertice su identificador (o nombre), su color, y su grado
void add_vertex_id_color_grado(GrafP G, u32 vertex)
{
    bool existe = false; // Me dice si el vertice ya estaba el el arreglo de vertices
    u32 i = 0; // Indice para recorrer el arreglo de vertices
    
    while(i < contador && !existe)
    {
        if (vertex == G->vertex_array[i]->id) // Si vertice esta en el array => aumento grado
        {
            G->vertex_array[i]->grado ++; // Aumentamos su grado
            existe = true; // Vertice ya estaba en el arreglo de vertices
        }

        i++;
    }

    if(!existe) // Si el vertice no estaba en el array, lo agrego
    {
        G->vertex_array[i] = calloc(1, sizeof(struct Vertex_Data)); // Alocamos memoria para un nuevo vertice
        G->vertex_array[i]->id = vertex; // Añadimos su identificador
        G->vertex_array[i]->grado = 1; // Añadimos su grado inicialmente
        G->vertex_array[i]->color = (i + 1); // Añadimos su color
        G->array_orden[i] = i; // Añadimos al arreglo de orden, la posicion en que fue ingresado el vertice

        contador ++; // Aumento el contador, indicando que añadimos un nuevo vertice
    }
}

// Guardamos en el areglo de vecinos la posición en donde está su vértice vecino
void add_vecino(GrafP G, u32 vertex_1, u32 vertex_2)
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
        if (G->vertex_array[i]->id == vertex_1)
        {
            pos1 = i;
            find1 = true;
        }
        if(G->vertex_array[i]->id == vertex_2)
        {
            pos2 = i;
            find2 = true;
        }
        i++;
    }

    while (j < G->vertex_array[pos1]->grado && !existe)
    {
        if (G->vertex_array[pos1]->vecinos[j] == 0)
        {
            G->vertex_array[pos1]->vecinos[j] = pos2;
            existe = true;
        }
        j++;
    }

    j = 0;
    existe = false;
    
    while (j < G->vertex_array[pos2]->grado && !existe)
    {
        if (G->vertex_array[pos2]->vecinos[j] == 0)
        {
            G->vertex_array[pos2]->vecinos[j] = pos1;
            existe = true;
        }
        j++;
    }
}


int LeerGrafo(GrafP G) 
{
    u32 vertex_count = 0; // Variable que contiene la cantidad de vertices del grafo
    u32 edges_count = 0; // Variable que contiene la cantidad de aristas del grafo
    u32 scan_result; // Variable que sirve para checkear que los parametros ingresados esta bien
    char line; // Variable que guarda el primer caracter ingresado
    u32 i = 0; // Indice para recorrer la entrada por primera vez, segun la cantidad de lados ingresados
    u32 j; // Indice para recorrer el arreglo de vertices
    u32 left; // Variable para almacenar el vertice izquierdo segun la entrada
    u32 right; // Variable para almacenar el vertice derecho segun la entrada
    u32 *lefts;
    u32 *rights;

// --------------------------PRIMERA RECORRIDA ----------------------------
    // Leo la entrada ingnorando los comentarios, esperando hasta que se ingrese un 'p'
    while (fscanf(stdin, "%c", &line) != EOF && line != 'p')
    {
        while (fscanf(stdin, "%c", &line) != EOF && line != '\n');
    }

    scan_result = fscanf(stdin, "%*s %u %u\n", &vertex_count, &edges_count);

    // Chequeo que la estrada sea correcta
    if (scan_result != 2)
    {
        return -1;
    }

    G->vertex_count = vertex_count; // Asignamos la cantidad de vertices a la estructura del grafo
    G->edges_count = edges_count; // Asignamos la cantidad de lados a la estructura del grafo
    G->color_count = vertex_count; // Asignamos la cantidad de colores al grafo, incialmente tendra tantos colores como vertices tenga

    G->vertex_array = calloc(vertex_count, sizeof(Vertex)); // Tamaño del arreglo de vertices
    G->array_orden = calloc(vertex_count, sizeof(u32)); // Tamaño del arreglo de orden
    lefts = calloc(edges_count, sizeof(u32));
    rights = calloc(edges_count, sizeof(u32));

    // Leo la entrada donde se expresa los lados del grafo
    while (i < edges_count && scan_result == 2)
    {
        left = 0;
        right = 0;

        scan_result = fscanf(stdin, "\ne %u %u", &left, &right); // Guardo los vertices ingresados
        // Chequeo que la entrada sea correcta y me fijo que no ingresen un lado con los mismos vertices
        // Por Ejemplo: e 1 1
        if (left == right || scan_result != 2)
        {
            return -1;
        }
        else
        {
            lefts[i] = left;
            rights[i] = right;
            add_vertex_id_color_grado(G, left); // Agrego el vertice a la estructura
            add_vertex_id_color_grado(G, right); // Agrego el vertice a la estructura
        }

        i++; // Leo la siguiente linea de la entrada
    }

    // Aloco memoria segun la cantidad de vecinos que tenga cada vertice
    for(j = 0; j < G->vertex_count; j++)
    {
        G->vertex_array[j]->vecinos = calloc(G->vertex_array[j]->grado, sizeof(u32));
    }
// -----------------------------------------------------------------------

    for(i = 0; i < edges_count;i++)
    {
        add_vecino(G, lefts[i], rights[i]); // Agrego los vecinos de cada vertice.
    }

    free(lefts);
    free(rights);
// -----------------------------------------------------------------------

    return vertex_count;
}

int ImprimeGrafo(GrafP G)
{
    u32 i;
    u32 k;
    u32 grado_aux = 0;

    printf("p edge %u %u\n", G->vertex_count, G->edges_count);
    
    for(i = 0; i < G->vertex_count; i++)
    {
        grado_aux = G->vertex_array[i]->grado;
        
        for(k = 0; k < grado_aux; k++)
        {
            if(G->vertex_array[i]->vecinos[k] > i)
            {
                printf("e %u %u\n", G->vertex_array[i]->id, G->vertex_array[G->vertex_array[i]->vecinos[k]]->id);
            }
        }
    }

    return 1;
}


u32 CantidadDeColores(GrafP G)
{
    return G->color_count; // Retorno la cantidad de colores del grafo
}


u32 NumeroVerticesDeColor(GrafP G, u32 i)
{
    u32 cant_color = 0; // Variable que contiene la cantidad de vertices con el color 'i'
    u32 j; // Indice para recorrer el arreglo de vertices

    // Recorremos el arreglo de vertices
    for(j = 0; j < G->vertex_count; j++)
    {
        // Si un vertices tiene el color 'i' aumentamos la variable cant_color
        if(G->vertex_array[j]->color == i)
        {
            cant_color ++;
        }
    }
    return cant_color;
}


u32 ImprimirColor(GrafP G, u32 i)
{
    u32 iterator; // Variable para recorrer el arreglo de vertices
    u32 cantidad_vertex_color = 0; // Varible que contiene la cantidad de vertices de color 'i'
    bool find = false; // Flag para saber si hay vertices de color 'i'

    // Recorremos el arreglo de vertices
    for (iterator = 0; iterator < G->vertex_count; iterator++)
    {
        // Nos fijamos si hay vertices tiene el color 'i'
        if (G->vertex_array[iterator]->color == i)
        {
            // Esto es para que la impresion de la salida sea como la que se especifico
            if (!find)
            {
                printf("Vertices de Color %u: ", i);
                printf("%u", G->vertex_array[iterator]->id);
            }
            else
            {
                printf(", %u", G->vertex_array[iterator]->id);
            }
            
            find = true;
            cantidad_vertex_color ++; // Aumentamos la cantidad de vertices que tienen el colr 'i'
        }
    }

    // Si no hay vertices de color 'i'
    if (!find)
    {
        printf("No hay vertices de color %u", i);
    }

    printf("->\n");

    return cantidad_vertex_color;
}



u32 Greedy(GrafP G)
{
    u32 i = 0;
    u32 j = 0;
    u32 color_actual = 1;
    u32 grado_aux = 0;
    u32 max_color = 0;

    G->vertex_array[G->array_orden[0]]->color = 1;

    for(i = 1; i < G->vertex_count; i++)
    {
        G->vertex_array[G->array_orden[i]]->color = 0;
    }

    for(i = 1; i < G->vertex_count; i++)
    {
        j = 0;
        color_actual = 1;
        grado_aux = G->vertex_array[G->array_orden[i]]->grado;

        while(j < grado_aux)
        {
            j++;

            if(color_actual == G->vertex_array[G->vertex_array[G->array_orden[i]]->vecinos[j-1]]->color)
            {
                color_actual++;
                j = 0;
            }
        }

        G->vertex_array[G->array_orden[i]]->color = color_actual;

        if(max_color < color_actual)
        {
            max_color = color_actual;
        }
    }

    G->color_count = max_color;

    return max_color;
}

u32 DSATUR(GrafP G){

    u32 i,j,k = 0;
    u32 dsatur_aux = 0;
    u32 max_dsatur = 0;
    u32 dsatur[G->vertex_count];
    u32 grado_aux = 0;
    u32 max_grado = 0;
    u32 por_colorear = 0;
    u32 empate_dsatur = 0;
    u32 color_max = 0;
    u32 color_actual = 0;
    u32 vecino_j = 0;
    bool falta_colorear = true;
    bool no_actualizar_dsatur = false;

    for(i = 0; i < G->vertex_count; i++)
    {
        dsatur[i] = 0;
        G->vertex_array[G->array_orden[i]]->color = 0;
        
        if(G->vertex_array[G->array_orden[i]]->grado > grado_aux)
        {
            max_grado = i;
            grado_aux = G->vertex_array[G->array_orden[i]]->grado;
        }
    }

    G->vertex_array[G->array_orden[max_grado]]->color = 1;
    
    for(j = 0; j < G->vertex_array[G->array_orden[max_grado]]->grado; j++)
    {
        dsatur[G->vertex_array[G->array_orden[max_grado]]->vecinos[j]]++;
    }

    while(falta_colorear)
    {
        dsatur_aux = 0;
        
        for(i = 0;i < G->vertex_count;i++)
        {
            if(G->vertex_array[G->array_orden[i]]->color == 0)
            {
                if(dsatur[i] > dsatur_aux)
                {
                    max_dsatur = i;
                    dsatur_aux = dsatur[i];
                }
            }
        }

        grado_aux = 0;

        for(i = 0; i < G->vertex_count; i++)
        {
            if(G->vertex_array[G->array_orden[i]]->color == 0)
            {
                if(dsatur[i] == dsatur_aux)
                {
                    empate_dsatur++;
                    
                    if(G->vertex_array[G->array_orden[i]]->grado > grado_aux)
                    {
                        grado_aux = G->vertex_array[G->array_orden[i]]->grado;
                        max_grado = i;
                    }
                }
            }
        }

        if(empate_dsatur >= 2)
        {
            por_colorear = max_grado;
        }
        else
        {
            por_colorear = max_dsatur;
        }

        color_actual = 1;
        grado_aux = G->vertex_array[G->array_orden[por_colorear]]->grado;
        j = 0;

        while(j < grado_aux)
        {
            j++;
            
            if(color_actual == G->vertex_array[G->vertex_array[G->array_orden[por_colorear]]->vecinos[j-1]]->color)
            {
                color_actual++;
                j = 0;
            }
        }

        for(j = 0;j < grado_aux; j++)
        {
            vecino_j = G->vertex_array[G->array_orden[por_colorear]]->vecinos[j];
            
            if(G->vertex_array[G->array_orden[vecino_j]]->color == 0)
            {
                k = 0;
                
                while(k < G->vertex_array[G->array_orden[vecino_j]]->grado && no_actualizar_dsatur)
                {
                    i = G->vertex_array[G->vertex_array[G->array_orden[vecino_j]]->vecinos[k]]->color;
                    no_actualizar_dsatur = no_actualizar_dsatur || (color_actual == i);
                    k++;
                }
                
                if(!no_actualizar_dsatur)
                {
                    dsatur[vecino_j]++;
                }
            }
        }

        i = 0;
        falta_colorear = false;
        
        while(i < G->vertex_count && !falta_colorear)
        {
            falta_colorear = falta_colorear || (G->vertex_array[G->array_orden[i]]->color == 0);
            i++;
        }
        
        G->vertex_array[G->array_orden[por_colorear]]->color = color_actual;

        if(color_max < color_actual)
        {
            color_max = color_actual;
        }
    }

    G->color_count = color_max;

    return color_max;
}


// Procedimiento para swapear (intercambiar) dos valores de un arreglo.
void swap(u32 *array, u32 i, u32 j)
{
    u32 tmp = array[i];
    array[i] = array[j];
    array[j] = tmp;
}


//------------------- Funciones auxiliares de Quick Sort -------------------
u32 Pivot(u32 *array, GrafP G, u32 left, u32 right)
{
    u32 piv, i, j;
    piv = left;
    i = left + 1;
    j = right;
    
    while (i <= j)
    {
        if (G->vertex_array[(G->array_orden[i])]->grado > G->vertex_array[(G->array_orden[piv])]->grado)
        {
            i++;
        }
        else if (G->vertex_array[(G->array_orden[j])]->grado <= G->vertex_array[(G->array_orden[piv])]->grado)
        {
            j--;
        }
        else
        {
            swap(array, i, j);
            i++;
            j--;
        }
    }

    swap(array, piv, j);
    piv = j;
    
    return piv;
}


void Quick_Sort_Rec(u32 *array, GrafP G, u32 left, u32 right)
{
    u32 piv;
    
    if (right > left && right != 0 && left != UINT32_MAX)
    {
        piv = Pivot(array, G, left, right);
        
        if(piv != 0)
        {
            Quick_Sort_Rec(array, G, left, piv - 1);
        }
        
        if(piv != UINT32_MAX)
        {
            Quick_Sort_Rec(array, G, piv + 1, right);
        }
    }
}


void Quick_Sort(u32 *array, GrafP G, u32 length)
{
    Quick_Sort_Rec(array, G, 0, length - 1);
}
//-------------------------------------------------------------------------

void OrdenWelshPowell(GrafP G)
{
    // SHOW_ORDEN(G);
    // ORDEN_EN_LISTA(G);

    Quick_Sort(G->array_orden, G, G->vertex_count); // Usamos el algoritmo de ordenamiento "Quick Sort"
                                                    // Para ordenar el arreglo de orden segun el grado de cada vertice

    // ORDEN_EN_LISTA(G); 
    // SHOW_ORDEN(G);
}


// Funcione que calcula el maximo elemento de un arreglo
// Setea esa celda en 0, para que no sea elegida otra vez
// Y nos retorna su posicion
u32 Calcular_Mayor(u32 *array, u32 length)
{
    u32 mayor = 0;
    u32 posicion = 0;

    for(u32 i = 1; i <= length; i++)
    {
        if(array[i] > mayor)
        {
            mayor = array[i];
            posicion = i;
        }
    }

    array[posicion] = 0;

    return posicion;
}

// Se pueden optimizar metiendo el Calcular Maximo adentro y obteniendo la cantidad de vertices con dicho color y disminurlo con cada swap

void GrandeChico(GrafP G)
{
    u32 cant_colores = CantidadDeColores(G); // Cantidad de colores que tiene el grafo
    u32 index_color; // Indice para recorrer el arreglo de colores
    u32 posicion_color = 0; // Variable que guarda la posicion (color) del arreglo de colores
    u32 indice_vertice = 0; // Indice del arreglo de orden
    u32 i; // Indice para asignar al arreglo de colores la cantidad de vertices por color
    u32 j; // Indice para recorrer el arreglo de vertices

    // Creamos un arreglo auxiliar para guardar en el la cantidad de vertices por color
    // Donde el indice del arreglo va a representar el color
    // Por eso las posiciones van de 0 a cant_colores, pero la posicion 0 no se tiene en cuenta
    u32 *array_colores = calloc(cant_colores + 1, sizeof(u32));

    // Recorremos el array de colores asignando la cantidad de vertices por color
    for(i = 1; i <= cant_colores; i++)
    {
        array_colores[i] = NumeroVerticesDeColor(G, i);
    }

    // Recorro el arreglo de colores
    for(index_color = 1; index_color <= cant_colores; index_color++)
    {
        // Busco el maximo elemento de ese arreglo y devuelvo su posicion
        posicion_color = Calcular_Mayor(array_colores, cant_colores);

        j = 0; // Seteo el indice en 0 para recorrer desde el principio el arreglo de vertices
        // Recorro el array de vertices
        while(j < G->vertex_count && indice_vertice < G->vertex_count)
        {
            // Chequeo si algun elemento tiene el color devuelto por la funcion Calcular_Mayor
            if(G->vertex_array[G->array_orden[j]]->color == posicion_color)
            {
                swap(G->array_orden, j, indice_vertice); // Swapeo los elementos del array de orden
                indice_vertice ++; // Me muevo una posicion para adelante en el arreglo de orden
            }
            j++;
        }
    }

    free(array_colores); // Libero el arreglo de colores
}


// Funcione que calcula el minimo elemento de un arreglo
// Setea esa celda en UINT32_MAX (maximo valor de 32 bits), para que no sea elegida otra vez
// Y nos retorna su posicion
u32 Calcular_Menor(u32 *array, u32 length)
{
    u32 menor = UINT32_MAX;
    u32 posicion = 0;

    for(u32 i = 1; i <= length; i++)
    {
        if(array[i] < menor)
        {
            menor = array[i];
            posicion = i;
        }
    }

    array[posicion] = UINT32_MAX;

    return posicion;
}

void ChicoGrande(GrafP G)
{
    u32 cant_colores = CantidadDeColores(G); // Cantidad de colores que tiene el grafo
    u32 index_color; // Indice para recorrer el arreglo de colores
    u32 posicion_color = 0; // Variable que guarda la posicion (color) del arreglo de colores
    u32 indice_vertice = 0; // Indice del arreglo de orden
    u32 i; // Indice para asignar al arreglo de colores la cantidad de vertices por color
    u32 j; // Indice para recorrer el arreglo de vertices

    // Creamos un arreglo auxiliar para guardar en el la cantidad de vertices por color
    // Donde el indice del arreglo va a representar el color
    // Por eso las posiciones van de 0 a cant_colores, pero la posicion 0 no se tiene en cuenta
    u32 *array_colores = calloc(cant_colores + 1, sizeof(u32));

    array_colores[0] = UINT32_MAX; // Seteamos el valor que esta en la posicion 0 en UINT32_MAX

    // Recorremos el array de colores asignando la cantidad de vertices por color
    for(i = 1; i <= cant_colores; i++)
    {
        array_colores[i] = NumeroVerticesDeColor(G, i);
    }

    // Recorro el arreglo de colores
    for(index_color = 1; index_color <= cant_colores; index_color++)
    {
        // Busco el minimo elemento de ese arreglo y devuelvo su posicion
        posicion_color = Calcular_Menor(array_colores, cant_colores);

        j = 0; // Seteo el indice en 0 para recorrer desde el principio el arreglo de vertices
        // Recorro el array de vertices
        while(j < G->vertex_count && indice_vertice < G->vertex_count)
        {
            // Chequeo si algun elemento tiene el color devuelto por la funcion Calcular_Menor
            if(G->vertex_array[G->array_orden[j]]->color == posicion_color)
            {
                swap(G->array_orden, j, indice_vertice); // Swapeo los elementos del array de orden
                indice_vertice ++; // Me muevo una posicion para adelante en el arreglo de orden
            }
            j++;
        }
    }

    free(array_colores); // Libero el arreglo de colores
}



void Revierte(GrafP G)
{
    u32 index = 0; // Indice del array de orden
    u32 i; // Indice del arreglo de vertices
    u32 k; // Variable que contendra la cantidad de colores del grafo

    // Recoro los colores del mas grande al mas chico
    for (k = CantidadDeColores(G); k > 0; k--)
    {
        i = 0; // Seteo la posicion en 0 para recorrer desde el principio el arreglo de vertices
        // Recorro el array de vertices
        while(i < G->vertex_count && index < G->vertex_count)
        {
            // Chequeo si algun elemento tiene el color devuelto por la funcion Calcular_Menor
            if(G->vertex_array[G->array_orden[i]]->color == k)
            {
                swap(G->array_orden, i, index); // Swapeo los elementos del array de orden
                index++; // Me muevo una posicion para adelante en el arreglo de orden
            }
            i++;
        }
    }
}


void OrdenAleatorio(GrafP G)
{
    u32 cantidad_colores = CantidadDeColores(G); // Variable que contiene la cantidad de colores que tiene el grafo
    u32 cantidad_colores_variable = CantidadDeColores(G); // Variable que contiene la cantidad de colores que tiene el grafo
    bool flag = false; // Flag que me indice si tengo que hacer el chequeo de si el numero aleatorio ya fue elegido.
    bool hacer_swap; // Flag que me indica si tengo que hacer o no el swapeo
    u32 index = 0; // Indice para recorrer el arreglo de orden
    u32 i = 0; // Indice para recorrer el arreglo de vertices
    u32 numero_aleatorio = 0; // Variable que contendra el numero aleatorio

    // Creamos un arreglo auxiliar para guardar en el 1 o 0 si el numero aleatorio ya habia sido elegido o no
    // Donde el indice del arreglo va a representar el color (el numero aleatorio seria el indice)
    // Por eso las posiciones van de 0 a cant_colores, pero la posicion 0 no se tiene en cuenta
    u32 *array_aleatorio = calloc(cantidad_colores + 1, sizeof(u32));

    srand(time(NULL)); // Para que los numeros aleatorios no sean los mismos en cada llamada al procedimiento

    numero_aleatorio = rand() % cantidad_colores + 1; // Numero aleatorio entre 1 y cantidad_colores ( [1 ... cantidad_colores] )

    // Itero tantas veces como colores tenga
    while (cantidad_colores_variable > 0)
    {
        hacer_swap = true; // Me indice que puedo hacer el swapeo

        // Corrobora si el numero aleatorio ya fue elegido, buscando en el array aleatorio
        // Si en la posicion esa hay o no un 1
        if (flag)
        {
            if (array_aleatorio[numero_aleatorio] == 1)
            {
                hacer_swap = false; // Si el nuemero aleatorio ya fue elegido, no hago el swap y elijo otro numero
            }
        }

        // Chequea si puedo hacer el Swap
        if (hacer_swap)
        {
            array_aleatorio[numero_aleatorio] = 1; // Guardo el numero aleatorio en el arreglo. Si es 1 es porque ya salio, 0 sino
            flag = true; // Seteo el flag en True para que para los proximos aleatorios sean examinados,
                         // para saber si fueron o no elegidos
            i = 0; // Seteo la posicion en 0 para recorrer desde el principio el arreglo de vertices
            // Recorro el array de vertices
            while(i < G->vertex_count && index < G->vertex_count)
            {
                // Chequeo si algun elemento tiene el mismo color que indica el numero aleatorio
                if(G->vertex_array[G->array_orden[i]]->color == numero_aleatorio)
                {
                    swap(G->array_orden, i, index); // Swapeo los elementos del array de orden
                    index++; // Me muevo una posicion mas en el array de orden
                }
                i++;
            }
            cantidad_colores_variable --; // Disminuyo la cantidad de colores ya examinados
        }

        numero_aleatorio = rand() % cantidad_colores + 1; // Calculo otro numero aleatorio
    }

    free(array_aleatorio); // Libero el arreglo de numeros aleatorios.
}