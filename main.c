#include <stdio.h>
#include <stdlib.h>
#include "api.h"

int main()
{
    Grapfd grafo = NULL;

    printf("ANTES DE NuevoGraf\n");

    grafo = NuevoGraf();

    printf("DESPUES DE NuevoGraf y ANTES DE LeerGraf\n");

    LeerGraf(grafo);

    printf("DESPUES DE LeerGraf y ANTES DE DestruirGraf\n");

    DestruirGraf(grafo);

    printf("Final\n");

    return 0;
}