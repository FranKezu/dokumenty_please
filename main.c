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

#define ARRIBA 72
#define ABAJO 80
#define ENTER 13

// PROTOTIPOS
void empezar_partida(HashMap *, char *);
void crear_partida(HashMap *);
void cargar_partida(HashMap *);
void mostrar_guia();

void empezar_partida(HashMap *mapa_partidas, char *nombre_partida){
  Pair *par = searchMap(mapa_partidas, nombre_partida);
  tipoPartida *partida = (tipoPartida *) par->value;
  printf("\nPartida '%s' cargada exitosamente.\n", partida->nombre_partida);

  //mostrar_menu_dia()
  //guardar_progreso()
}

// Función para crear una nueva partida solicitando el nombre
void crear_partida(HashMap *mapa_partidas) {
  system("cls"); // Limpiar pantalla
  printf("Creando una nueva partida...\n");
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
  empezar_partida(mapa_partidas, nombre);
}

void cargar_partida(HashMap *mapa_partidas){

  if(firstMap(mapa_partidas) == NULL){
    puts("No se encontraron partidas guardadas.");
    return;
  }

  //Mostrar partidas disponibles al jugador.
  puts("Partidas guardadas disponibles:\n");
  int cantidad = sizeMap(mapa_partidas);
  char *nombres[cantidad]; // Array temporal.
  int i = 0;

  Pair *par = firstMap(mapa_partidas);
  while (par != NULL && i < cantidad) {
    nombres[i] = par->key;
    printf("%d. %s\n", i + 1, nombres[i]);
    i++;
    par = nextMap(mapa_partidas);
  }

  //Opciones para el jugador
  int opcion;
  printf("\nSeleccione una partida por número (1-%d): ", cantidad);
  scanf("%d", &opcion);
  getchar(); // Limpiar el buffer
  if (opcion < 1 || opcion > cantidad) {
    printf("Selección inválida.\n");
    return;
  }

  // Obtener la partida seleccionada y error (por si cambiamos algo y da error)
  char *nombre_seleccionado = nombres[opcion - 1];
  Pair *partida_pair = searchMap(mapa_partidas, nombre_seleccionado);
  if (partida_pair == NULL || partida_pair->value == NULL) {
    printf("Error al cargar la partida.\n");
    return;
  }
  
  empezar_partida(mapa_partidas, nombre_seleccionado);
}

void mostrar_guia(){
}

int main() {
  setlocale(LC_ALL, "es_ES.UTF-8"); // Para que se puedan ver tildes, ñ, y carácteres especiales.

  int seleccion = 0;
  int tecla;
  bool salir = false;

  HashMap * mapa_partidas = leer_partidas();

  //HashMap *mapa_sujetos = createHashMap();
  //HashMap *mapa_pasaportes = createHashMap();
  //HashMap *mapa_dnis = createHashMap();
  

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
      crear_partida(mapa_partidas);
      break;
    case 1:
      printf("Has seleccionado: Cargar partida\n");
      cargar_partida(mapa_partidas);
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

  // Restaurar color por si se imprime algo más después (opcional)
  //SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);

  return 0;
}
