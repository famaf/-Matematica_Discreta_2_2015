#ifndef API_H
#define API_H

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>


typedef uint32_t u32;


typedef struct GrafoPlus *GrapfP;
typedef struct Vertex_Data Vertex;


GrapfP NuevoGraf();


int DestruirGraf(GrapfP G);


int LeerGrafo(GrapfP G);


u32 CantidadDeColores(GrapfP G);

u32 NumeroVerticesDeColor(GrapfP G, u32 i);

/*int ImprimirGrafo(GrapfP G);


int ImprimirColor(GrapfP G, u32 i);



*/
#endif