#ifndef API_H
#define API_H


#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>


typedef uint32_t u32;


typedef struct GrafoPlus *GrafP;


typedef struct Vertex_Data *Vertex;


GrafP NuevoGraf();


int DestruirGraf(GrafP G);


int LeerGrafo(GrafP G);


u32 CantidadDeColores(GrafP G);


u32 NumeroVerticesDeColor(GrafP G, u32 i);


int ImprimirGrafo(GrafP G);


u32 ImprimirColor(GrafP G, u32 i);


u32 Greedy(GrafP G);


u32 DSATUR(GrafP G);


void OrdenWelshPowell(GrafP G);


void GrandeChico(GrafP G);


void ChicoGrande(GrafP G);


void Revierte(GrafP G);

#endif
