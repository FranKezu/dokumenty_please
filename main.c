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

void inicio_turno(int dia);

// Este es el CSV de sujetos/personas.
// AL SUJETO SE LE ASIGNA EL PASAPORTE Y DNI CON MISMA ID (para hacernos el trabajo mas facil para nosotros para identificar)

// sugerencia la key del hashmap puede ser por id

typedef struct {
  int ID;
  int dinero;
  char *nombre;                 
  char *genero;
  char *motivo_viaje;              
  bool habilitado;
} sujeto;

typedef struct{
  int ID;                        
  char *nombre;
  char *documento;
  char *nacimiento;
  char *pais;
  char *caducidad;
} DNI;

typedef struct {
  int ID;
  char *nombre;
  char *pais;
  char *numero;           // Número del pasaporte para comprobar si es que coincide con sujeto.pasaporte
  char *emision;    // Fecha de emisión del pasaporte ejemplo  = 01-01-1980
  char *caducidad; // Fecha de expiración del pasaporte ejemplo = 01-01-1990
} pasaporte;


// Aquí se guardan todas las personas procesadas.
typedef struct{
  sujeto persona; // => Datos de la persona rechazada/aprobada.
  char *motivo; // => Motivo de la decisión (si es que el usuario decidió escribir)
  int dia; // => Día en el que fue admitido/rechazado
  bool decision; // => Decisión del usuario
} procesado;

typedef struct {
  char *nombre;                 // Nombre de la partida
  int dia;                      // Día actual en el juego
  int aura;                     // Puntuación de aura
  int num_personas;             // Número de personas procesadas
  procesado *personas;          // Arreglo dinámico de personas procesadas
} partida;


char* leer_nombre_partida() {
    char buffer[51];
    while (1) {
        printf("Ingrese el nombre de la partida: ");
        fflush(stdout);  // Asegura que el mensaje se imprima antes del input

        if (fgets(buffer, sizeof(buffer), stdin) == NULL) continue;

        buffer[strcspn(buffer, "\n")] = '\0'; // Eliminar salto de línea

        if (strlen(buffer) == 0) {
            printf("El nombre no puede estar vacío.\n");
            continue;
        }

        char *nombre = malloc(strlen(buffer) + 1);
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
  
  partida game;

  char *nombre_partida = leer_nombre_partida();
  
  // Inicializar la estructura partida
  game.nombre = nombre_partida;
  game.dia = 1; // Iniciar en el primer día
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



#define ARRIBA 72
#define ABAJO 80
#define ENTER 13



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
