#include <stdio.h>
#include <stdlib.h>
#include "api.h"

int main()
{
    printf("ANTES DE NuevoGraf\n");

    GrapfP grafo = NuevoGraf();

    printf("DESPUES DE NuevoGraf y ANTES DE LeerGraf\n");

    LeerGrafo(grafo);

    ImprimirGrafo(grafo);

    printf("DESPUES DE LeerGraf y ANTES DE DestruirGraf\n");

    DestruirGraf(grafo);

    printf("Final\n");

    return 0;
}