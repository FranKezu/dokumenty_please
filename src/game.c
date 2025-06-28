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

/*
 * Función: calcular_habilitado
 * Descripción: Función para calcular según el dia y la dificultad si la persona esta habilitada
 *              para pasar el control o no, de esta manera se decide si la decisión tomada por el
 *              jugador es acertada o érronea. Las reglas se van acumulando, ejemplo: la regla del
 *              día 19 se seguirá pidiendo en el día 20 y los posteriores.
 *
 * Parámetros:  Recibe como parámetros, la estructura tipoPersona y el día, según el día
 *              se definirá la dificultad.
 */

bool calcular_habilitado(tipoPersona * persona, int dia) {
  if (persona == NULL)
    return false;
  tipoSujeto * sujeto = persona -> sujeto;
  tipoPasaporte * pasaporte = persona -> pasaporte;
  tipoDNI * DNI = persona -> dni;

  int dificultad;
  if (dia == 1) dificultad = 1;
  else if (dia == 2) dificultad = 2;
  else if (dia == 3) dificultad = 3;
  else dificultad = 4;

  // Coindcidan nombres de Pasaporte y DNI
  if (dificultad >= 1) {
    // Regla 1: Los nombres deben coincidir (sujeto, DNI, pasaporte)
    if (strcmp(sujeto -> nombre, DNI -> nombre) != 0 || strcmp(sujeto -> nombre, pasaporte -> nombre) != 0) {
      return false;
    }
    // Regla 2: Los países deben coincidir (DNI, pasaporte)
    if (strcmp(DNI->pais, pasaporte->pais) != 0) return false;
    // Regla 3: Rechazar motivos de turismo
    if (strcmp(sujeto -> motivo, "Turismo") == 0) {
      return false;
    }
  }

  if (dificultad >= 2) {
    // Regla 4: DNI y pasaporte no deben estar vencidos
    if ((DNI -> caducidad[3] == '0') && (DNI -> caducidad[4] == '2') || (DNI -> caducidad[3] == '0') && (DNI -> caducidad[4] == '1')) {
      return false;
    }
    // Regla 5: Los números de los documentos deben coincidir
    if (strcmp(pasaporte -> documento, DNI -> documento) != 0) {
      return false;
    }
  }
  if (dificultad >= 3) {
    // Regla 6: Rechazar pasaportes con la letra 'O'
    if(pasaporte->pasaporte[0] == 'O') return false;
    // Regla 7: Prohibir ingreso a nacidos en agosto
    if ((DNI -> caducidad[3] == '0') && (DNI -> caducidad[4] == '8')) return false;
  }

  if(dificultad >= 4){
    // Regla 8: Prohibir nacionalidad 'Letonia'
    if(strcmp(DNI->pais, "Letonia") == 0 || strcmp(pasaporte->pais, "Letonia") == 0) return false;
    // Regla 9: Rechazar a quienes tengan menos de 800 rublos
    if (sujeto->dinero < 800) return false;
    // Regla 10: Rechazar a quienes tengan más de 2500 rublos
    if (sujeto->dinero > 2500) return false;
    // Regla 11: Rechazar motivos familiares
    if (strcmp(sujeto->motivo, "Familia") == 0) return false;
  }

  return true;
}


/*
 * Función: encolar_personas
 * Descripción: Función para crear una cola de personas para cada día, simulando así una cola en la vida real
 *              para que el jugador tenga que revisar los datos pertinentes y decidir si le permite el acceso
 *              o no. Se usa un ciclo "for" para ingresar los datos a la cola y borrar los que van ingresando
 *              a la cola de el HashMap, para no repetir a las mismas personas.
 *
 * Parámetros:  Recibe como parametro, la estructura o capsula de los mapas, obteniuendo así,
 *              toda la información de cada persona. Su pasaporte, DNI, el motivo de viaje, etc.
 *              
 */


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

/*
 * Función: empezar_dia
 * Descripción: Función para empezar el día y encolar a las personas (7 por día), mostrando por
 *              pantalla todo lo pertinente al día como la hora, el inicio del turno, aproximación
 *              de las personas, etc. Se maneja un bucle para avanzar de día cuando se termine de
 *              atender a la cola de personas, y se guarda la partida.
 *
 * Parámetros:  Recibe como parámetros, la estructura o capsula de los mapas y la
 *              estructura tipoPartida.
 */

void empezar_dia(tipoMapas mapas, tipoPartida * partida) {
  printf("\033[33mDía: \033[37m%d \033[33m- Hora: \033[37m09:00\n\033[0m", partida -> dia_actual);
  printf("\033[37mInicia el turno...\n\n\033[0m");
  Sleep(2000);
  Queue * cola_diaria = encolar_personas(mapas);
  int contador = 1;
  while (contador != 7) {
    printf("Se aproxima la persona número: %d\n\n", contador);
    tipoPersona * persona = (tipoPersona * ) queue_remove(cola_diaria);
    persona->sujeto->habilitado = calcular_habilitado(persona, partida->dia_actual);
    menu_acciones(cola_diaria, persona, partida);
    contador++;
  }
  system("cls");
  partida->dia_actual +=1;
  autoguardado(partida);
  empezar_dia(mapas, partida);
}

/*
 * Función: empezar_partida
 * Descripción: Función para iniciar una partida existente. Busca en el mapa_partidas el nombre
 *              de la partida existente, muestra un mensaje por pantalla para indicar que se inició
 *              con éxito y finalmente usa la función empezar_dia.
 *
 * Parámetros:  Recibe como parametros, la estructura o capsula de los mapas y el
 *              nombre de la partida a buscar.
 */

void empezar_partida(tipoMapas mapas, char * nombre_partida) {
  HashMap * mapa_partidas = mapas.mapa_partidas;
  Pair * par = searchMap(mapa_partidas, nombre_partida);
  tipoPartida * partida = (tipoPartida * ) par -> value;

  system("cls");
  printf("\nPartida '%s' iniciada exitosamente.\n\n", partida -> nombre_partida);
  autoguardado(partida);
  empezar_dia(mapas, partida);
}
