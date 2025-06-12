#include "include/extra.h"
#include "include/hashmap.h"
#include "include/heap.h"
#include "include/list.h"
#include "include/map.h"
#include "include/menu.h"

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

void inicio_turno(int dia);

// Estructura que representa los datos de una persona/sujueto que desea ingresar al país
typedef struct {
  int ID; // Identificador único del sujeto.
  int dinero; // Cantidad de dinero que posee la persona.
  char *nombre; // Es el nombre completo del sujeto.
  char *genero; // Indica el género del sujeto.
  char *motivo_viaje; // Contiene la razón del viaje.     
  bool habilitado; // Indica si puede ingresar o no.
} tipoSujeto;

// Estructura que representa a una persona que desea ingresar al país
typedef struct{
  int ID; // Se utiliza para asignarle este DNI al sujeto que tenga la misma ID.      
  char *nombre; // Cantidad de dinero que posee la persona.
  char *documento; // Es el nombre completo del sujeto.
  char *nacimiento; // Fecha de nacimiento.
  char *pais; //  País de origen.
  char *caducidad; // Fecha de vencimiento del documento.
} tipoDNI;

// Estructura que representa el pasaporte de la persona que desea ingresar.
typedef struct {
  int ID; // Se utiliza para asignarle este pasaporte al sujeto que tenga la misma ID.
  char *nombre; // Es el nombre completo del sujeto.
  char *pais; // País emisor del pasaporte.
  char *documento; // Número de documento.
  char *emision; //  Fecha de emisión del pasaporte.
  char *caducidad; // Fecha de expiración del pasaporte.
} tipoPasaporte;

// Almacena los datos de una persona que fue admitida rechazada por el jugador
typedef struct{
  tipoSujeto persona; // Contiene los datos de la persona.
  char *motivo; // Es el nombre completo del struct sujeto.
  int dia; // Día en que se tomó la decisión.
  bool decision; // Registra la decisión del jugador, true si fue admitido, false si fue rechazado.
} tipoProcesado;

// Es el archivo de guardado que se irá actualizando según pasen los días con la información que el jugador vaya progresando.
typedef struct {
  char *nombre_partida; // Nombre de la partida.
  int dia_actual; // Día en que actualmente está la partida.
  int aura; // Representa la puntuación acumulada.
  //tipoProcesado *listaPersonas; // Lista de tipo estructura procesado, que almacenará la información de los sujetos procesados por el jugador.
} tipoPartida;

char *leer_char() {
  char buffer[51];
  while (1) {
    printf("Ingrese el nombre de la partida: ");
    fflush(stdout); // Asegura que el mensaje se imprima antes del input

    if (fgets(buffer, sizeof(buffer), stdin) == NULL) continue;

    buffer[strcspn(buffer, "\n")] = '\0'; // Eliminar salto de línea

    if (strlen(buffer) == 0) {
      printf("El nombre no puede estar vacío.\n");
      continue;
    }

    char * nombre = malloc(strlen(buffer) + 1);
    if (!nombre) {
      printf("Error de memoria.\n");
      exit(1);
    }
    strcpy(nombre, buffer);
    return nombre;
  }
}

HashMap *leer_partidas() {
  FILE *archivo = fopen("data/guardado.csv", "r");

  if (!archivo) {
    printf("Error al abrir el archivo %s\n", "data/guardado.csv");
    return NULL;
  }

  HashMap *mapa = createMap(100);
  char **campos;
  // Leer y descartar encabezado
  campos = leer_linea_csv(archivo, ',');
  while ((campos = leer_linea_csv(archivo, ',')) != NULL) {
    if (!campos[0]) continue;
      tipoPartida *partida = malloc(sizeof(tipoPartida));
      partida->nombre_partida = strdup(campos[0]);
      partida->dia_actual = atoi(campos[1]);
      partida->aura = atoi(campos[2]);
      //partida->listaPersonas = NULL; // No se carga de momento
      insertMap(mapa, partida->nombre_partida, partida);
  }
  fclose(archivo);
  return mapa;
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
  FILE *archivo = fopen("data/guardado.csv", "a");

  // Inicializar la estructura partida
  tipoPartida *nueva = malloc(sizeof(tipoPartida));
  nueva->nombre_partida = strdup(nombre);
  nueva->dia_actual = 1;
  nueva->aura = 0;
  //nueva.listaPersonas = NULL; // Lista vacía

  // Guardar línea con lista vacía
  fprintf(archivo, "%s,%d,%d,\n", nueva->nombre_partida, nueva->dia_actual, nueva->aura);
  fclose(archivo);
  insertMap(mapa_partidas, nueva->nombre_partida, nueva);

  printf("\nPartida '%s' creada exitosamente.\n", nueva->nombre_partida);

  char *intro[] = {
  "Sistema de Control Fronterizo del Estado Socialista",
  "Oficina de Verificación de Documentos y Seguridad del Pueblo",
  "",
  ">> Fecha: 6 de Junio de 1985",
  ">> Localización: Puesto Fronterizo Central de Novagrad",
  "",
  "Camarada, ha sido asignado al puesto de inspección del Partido.",
  "Examine los documentos con máxima vigilancia.",
  "Cada decisión de admisión o rechazo recae bajo su responsabilidad.",
  "Errores serán castigados severamente. Lealtad y precisión serán recompensadas.",
  "",
  "¡GLORIA AL PARTIDO Y A LA MADRE PATRIA!",
  "",
  "Presione una tecla para continuar...",
  NULL}; // => Para decirle a la función hasta donde debe imprimir.
  imprimir(intro);
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

  // Obtener la partida seleccionada
  char *nombre_seleccionado = nombres[opcion - 1];
  Pair *partida_pair = searchMap(mapa_partidas, nombre_seleccionado);
  if (partida_pair == NULL || partida_pair->value == NULL) {
    printf("Error al cargar la partida.\n");
    return;
  }
  tipoPartida *partida = (tipoPartida *) partida_pair->value;
  printf("\nPartida '%s' cargada exitosamente.\n", partida->nombre_partida);
  //empezar_partida(partida);
}

void empezar_partida(){
  //mostrar_menu_dia()
  //guardar_progreso()
}

void mostrar_guia(){
}

int main() {
  setlocale(LC_ALL, "es_ES.UTF-8"); // Para que se puedan ver tildes, ñ, y carácteres especiales.

  int seleccion = 0;
  int tecla;
  bool salir = false;

  HashMap * mapa_partidas = leer_partidas();
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
    presioneTeclaParaContinuar();
  }

  // Restaurar color por si se imprime algo más después (opcional)
  //SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);

  return 0;
}
