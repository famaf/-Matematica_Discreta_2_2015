#include <stdio.h>

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
    u32 coloreo_WP = 0;
    u32 coloreo_D = 0;
    u32 Nv = 10;

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


    if (porcentaje < 25)
    {

    }
    else if (porcentaje >= 25 && porcentaje < 50)
    {

    }
    else if (porcentaje >= 50 && porcentaje < 75)
    {

    }
    else
    {

    }

    return 0;
}