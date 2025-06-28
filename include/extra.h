#ifndef EXTRA_H
#define EXTRA_H

#include "list.h"
#include "hashmap.h"
#include "../estructuras.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

HashMap *leer_partidas();

HashMap *leer_procesados(); 

HashMap *leer_dni();

HashMap *leer_pasaportes();

HashMap *leer_sujetos();

char *leer_char();

char **leer_linea_csv(FILE *archivo, char separador);

List *split_string(const char *str, const char *delim);

void eliminar_partida(char * nombre_partida);

void autoguardado(tipoPartida *partida);

void presioneTeclaParaContinuar();

#endif