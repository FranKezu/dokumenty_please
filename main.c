#include "include/extra.h"
#include "include/hashmap.h"
#include "include/heap.h"
#include "include/list.h"
#include "include/map.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <conio.h>
#include <windows.h> // Solo funciona en windows

#define ARRIBA 72
#define ABAJO 80
#define ENTER 13
// desde aca ---------------------------------------------------------------------

// fue lo mejor que pude hacer ya que la libreria windows.h con conio.h
// lo interpretan como si fuera bytes de unicode o sea como caracteres raros :,v
void mostrar_barra_progreso(float duracion_segundos) {
  int ancho_barra = 30; // Largo de la barra
  int pasos = 40; // Actualizaciones fluidas (en si mientras mas grande este numero mas lento carga la barra de carga igual)
  int espera_ms = (int)(duracion_segundos * 1000 / pasos); // Milisegundos por paso

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


// simulacion de juego

void simulacionxd(){
    system("cls");

    // time_t t = time(NULL);
    // struct tm tm = *localtime(&t);
    // idea para colocar la fecha actual 

    // Texto de introducción tipo Papers, Please
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
        "¡GLORIA AL PARTIDO Y A LA MADRE PATRIA!"
    };


    HANDLE hCon = GetStdHandle(STD_OUTPUT_HANDLE);

    // Color verde tenue
    SetConsoleTextAttribute(hCon, FOREGROUND_GREEN | FOREGROUND_INTENSITY);

    for (int i = 0; i < sizeof(intro) / sizeof(intro[0]); i++) {
        for (int j = 0; intro[i][j] != '\0'; j++) {
            printf("%c", intro[i][j]);
            fflush(stdout);
            // sleep es la pausa entre lineas
            Sleep(15); // efecto máquina de escribir
        }
        printf("\n");
        Sleep(130); // breve pausa entre líneas
    }

    // Espera final y restaurar color
    Sleep(450);
    SetConsoleTextAttribute(hCon, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
    printf("\nPresione una tecla para continuar...");
    getch();
}

// hasta aca ---------------------------------------------------------------------

// Imprime el menú con la opción seleccionada resaltada (con colores)
void mostrar_menu(int seleccion) {
  // Array con las opciones del menú
  char * opciones[] = {
    "Jugar",
    "Continuar partida",
    "Opciones",
    "Salir",
    "Entrar."
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
  printf("=== Menu Principal ===\n\n");

  // Restaurar colores a blanco sobre fondo negro antes de listar opciones
  SetConsoleTextAttribute(hCon, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);

  // 2) OPCIONES

  // Iteramos según la opción en la que estamos parados
  for (int i = 0; i < 5; i++) {
    if (i == seleccion) {
      // Texto negro (0) + fondo blanco (FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE)
      SetConsoleTextAttribute(hCon,
        BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE // fondo blanco
        |
        FOREGROUND_INTENSITY); // texto en negro (sin color de primer plano)
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


// nose a ustedes pero se me hace raro que haya un jugar y un cargar yo eliminaria la opcion de cargar partida u pondria otra cosa en esa seccion 

int main() {
  setlocale(LC_ALL, "es_ES.UTF-8"); // Para que se puedan ver tildes, ñ, y carácteres especiales.
  int seleccion = 0;
  int tecla;

  do {
    mostrar_menu(seleccion);
    tecla = getch();

    if (tecla == 0 || tecla == 224) { // Tecla especial (como flechas)
      tecla = getch(); // Obtener código real
      if (tecla == ARRIBA && seleccion > 0)
        seleccion--;
      if (tecla == ABAJO && seleccion < 4)
        seleccion++;
    }

  } while (tecla != ENTER);

  // Una vez que se presionó ENTER, limpiar pantalla y mostrar la selección definitiva
  system("cls");
  switch (seleccion) {
  case 0:
    printf("Has seleccionado: Jugar\n");
    mostrar_barra_progreso(0.8);
    simulacionxd();
    break;
  case 1:
    printf("Has seleccionado: Continuar partida\n");
    
    break;
  case 2:
    printf("Has seleccionado: Opciones\n");
    break;
  case 3:
    printf("Has seleccionado: Salir\n");
    break;
  }

  // Restaurar color por si se imprime algo más después (opcional)
  // ROJO + VERDE + AZUL = BLANCO
  SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);

  return 0;
}
