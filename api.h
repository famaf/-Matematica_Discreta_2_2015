#ifndef API_H
#define API_H

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>


typedef uint32_t = u32;


typedef GrafSt *GrafP;


GrapfP NuevoGraf();


int DestruirGraft(Grapfp G);


int LeerGrafo(GrapfP G);


int ImprimirGrafo(GrapfP G);


int ImprimirColor(GrapfP G, u32 i);


u32 CantidadDeColores(GrapfP G);


#endif