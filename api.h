#ifndef API_H
#define API_H


#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>


typedef uint32_t u32;


typedef struct GrafoPlus *GrapfP;


typedef struct Vertex_Data *Vertex;


GrapfP NuevoGraf();


int DestruirGraf(GrapfP G);


int LeerGrafo(GrapfP G);


u32 CantidadDeColores(GrapfP G);


u32 NumeroVerticesDeColor(GrapfP G, u32 i);


int ImprimirGrafo(GrapfP G);


u32 ImprimirColor(GrapfP G, u32 i);


u32 Greedy(GrapfP G);


u32 DSATUR(GrapfP G);


void OrdenWelshPowell(GrapfP G);


void GrandeChico(GrapfP G);


void ChicoGrande(GrapfP G);


void Revierte(GrapfP G);

#endif
