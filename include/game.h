#ifndef game_h
#define game_h

#include "../include/queue.h"
#include "../include/extra.h"
#include "../estructuras.h"

#include <stdbool.h>

void empezar_dia(tipoMapas, tipoPartida *);

void empezar_partida(tipoMapas, char *);

Queue *encolar_personas(tipoMapas);

bool calcular_habilitado(tipoPersona *, int);



#endif