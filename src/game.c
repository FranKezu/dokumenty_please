#include "../include/game.h"
#include "../include/menu.h"
#include "../include/hashmap.h"
#include "../include/queue.h"
#include "../include/extra.h"
#include "../estructuras.h"

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include <mmsystem.h>
#include <stdbool.h>
#include <time.h>

bool calcular_habilitado(tipoPersona * persona, int dia) {
  if (persona == NULL)
    return false;
  tipoSujeto * sujeto = persona -> sujeto;
  tipoPasaporte * pasaporte = persona -> pasaporte;
  tipoDNI * DNI = persona -> dni;

  char num_Pasaporte[] = {'P', 'A', 'O', 'E'};

  short random = rand() % 4;

  int dificultad;
  if (dia == 1) dificultad = 1;
  else if (dia == 2) dificultad = 2;
  else dificultad = 3;

  // Coincidan nombres de Pasaporte y DNI
  if (dificultad >= 1) {
    if (strcmp(sujeto->nombre, DNI->nombre) != 0)
      return false;
  }
  // También va a tener que verificar que el pasaporte tenga el mismo nombre
  // Coincide numero de pasaporte y DNI
  // Que no esté vencido
  if (dificultad >= 2) {
    if (strcmp(pasaporte->nombre, DNI->nombre) != 0) return false;
    if (strcmp(pasaporte->documento, DNI->documento) != 0) return false;
  }
  if (dificultad >= 3){
    if (pasaporte->documento[0] != num_Pasaporte[random]) return false;
  }

  return true;
}

void empezar_dia(tipoMapas mapas, tipoPartida * partida) {
  printf("\033[33mDía: \033[37m%d \033[33m- Hora: \033[37m09:00\n\033[0m", partida -> dia_actual);
  printf("\033[37mInicia el turno...\n\n\033[0m");
  presioneTeclaParaContinuar();
  Queue * cola_diaria = encolar_personas(mapas);
  int contador = 1;
  while (contador != 7) {
    printf("Se aproxima la persona número: %d\n\n", contador);
    tipoPersona * persona = (tipoPersona * ) queue_remove(cola_diaria);
    menu_acciones(cola_diaria, persona, partida);
    contador++;
  }
}

void empezar_partida(tipoMapas mapas, char * nombre_partida) {
  HashMap * mapa_partidas = mapas.mapa_partidas;
  Pair * par = searchMap(mapa_partidas, nombre_partida);
  tipoPartida * partida = (tipoPartida * ) par -> value;

  system("cls");
  printf("\nPartida '%s' iniciada exitosamente.\n\n", partida -> nombre_partida);
  empezar_dia(mapas, partida);
}

Queue * encolar_personas(tipoMapas mapas) {
  HashMap * mapa_sujetos = mapas.mapa_sujetos;
  HashMap * mapa_pasaportes = mapas.mapa_pasaportes;
  HashMap * mapa_dni = mapas.mapa_dni;

  srand(time(NULL));

  Queue * cola_personas = queue_create();
  for (short i = 0; i < 7; i++) {
    int random = rand() % 1000;
    char ID[10];
    sprintf(ID, "%d", random);

    tipoPersona * persona = (tipoPersona * ) malloc(sizeof(tipoPersona));

    Pair * Sujeto = searchMap(mapa_sujetos, ID);
    persona -> sujeto = Sujeto -> value;
    eraseMap(mapa_sujetos, ID);

    Pair * Pasaporte = searchMap(mapa_pasaportes, ID);
    persona -> pasaporte = Pasaporte -> value;
    eraseMap(mapa_pasaportes, ID);

    Pair * DNI = searchMap(mapa_dni, ID);
    persona -> dni = DNI -> value;
    eraseMap(mapa_dni, ID);

    queue_insert(cola_personas, persona);
  }

  return cola_personas;
}