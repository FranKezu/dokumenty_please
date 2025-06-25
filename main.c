#include "include/extra.h"
#include "include/hashmap.h"
#include "include/list.h"
#include "include/menu.h"
#include "include/queue.h"
#include "estructuras.h"

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>
#include <locale.h>
#include <conio.h>
#include <windows.h>
#include <time.h>

#define ARRIBA 72
#define ABAJO 80
#define ENTER 13

// PROTOTIPOS
void empezar_partida(tipoMapas, char *);
void crear_partida(tipoMapas);
void cargar_partida(tipoMapas);
Queue *encolar_personas(tipoMapas);
void mostrar_guia();


void empezar_dia(tipoMapas mapas, tipoPartida *partida){
  printf("\033[33mDía: \033[37m%d \033[33m- Hora: \033[37m09:00\n\033[0m", partida->dia_actual);
  printf("\033[37mInicia el turno...\n\n\033[0m");
  presioneTeclaParaContinuar();
  Queue *cola_diaria = encolar_personas(mapas); 
  int contador = 1;
  while(contador != 7){
    printf("Se aproxima la persona número: %d\n\n", contador);
    tipoPersona *persona = (tipoPersona *)queue_remove(cola_diaria);
    menu_acciones(cola_diaria, persona, partida);
    contador++;
  }
}


void empezar_partida(tipoMapas mapas, char *nombre_partida){
  HashMap *mapa_partidas = mapas.mapa_partidas;
  Pair *par = searchMap(mapa_partidas, nombre_partida);
  tipoPartida *partida = (tipoPartida *) par->value;

  system("cls");
  printf("\nPartida '%s' iniciada exitosamente.\n\n", partida->nombre_partida);
  empezar_dia(mapas, partida);
}

// Función para crear una nueva partida solicitando el nombre
void crear_partida(tipoMapas mapas) {
  HashMap *mapa_partidas = mapas.mapa_partidas;
  system("cls"); // Limpiar pantalla
  printf("Creando una nueva partida...\n");
  printf("Ingrese el nombre de la partida: ");
  char *nombre = leer_char();

  //Verificar nombre duplicado (aquí es cuando el hashmap brilla O(1) chabales)
  Pair *temp = searchMap(mapa_partidas, nombre);
  if (temp != NULL) {
    printf("\nYa existe una partida con ese nombre, por favor intenta con otro.\n");
    return;
  }
  
  //Abrir archivo
  FILE *archivo = fopen("data/partida.csv", "a");

  // Inicializar la estructura partida
  tipoPartida *nueva = malloc(sizeof(tipoPartida));
  nueva->nombre_partida = strdup(nombre);
  nueva->dia_actual = 1;
  nueva->aura = 0;
  //nueva.listaPersonas = NULL;

  // Guardar línea con lista vacía
  fprintf(archivo, "%s,%d,%d,\n", nueva->nombre_partida, nueva->dia_actual, nueva->aura);
  fclose(archivo);
  insertMap(mapa_partidas, nueva->nombre_partida, nueva);

  printf("\nPartida '%s' creada exitosamente.\n", nueva->nombre_partida);

  char *intro[] = {
    "\033[91m=== COMITÉ DE SEGURIDAD DEL ESTADO DE LA UNIÓN SOVIÉTICA ===\033[0m",
    "\033[97mDepartamento de Control de Fronteras e Identificación Ciudadana\033[0m",
    "",
    "\033[93m>> Fecha: 6 de Junio de 1985\033[0m",
    "\033[93m>> Ubicación: Puesto Fronterizo de Krasnograd, URSS\033[0m",
    "",
    "\033[97m>>> Camarada inspector:\033[0m",
    "\033[37mUsted ha sido asignado por el Comité Central para supervisar el cruce de nuestra sagrada frontera.\033[0m",
    "\033[37mVerifique cuidadosamente pasaportes, permisos y documentos de identidad.\033[0m",
    "\033[91m¡Alerta! Los enemigos del pueblo intentan infiltrarse a diario.\033[0m",
    "",
    "\033[97mCada autorización o rechazo influye en la seguridad del Estado.\033[0m",
    "\033[91mErrores serán considerados actos de traición.\033[0m",
    "\033[92mLa obediencia al protocolo será recompensada por el Partido.\033[0m",
    "",
    "\033[91m=== ¡POR LA PATRIA Y EL PARTIDO! ===\033[0m",
    NULL
  };

  imprimir(intro);
  empezar_partida(mapas, nombre);
}

