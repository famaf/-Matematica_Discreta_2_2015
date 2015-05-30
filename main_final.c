#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "API.h"

#define MIN(x, y) x<y?x:y


u32 WelshPowell(GrapfP G)
{
    OrdenWelshPowell(G);

    coloreo = Greedy(G);

    return coloreo,
}


int main()
{
    u32 check = 0;
    u32 coloreo = 0;
    u32 coloreo_G = 0;
    u32 coloreo_WP = 0;
    u32 coloreo_D = 0;
    u32 porcentaje = 0;
    u32 Nv;

    GrapfP G = NuevoGraf();

    check = LeerGrafo();

    if (check == 0)
    {
        printf("X(G) = 1\n");
        return 0;
    }
    else if (check == -1)
    {
        printf("Ocurrio un error\n");
        return 1;
    }

    coloreo_D = DSATUR(G);

    if (coloreo == 2)
    {
        printf("Grafo Bipartito\n");
        return 0;
    }

    coloreo_WP = WelshPowell(G);

    printf("WelshPowell: Colores Usados: %u\n", coloreo_WP);

    coloreo_D = DSATUR(G);

    printf("DSATUR: Colores Usados: %u\n", coloreo_D);

    if (coloreo_WP == 3 || coloreo_D == 3)
    {
        printf("X(G) = 3\n");
        return o;
    }

    coloreo = MIN(coloreo_WP, coloreo_D);

    srand(time(NULL));

    porcentaje = rand() % 101; // Numero entre [0 ... 100]


    for (Nv = 10; Nv > 0; Nv --)
    {
        if (porcentaje >= 4 && porcentaje <= 10)
        {
            OrdenAleatorio(G);
            coloreo_G = Greedy(G);
        }
        else if (porcentaje > 10 && porcentaje =< 50)
        {
            Revierte(G);
            coloreo_G = Greedy(G);
        }
        else if (porcentaje > 50 && porcentaje <= 75)
        {
            ChicoGrande(G);
            coloreo_G = Greedy(G);
        }
        else if (porcentaje)
        {
            GrandeChico(G);
            coloreo_G = Greedy(G);
        }

        coloreo = MIN(coloreo, coloreo_G);

        porcentaje = rand() % 101;
    }

    printf("Mejor coloreo con Greedy iterado %u veces es: %u colores\n", Nv, coloreo);

    return 0;
}