#ifndef HELPERS_H
#define HELPERS_H

#include <stdio.h>


char *readline(FILE *file);

char *readline_from_stdin(void);
/*
 * Read the user input from standard input until a newline is detected,
 * and return the corresponding (dinamically allocated) string.
 *
 * The caller to this function is responsible for the allocated memory.
 *
 * POST: A new null-terminated string is returned with the content read from
 * standard input, or NULL if there was an error.
 */

/*
 * Lee la entrada del usuario de la entrada estándar hasta que se detecta un salto 
 * de línea, y devolver el (dinámicamente asignada) string correspondiente.
 * La persona que llama a esta función es responsable de la memoria asignada.
 * POST: Una nueva cadena terminada en cero se devuelve con el contenido lee de la
 * entrada estándar, o NULL si hubo un error.
*/
#endif