void mostrar_guia() {
  system("cls"); 

  char *reglas[] = {
    "\033[91m=== REGLAS BÁSICAS DE DOKUMENTY PLEASE ===\033[0m",
    "",
    "\033[97m1. Objetivo del Juego\033[0m",
    "\033[37mEres un oficial en un puesto fronterizo de la Unión Soviética durante la Guerra Fría. Tu misión es:\033[0m",
    "\033[37m- Revisar documentos (pasaportes, DNI, permisos) de civiles, soldados y refugiados.\033[0m",
    "\033[37m- Proteger la seguridad nacional detectando infiltrados o documentos falsos.\033[0m",
    "\033[37m- Equilibrar las órdenes del gobierno con dilemas morales que afectan la historia.\033[0m",
    "",
    "\033[97m2. Cómo Jugar\033[0m",
    "\033[37m- Revisa los documentos de cada persona, comparando nombres, IDs, países y fechas.\033[0m",
    "\033[37m- Asegúrate de que sean válidos (no vencidos, sin errores).\033[0m",
    "\033[37m- Decide: \033[92mAceptar (1)\033[37m para permitir el ingreso o \033[91mRechazar (0)\033[37m con un motivo.\033[0m",
    "\033[37m- Cada día recibes reglas: qué documentos chequear, perfiles sospechosos o restricciones.\033[0m",
    "",
    "\033[97m3. Progresión y Puntuación\033[0m",
    "\033[37m- Cada día atiendes a varias personas y avanzas al siguiente, con reglas más difíciles.\033[0m",
    "\033[37m- Tu \033[92maura\033[37m refleja tu desempeño: sube con decisiones correctas, baja con errores.\033[0m",
    "\033[37m- Guarda tu progreso en cualquier momento y carga partidas anteriores.\033[0m",
    "",
    "\033[97m4. Consecuencias\033[0m",
    "\033[37m- Aceptar a un espía o rechazar a un inocente tiene consecuencias en la historia.\033[0m",
    "\033[37m- Tus elecciones desbloquean diferentes finales según tu aura.\033[0m",
    "",
    "\033[97m5. Interfaz y Controles\033[0m",
    "\033[37m- Usa \033[93mflechas\033[37m para navegar menús y \033[93mEnter\033[37m para seleccionar.\033[0m",
    "\033[37m- Ingresa el nombre de la partida (máximo 50 caracteres).\033[0m",
    "\033[37m- Decide con \033[92m1 (Aceptar)\033[37m o \033[91m0 (Rechazar)\033[37m.\033[0m",
    "",
    "\033[97m6. Eventos Especiales\033[0m",
    "\033[37m- Eventos aleatorios (cambios de reglas o situaciones históricas) afectan el juego.\033[0m",
    "\033[37m- La dificultad crece con más personas y reglas complejas.\033[0m",
    "",
    "\033[91m=== ¡POR LA PATRIA, CAMARADA! ===\033[0m",
    NULL
  };

  imprimir(reglas);

  printf("\nPresiona Enter para volver al menú principal...");
  getchar();
}

