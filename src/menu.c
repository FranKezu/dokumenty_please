#include "../include/menu.h"
#include "../include/hashmap.h"
#include "../include/queue.h"
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


// esta funcion de igual forma es un boceto ya que no entendi muy bien como van a querer contar los dias 
// si con un numero fijo de atender sujetos o de otra forma personalmente no entendi como quieren hacer eso :c

/*
bool leer_archivo_sujetos(const char *nombre_archivo, HashMap *mapa_sujetos, Queue *cola_sujetos) {
    FILE *archivo = fopen(nombre_archivo, "r");
    if (!archivo) {
        printf("Error: No se pudo abrir %s\n", nombre_archivo);
        return false;
    }
    char buffer[256];
    // Saltar primera línea (encabezado)
    if (!fgets(buffer, sizeof(buffer), archivo)) {
        fclose(archivo);
        return false;
    }
    while (fgets(buffer, sizeof(buffer), archivo)) {
        buffer[strcspn(buffer, "\n")] = 0;  // Eliminar salto de línea
        tipoSujeto *sujeto = malloc(sizeof(tipoSujeto));
        if (sujeto == NULL) {
            fclose(archivo);
            return false; // Falla asignación memoria
        }
        char *token = strtok(buffer, ",");
        if (!token) { free(sujeto); continue; }
        sujeto->ID = atoi(token);
        token = strtok(NULL, ",");
        if (!token) { free(sujeto); continue; }
        sujeto->dinero = atoi(token);
        token = strtok(NULL, ",");
        if (!token) { free(sujeto); continue; }
        sujeto->nombre = strdup(token);
        token = strtok(NULL, ",");
        if (!token) { free(sujeto->nombre); free(sujeto); continue; }
        sujeto->genero = strdup(token);
        token = strtok(NULL, ",");
        if (!token) {
            free(sujeto->genero);
            free(sujeto->nombre);
            free(sujeto);
            continue;
        }
        sujeto->motivo_viaje = strdup(token);
        token = strtok(NULL, ",");
        if (!token) {
            free(sujeto->motivo_viaje);
            free(sujeto->genero);
            free(sujeto->nombre);
            free(sujeto);
            continue;
        }
        sujeto->habilitado = atoi(token);
        // Insertar sujeto en hashmap con clave ID. Usar puntero como clave es inseguro, usar ID convertido a cadena o wrapper:
        // Para evitar problema de direcciones, creamos una clave estática para ID:
        // Pero para esta función, uso int * clave dinámica:
        int *clave_id = malloc(sizeof(int));
        if (!clave_id) {
            // Liberar strings y sujeto
            free(sujeto->motivo_viaje);
            free(sujeto->genero);
            free(sujeto->nombre);
            free(sujeto);
            fclose(archivo);
            return false;
        }
        *clave_id = sujeto->ID;
        insertMap(mapa_sujetos, (char *)clave_id, sujeto);
        // Encolar sujeto en la cola
        queue_insert(cola_sujetos, sujeto);
    }
    fclose(archivo);
    return true;
}*/


/* no se me ocurre como enlazar la partida con los csv pero este seria un boceto como para identificar si es que se leen bien las colas aunque a mi ni me meo la wea

void empezar_partida(HashMap *mapa_partidas, HashMap *mapa_sujetos, HashMap *mapa_dnis, HashMap *mapa_pasaportes, char *nombre_partida) {
    Pair *par = searchMap(mapa_partidas, nombre_partida);
    tipoPartida *partida = (tipoPartida *) par->value;
    printf("\nPartida '%s' cargada exitosamente.\n", partida->nombre_partida);
    
    // Cargar sujetos del día actual
    Queue *cola_sujetos = cargar_sujetos_del_dia(partida->dia_actual, mapa_sujetos, mapa_dnis, mapa_pasaportes);
    
    // Verificar si la cola de sujetos se ha cargado correctamente
    if (cola_sujetos == NULL || isEmptyQueue(cola_sujetos)) {
        printf("No se han cargado sujetos para el día %d.\n", partida->dia_actual);
    } else {
        printf("Sujetos cargados para el día %d:\n", partida->dia_actual);
        // Mostrar información de los sujetos sin eliminarlos
        mostrar_sujetos_en_cola(cola_sujetos);
    }
}

*/