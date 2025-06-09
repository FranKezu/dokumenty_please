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
  char *numero; // Número del pasaporte.
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
  tipoProcesado *personas; // Lista de tipo estructura procesado, que almacenará la información de los sujetos procesados por el jugador.
} tipoPartida;

char * leer_nombre_partida() {
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

// Función para crear una nueva partida solicitando el nombre
void crear_partida_nueva() {
  system("cls"); // Limpiar pantalla
  printf("Creando una nueva partida...\n");
  
  tipoPartida game;
  char *nombre_partida = leer_nombre_partida();
  
  // Inicializar la estructura partida
  game.nombre_partida = nombre_partida;
  game.dia_actual = 1; // Iniciar en el primer día
  game.aura = 0; // Iniciar con aura en 0
  game.personas = NULL; // Sin personas procesadas inicialmente

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
  NULL // => Para decirle a la función hasta donde debe imprimir.
  };

  mostrar_barra_progreso(0.5);
  imprimir(intro);
  inicio_turno(1);
}

// Función para crear una nueva partida solicitando el nombre
void crear_partida_nueva() {
  system("cls"); // Limpiar pantalla
  printf("Creando una nueva partida...\n");
  
  tipoPartida game;

  char *nombre_partida = leer_nombre_partida();
  
  // Inicializar la estructura partida
  game.nombre_partida = nombre_partida;
  game.dia_actual = 1; // Iniciar en el primer día
  game.aura = 0; // Iniciar con aura en 0
  game.personas = NULL; // Sin personas procesadas inicialmente

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
  NULL // => Para decirle a la función hasta donde debe imprimir.
  };

  mostrar_barra_progreso(0.5);
  imprimir(intro);
  inicio_turno(1);
}


/*Estas fueron las personas que procesaste:
//IDEA DE TEXTO PARA MOSTRAR AL FINAL DEL JUEGO (CUANDO GANA O PIERDE) es como un resumen

Hugo Palomino
Razón: enemigo del estado de chile
FALLA, debiste dejar pasar a Hugo, ya que estaba habilitado, ahora se morirá de frío en las afueras
-1000 aura.

Ariel Leiva
Razón: enemigo del estado de chile
CORRECTO, ariel pudo reunirse con su familiar, era una persona limpia.
+10000 aura.

Franco Bernal
Razón: persona normal
FALLA, debiste rechazar la entrada a Franco, llevaba una pistola y mató a dos bebés.
-1000 aura.

*/

int main() {
  setlocale(LC_ALL, "es_ES.UTF-8"); // Para que se puedan ver tildes, ñ, y carácteres especiales.

  int seleccion = 0;
  int tecla;

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
    
    crear_partida_nueva();
    break;
  case 1:
    printf("Has seleccionado: Cargar partida\n");
    //cargar_partida();
    break;
  case 2:
    printf("Has seleccionado: Reglas\n");
    //mostrar_reglas();
    break;
  case 3:
    printf("Saliendo del juego...\n");
    break;
  }

  // Restaurar color por si se imprime algo más después (opcional)
  //SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);

  return 0;
}