void cargar_partida(tipoMapas mapas){
  HashMap *mapa_partidas = mapas.mapa_partidas;
  if(firstMap(mapa_partidas) == NULL){
    printf("\033[91mNo se encontraron partidas guardadas.\033[0m\n");
    return;
  }

  //Mostrar partidas disponibles al jugador.
  printf("\033[97mPartidas guardadas disponibles:\n\n\033[0m");
  int cantidad = sizeMap(mapa_partidas);
  char *nombres[cantidad]; // Array temporal.
  int i = 0;

  Pair *par = firstMap(mapa_partidas);
  while (par != NULL && i < cantidad) {
    nombres[i] = par->key;
    tipoPartida *p = (tipoPartida *) par->value;
    printf("\033[91m%d.\033[0m \033[37m%s\033[0m (Día: \033[37m%d\033[0m)\n", i + 1, nombres[i], p->dia_actual);
    i++;
    par = nextMap(mapa_partidas);
  }

  //Opciones para el jugador
  int opcion;
  printf("\n\033[93mSeleccione una partida por número (1-%d): \033[0m", cantidad);
  scanf("%d", &opcion);
  getchar(); // Limpiar el buffer
  if (opcion < 1 || opcion > cantidad) {
    printf("\033[91mSelección inválida.\033[0m\n");
    return;
  }

  // Obtener la partida seleccionada y error (por si cambiamos algo y da error)
  char *nombre_seleccionado = nombres[opcion - 1];
  Pair *partida_pair = searchMap(mapa_partidas, nombre_seleccionado);
  if (partida_pair == NULL || partida_pair->value == NULL) {
    printf("\033[91mError al cargar la partida.\033[0m\n");
    return;
  }
  
  printf("\033[92m\nIniciando partida \"%s\"...\n\n\033[0m", nombre_seleccionado);
  mostrar_barra_progreso(1);
  empezar_partida(mapas, nombre_seleccionado);
}

Queue *encolar_personas(tipoMapas mapas){
  HashMap *mapa_sujetos = mapas.mapa_sujetos;
  HashMap *mapa_pasaportes = mapas.mapa_pasaportes;
  HashMap *mapa_dni = mapas.mapa_dni;

  srand(time(NULL));

  Queue *cola_personas = queue_create();
  for(short i = 0; i < 7; i++){
    int random = rand() % 1000;
    char ID[10];
    sprintf(ID, "%d", random);
    
    tipoPersona *persona = (tipoPersona *)malloc(sizeof(tipoPersona));
    
    Pair *Sujeto = searchMap(mapa_sujetos, ID);
    persona->sujeto = Sujeto->value;
    eraseMap(mapa_sujetos, ID);
    
    Pair *Pasaporte = searchMap(mapa_pasaportes, ID);
    persona->pasaporte = Pasaporte->value;
    eraseMap(mapa_pasaportes, ID);
    
    Pair *DNI = searchMap(mapa_dni, ID);
    persona->dni = DNI->value;
    eraseMap(mapa_dni, ID);

    queue_insert(cola_personas, persona);
  }
  
  return cola_personas;
}
int main() {
  setlocale(LC_ALL, "es_ES.UTF-8"); // Para que se puedan ver tildes, ñ, y carácteres especiales.

  int seleccion = 0;
  int tecla;
  bool salir = false;

  //Archivo de guardado

  //Información de sujetos
  tipoMapas mapas;
  mapas.mapa_partidas = leer_partidas();
  mapas.mapa_sujetos = leer_sujetos();
  mapas.mapa_pasaportes = leer_pasaportes();
  mapas.mapa_dni = leer_dni();
  
  while (!salir) {
    do {
      menu_principal(seleccion);
      tecla = getch();

      if (tecla == 0 || tecla == 224) { // Tecla especial (como flechas)
        tecla = getch(); // Obtener código real
        if (tecla == ARRIBA && seleccion > 0)
          seleccion--;
        if (tecla == ABAJO && seleccion < 3)
          seleccion++;
      }
    } while (tecla != ENTER);

    // Una vez que se presionó ENTER, limpiar pantalla y mostrar la selección definitiva
    system("cls");
    switch (seleccion) {
    case 0:
      printf("Has seleccionado: Jugar\n");
      crear_partida(mapas);
      break;
    case 1:
      printf("Has seleccionado: Cargar partida\n");
      cargar_partida(mapas);
      break;
    case 2:
      printf("Has seleccionado: Reglas\n");
      mostrar_guia();
      break;
    case 3:
      printf("Saliendo del juego...\n");
      salir = true;
      break;
    }
    if(seleccion != 3) presioneTeclaParaContinuar();
  }

  return 0;
}