#include <stdio.h>
#include <stdlib.h>
#include "api.h"

int main()
{
    GrapfP grafo = NuevoGraf();

    printf("ANTES DE NuevoGraf\n");

    //grafo = NuevoGraf();

    printf("DESPUES DE NuevoGraf y ANTES DE LeerGraf\n");

    LeerGrafo(grafo);

    printf("DESPUES DE LeerGraf y ANTES DE DestruirGraf\n");

    DestruirGraf(grafo);

    printf("Final\n");

    return 0;
}