#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "helpers.h"



static inline char *_non_empty_line(FILE *fd) {
    assert(fd != NULL);
    char *line = readline(fd);
    while (strlen(line) == 0){
        free(line);
        line = readline(fd);
    }
    return(line);
}


int LeerGrafo(FILE *fd) 
{
    assert(fd != NULL);
    int scan_result = 0;
    char *line = NULL;
    unsigned int vertices_count = 0, edges_count = 0;

    line = _non_empty_line(fd); // line es un buffer, sscanf lee los elemento del buffer

    /* Primera(s) Linea: Si empieza con 'c' se ignora y se pasa a la siguiente */
    while (line[0] == 'c')
    {
        free(line);
        line = _non_empty_line(fd);
    }

    /* Segunda Linea: Debe contener cantidad de vértices y lados */

    scan_result = sscanf(line, "p edge %u %u\n", &vertices_count, &edges_count);
    
    free(line);
    
    if (scan_result != 2)
    {
        exit(EXIT_FAILURE);
        //return -1;
    }

    /* siguiente linea edges_count debe ser aristas */
    for (unsigned int i = 0; i < edges_count; i++)
    {
        unsigned int left = 0, right = 0;

        line = _non_empty_line(fd);

        scan_result = sscanf(line, "e %u %u", &left, &right);

        if (scan_result != 2)
        {
            exit(EXIT_FAILURE);
            //return -1;
        }

        free(line);
    }

    return vertices_count;
}