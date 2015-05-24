#include <stdio.h>
#include <stdlib.h>
#include "api.h"

int main()
{
//    u32 mario;
//    printf("ANTES DE NuevoGraf\n");

    GrapfP grafo = NuevoGraf();

//    printf("DESPUES DE NuevoGraf y ANTES DE LeerGraf\n");

    LeerGrafo(grafo);

    //ImprimirGrafo(grafo);

    //printf("Cantidad de colores usados: %u\n", CantidadDeColores(grafo));

    OrdenWelshPowell(grafo);

    //ImprimirColor(grafo, 433);

    //printf ("NumeroVerticesDeColor x = %u\n", NumeroVerticesDeColor(grafo, 488));

    //printf("DESPUES DE LeerGraf y ANTES DE DestruirGraf\n");

    //printf("la cantidad de colores es %u\n", Greedy(grafo));

    DestruirGraf(grafo);

    printf("Final\n");

    return 0;
}