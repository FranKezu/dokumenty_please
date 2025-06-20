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

#pragma comment(lib, "Winmm.lib")

void mostrar_barra_progreso(float segundos) {
  int ancho_barra = 30; // Largo de la barra
  int pasos = 40; // Actualizaciones fluidas (en si mientras mas grande este numero mas lento carga la barra de carga igual)
  int espera_ms = (int)(segundos * 1000 / pasos); // Milisegundos por paso

  // por lo que entendi se usa para poder cambiar el color del texto es un enlace 
  HANDLE hCon = GetStdHandle(STD_OUTPUT_HANDLE); // Handle de la consola

  for (int i = 0; i <= pasos; i++) {
    int completado = (i * ancho_barra) / pasos; // Bloques completados
    // Alternar colores para efecto dinámico
    int color = (i % 2 == 0) ? (FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY) : // Cian
                              (FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY); // Magenta
    SetConsoleTextAttribute(hCon, color);

    // Imprimir barra con texto y efecto
    printf("\rCargando nivel... |=");
    for (int j = 0; j < completado; j++) printf("=");
    if (completado < ancho_barra) printf(">"); // Indicador dinámico
    for (int j = completado + 1; j < ancho_barra; j++) printf("-");
    printf("=|");
    fflush(stdout);

    // por eso si aumentamos pasos se demora mas porque sleep su calculo es mayor
    Sleep(espera_ms); // Espera en milisegundos
  }

  // Restaurar color blanco y añadir salto de línea
  SetConsoleTextAttribute(hCon, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
  printf("\n");
}

void imprimir(char **texto) {
  system("cls");
  HANDLE hCon = GetStdHandle(STD_OUTPUT_HANDLE);
  SetConsoleTextAttribute(hCon, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
  for (int i = 0; texto[i] != NULL; i++) {
    for (int j = 0; texto[i][j] != '\0'; j++) {
      printf("%c", texto[i][j]);
      fflush(stdout);
      Sleep(15);
    }
    printf("\n");
    Sleep(130);
  }

  Sleep(450);
  SetConsoleTextAttribute(hCon, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
  getch();
}

// Imprime el menú con la opción seleccionada resaltada (con colores)
void menu_principal(int seleccion) {
  // Array con las opciones del menú
  char * opciones[] = {
    "Empezar partida nueva",
    "Cargar partida",
    "Reglas",
    "Salir del juego",
  };

  // Obtener handle de la consola (Para editar colores)
  HANDLE hCon = GetStdHandle(STD_OUTPUT_HANDLE);

  // Limpiar pantalla (podrías usar la función del profe, pero es lo mismo)
  system("cls");

  // 1) TITULO

  //hcon corresponde a la linea print donde estamos parados, FOREGROUND corresponde a los colores del texto,
  //BACKGROUND corresponde a los colores del fondo del texto.
  //Podemos usar más de un FOREGROUND/BACKGROUND para crear combinaciones de colores.

  SetConsoleTextAttribute(hCon, FOREGROUND_RED | FOREGROUND_INTENSITY | BACKGROUND_BLUE);
  printf("=== Dokumenty Please ===\n\n");

  // Restaurar colores a blanco sobre fondo negro antes de listar opciones
  SetConsoleTextAttribute(hCon, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);

  // 2) OPCIONES

  // Iteramos según la opción en la que estamos parados
  for (int i = 0; i < 4; i++) {
    if (i == seleccion) {
      // Texto negro (0) + fondo blanco (FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE)
      SetConsoleTextAttribute(hCon,
        BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | FOREGROUND_INTENSITY); // texto en negro (sin color de primer plano)
      printf(">> %s <<\n", opciones[i]);
      // Volver a restablecer colores a blanco sobre fondo negro para la siguiente iteración
      SetConsoleTextAttribute(hCon, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
    } else {
      // Opción no seleccionada: texto blanco sobre fondo negro
      printf("   %s\n", opciones[i]);
    }
  }
  // Al salir de la función, los colores ya quedaron como los de texto blanco/fondo negro
}

void inicio_turno(int dia) {
  system("cls"); // Limpiar pantalla
  printf("  Inicializando cabina de control");
  for (int i = 0; i < 3; i++) {
      Sleep(500);
      printf(".");
  }
  printf("\n");
  Sleep(600);
  printf("  Preparando sellos oficiales y escáner");
  for (int i = 0; i < 3; i++) {
    Sleep(500);
    printf(".");
    }
  printf("\n");
  Sleep(1000);
  printf("\n  >>> Puesto de inspección operativo.\n");
  Sleep(1000);
  printf("  >>> Puede comenzar el control de documentos.\n\n");
  Sleep(1500);
  printf("\n*Sonido metálico de puerta abriéndose lentamente*\n");
  Sleep(1500);
    /*
    if (!PlaySound(TEXT("puerta.wav"), NULL, SND_FILENAME | SND_ASYNC)) {
        printf("[PUERTA]: *Error al reproducir el sonido*\n");
    } else {
        printf("[PUERTA]: *Sonido de puerta reproduciéndose*\n");
    }
    */
  Sleep(1000); 
  printf("Un visitante entra lentamente al puesto de control...\n");
  Sleep(2000);
}

void mostrar_DNI(tipoDNI *dni){
  system("cls");
  printf("╔════════════════════════════════════════════════════════════════════════════════════════════╗\n");
  printf("║                                               │                                            ║\n");
  printf("║                 #######                       │       NOMBRE:        %-22s║\n", dni->nombre);
  printf("║               ###########                     │       RUT / ID:      %-22s║\n", dni->documento);
  printf("║              #############                    │       NACIMIENTO:    %-22s║\n", dni->nacimiento);
  printf("║             ###############                   │       NACIONALIDAD:  %-22s║\n", dni->pais);
  printf("║             ###############                   │       SEXO:          MASCULINO             ║\n");
  printf("║             ###############                   │       VÁLIDO HASTA:  %-22s║\n", dni->caducidad);
  printf("║             ###############                   │                                            ║\n");
  printf("║              #############                    │       8888888b.  888b    888 8888888       ║\n");
  printf("║               ###########                     │       888  \"Y88b 8888b   888   888         ║\n");
  printf("║                #########                      │       888    888 88888b  888   888         ║\n");
  printf("║                #########                      │       888    888 888Y88b 888   888         ║\n");
  printf("║             ################                  │       888    888 888 Y88b888   888         ║\n");
  printf("║          #####################                │       888    888 888  Y88888   888         ║\n");
  printf("║       ###########################             │       888  .d88P 888   Y8888   888         ║\n");
  printf("║      #############################            │       8888888P\"  888    Y888 8888888       ║\n");
  printf("╚════════════════════════════════════════════════════════════════════════════════════════════╝\n");
}

void mostrar_pasaporte(tipoPasaporte *pasaporte){
  printf("╔════════════════════════════════════════════════════════════════════════════════════════════╗\n");
  printf("║                     ☭ ПАСПОРТ СОЮЗА СОВЕТСКИХ СОЦИАЛИСТИЧЕСКИХ РЕСПУБЛИК ☭                 ║\n");
  printf("║                     ☭ PASSPORT OF THE UNION OF SOVIET SOCIALIST REPUBLICS ☭                ║\n");
  printf("╠════════════════════════════════════════════════════════════════════════════════════════════╣\n");
  printf("║███████████████████████████████████████████████│                                            ║\n");
  printf("║█████████████████       ███████████████████████│       NOMBRE:        %-22s║\n", pasaporte->nombre);
  printf("║███████████████           █████████████████████│       PAIS:          %-22s║\n", pasaporte->pais);
  printf("║██████████████             ████████████████████│       DOCUMENTO:     %-22s║\n", pasaporte->documento);
  printf("║█████████████               ███████████████████│       PASAPORTE:     %-22s║\n", pasaporte->pasaporte);
  printf("║█████████████               ███████████████████│       EMISIÓN:       %-22s║\n", pasaporte->emision);
  printf("║█████████████               ███████████████████│       VÁLIDO HASTA:  %-22s║\n", pasaporte->caducidad);
  printf("║█████████████               ███████████████████│                                            ║\n");
  printf("║██████████████             ████████████████████│       ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★    ║\n");
  printf("║███████████████           █████████████████████│       ★                               ★    ║\n");
  printf("║████████████████         ██████████████████████│       ★ Официальный паспорт СССР      ★    ║\n");
  printf("║████████████████         ██████████████████████│       ★ Official passport of the USSR ★    ║\n");
  printf("║█████████████                ██████████████████│       ★                               ★    ║\n"); 
  printf("║██████████                     ████████████████│       ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★    ║\n");
  printf("║███████                           █████████████│                                            ║\n");
  printf("║██████                             ████████████│                                            ║\n");
  printf("╠════════════════════════════════════════════════════════════════════════════════════════════╣\n");
  printf("║                        ☭ ВЫДАН МИНИСТЕРСТВОМ ВНУТРЕННИХ ДЕЛ СССР ☭                         ║\n");
  printf("║                     ☭ AUTHORIZED BY THE SOVIET MINISTRY OF SECURITY ☭                      ║\n");
  printf("╚════════════════════════════════════════════════════════════════════════════════════════════╝\n");
}

void menu_acciones(Queue *cola, tipoPersona *persona) {
  char opcion;
  int aprobado = 0; // 1 para aprobar, 0 para rechazar
  do {
    system("cls");
    printf("\n=== Menú de Veredicto ===\n");
    printf("DATOS DEL SUJETO\n");
    printf("%s\n",persona->sujeto->nombre);
    printf("%s\n",persona->dni->pais);
    printf("1. Inspeccionar DNI\n");
    printf("2. Inspeccionar Pasaporte\n");
    printf("3. Aprobar\n");
    printf("4. Rechazar\n");
    printf("Ingrese su opción:");
    scanf(" %c", & opcion);

    switch (opcion) {
    case '1':
      mostrar_DNI(persona->dni);
      break;
    case '2':
      mostrar_pasaporte(persona->pasaporte);
      break;
    case '3':
      printf("\nHas aprobado a %s\n", persona->sujeto->nombre);
      break;
    case '4':
      printf("\nHas rechazado a %s\n", persona->sujeto->nombre);
      break;
    default:
      printf("\n Opción no válida. Intente de nuevo.\n");
      break;
    }
    presioneTeclaParaContinuar();
  } while (opcion != '3' && opcion != '4');
}

