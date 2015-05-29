#include <stdio.h>
#include <stdlib.h>
#include "api.h"

int main()
{
//    u32 mario;
    printf("inicio\n\n");

    GrapfP grafo = NuevoGraf();

//    printf("DESPUES DE NuevoGraf y ANTES DE LeerGraf\n");

    LeerGrafo(grafo);

 //   ImprimirGrafo(grafo);

    //printf("Cantidad de colores usados: %u\n", CantidadDeColores(grafo));

    //OrdenWelshPowell(grafo);
    printf("La cantidad de colores con Greedy es: %u\n\n", Greedy(grafo));


    //printf("La cantidad de colores con DSATUR es: %u\n\n", DSATUR(grafo));
    
    // printf("<<<<<<GRANDE_CHICO>>>>>>\n");
    // GrandeChico(grafo);

    printf("<<<<<<CHICO_GRANDE>>>>>>\n");
    ChicoGrande(grafo);

    // printf("<<<<<REVIERTE>>>>>\n");
    // Revierte(grafo);

    //ImprimirColor(grafo, 433);

    //printf ("NumeroVerticesDeColor x = %u\n", NumeroVerticesDeColor(grafo, 488));

    //printf("DESPUES DE LeerGraf y ANTES DE DestruirGraf\n");


    DestruirGraf(grafo);

    printf("Final\n\n");

    return 0;
}