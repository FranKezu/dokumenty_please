#include "../include/menu.h"
#include "../include/hashmap.h"
#include "../include/queue.h"
#include "../include/extra.h"
#include "../estructuras.h"
#include "../include/game.h"

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include <mmsystem.h>
#include <stdbool.h>

#pragma comment(lib, "Winmm.lib")

void mostrar_barra_progreso(float segundos) {
  int ancho_barra = 30; // Largo de la barra
  int pasos = 40; // Actualizaciones fluidas
  int espera_ms = (int)(segundos * 1000 / pasos); // Milisegundos por paso

  HANDLE hCon = GetStdHandle(STD_OUTPUT_HANDLE); // Handle de la consola

  for (int i = 0; i <= pasos; i++) {
    int completado = (i * ancho_barra) / pasos; // Bloques completados

    // Colores estilo soviético: alternar rojo intenso y amarillo brillante
    int color = (i % 2 == 0) ? (FOREGROUND_RED | FOREGROUND_INTENSITY) : // Rojo intenso
                              (FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY); // Amarillo brillante

    SetConsoleTextAttribute(hCon, color);

    // Imprimir barra con texto y efecto
    printf("\rCargando... |=");
    for (int j = 0; j < completado; j++) printf("=");
    if (completado < ancho_barra) printf(">"); // Indicador dinámico
    for (int j = completado + 1; j < ancho_barra; j++) printf("-");
    printf("=|");
    fflush(stdout);

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


void mostrar_DNI(tipoDNI *dni){
  system("cls");

  printf("\033[93m╔═════════════════════════════════════════════════════════════════════════════════════════════╗\n");
  printf("║              ☭ ДОКУМЕНТ ЛИЧНОСТИ СОЮЗА СОВЕТСКИХ СОЦИАЛИСТИЧЕСКИХ РЕСПУБЛИК ☭               ║\n");
  printf("║              ☭ IDENTITY DOCUMENT OF THE UNION OF SOVIET SOCIALIST REPUBLICS ☭               ║\n");
  printf("╠═════════════════════════════════════════════════════════════════════════════════════════════╣\n");
  printf("║                                               │                                             ║\n");
  printf("║                 #######                       │       NOMBRE:        \033[37m%-23s\033[93m║\n", dni->nombre);
  printf("║               ###########                     │       PAÍS:          \033[37m%-23s\033[93m║\n", dni->pais);
  printf("║              #############                    │       SEXO:          \033[37m%-23s\033[93m║\n",dni->genero);
  printf("║             ###############                   │       N° DOCUMENTO:  \033[37m%-23s\033[93m║\n", dni->documento);
  printf("║             ###############                   │       NACIMIENTO:    \033[37m%-23s\033[93m║\n", dni->nacimiento);
  printf("║             ###############                   │       VÁLIDO HASTA:  \033[37m%-23s\033[93m║\n", dni->caducidad);
  printf("║             ###############                   │                                             ║\n");
  printf("║              #############                    │       8888888b.  888b    888 8888888        ║\n");
  printf("║               ###########                     │       888  \"Y88b 8888b   888   888          ║\n");
  printf("║                #########                      │       888    888 88888b  888   888          ║\n");
  printf("║                #########                      │       888    888 888Y88b 888   888          ║\n");
  printf("║             ################                  │       888    888 888 Y88b888   888          ║\n");
  printf("║          #####################                │       888    888 888  Y88888   888          ║\n");
  printf("║       ###########################             │       888  .d88P 888   Y8888   888          ║\n");
  printf("║      #############################            │       8888888P\"  888    Y888 8888888        ║\n");
  printf("╠═════════════════════════════════════════════════════════════════════════════════════════════╣\n");
  printf("║                        ☭ ВЫДАН МИНИСТЕРСТВОМ ВНУТРЕННИХ ДЕЛ СССР ☭                          ║\n");
  printf("║                     ☭ AUTHORIZED BY THE SOVIET MINISTRY OF SECURITY ☭                       ║\n");
  printf("╚═════════════════════════════════════════════════════════════════════════════════════════════╝\033[0m\n");
}

void mostrar_pasaporte(tipoPasaporte *pasaporte){
  system("cls");

  printf("\033[91m╔══════════════════════════════════════════════════════════════════════════════════════════════════╗\n");
  printf("║                        ☭ ПАСПОРТ СОЮЗА СОВЕТСКИХ СОЦИАЛИСТИЧЕСКИХ РЕСПУБЛИК ☭                    ║\n");
  printf("║                        ☭ PASSPORT OF THE UNION OF SOVIET SOCIALIST REPUBLICS ☭                   ║\n");
  printf("╠══════════════════════════════════════════════════════════════════════════════════════════════════╣\n");
  printf("║███████████████████████████████████████████████│                                                  ║\n");
  printf("║█████████████████       ███████████████████████│      NOMBRE:        \033[37m%-29s\033[91m║\n", pasaporte->nombre);
  printf("║███████████████           █████████████████████│      PAÍS:          \033[37m%-29s\033[91m║\n", pasaporte->pais);
  printf("║██████████████             ████████████████████│      N° DNI:        \033[37m%-29s\033[91m║\n", pasaporte->documento);
  printf("║█████████████               ███████████████████│      N° PASAPORTE:  \033[37m%-29s\033[91m║\n", pasaporte->pasaporte);
  printf("║█████████████               ███████████████████│      VÁLIDO HASTA:  \033[37m%-29s\033[91m║\n", pasaporte->caducidad);
  printf("║█████████████               ███████████████████│                                                  ║\n");
  printf("║█████████████               ███████████████████│                                                  ║\n");
  printf("║██████████████             ████████████████████│      ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★           ║\n");
  printf("║███████████████           █████████████████████│      ★                               ★           ║\n");
  printf("║████████████████         ██████████████████████│      ★ Официальный паспорт СССР      ★           ║\n");
  printf("║████████████████         ██████████████████████│      ★ Official passport of the USSR ★           ║\n");
  printf("║█████████████                ██████████████████│      ★                               ★           ║\n");
  printf("║██████████                     ████████████████│      ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★           ║\n");
  printf("║███████                           █████████████│                                                  ║\n");
  printf("║██████                             ████████████│                                                  ║\n");
  printf("╠══════════════════════════════════════════════════════════════════════════════════════════════════╣\n");
  printf("║                           ☭ ВЫДАН МИНИСТЕРСТВОМ ВНУТРЕННИХ ДЕЛ СССР ☭                            ║\n");
  printf("║                        ☭ AUTHORIZED BY THE SOVIET MINISTRY OF SECURITY ☭                         ║\n");
  printf("╚══════════════════════════════════════════════════════════════════════════════════════════════════╝\033[0m\n");
}

void mostrar_sello(tipoPersona *persona, tipoPartida *partida, bool aprobado) {
  char texto_aprobado[50] = "A P R O B A D O";
  char texto_rechazado[50] = "R E C H A Z A D O";

  printf("\n");
  if (aprobado) {
    printf("\033[32m"); // Verdegcc main.c src\extra.c src\hashmap.c src\list.c src\menu.c src\queue.c src\game.c -o bin\run.exe
    printf("~~ %6s ~~\n", persona->dni->nombre);
    printf("~~ %6s ~~\n\n", texto_aprobado);
  } else {
    printf("\033[91m"); // Rojo
    printf("~~ %6s ~~\n", persona->dni->nombre);
    printf("~~ %6s ~~\n\n", texto_rechazado);
  }
  //calcular_habilitado(tipoPersona * persona, int dia)
  persona->sujeto->habilitado = calcular_habilitado(persona, partida->dia_actual);
  if(persona->sujeto->habilitado){
    partida->aura += 200;
    printf("Correcto, buen trabajo\n\n");
  }  
  else{
    partida->aura -= 200;
    printf("Incorrecto, dejaste pasar a una persona no habilitada\n\n");
  }
  printf("\033[0m"); // Reset
}

void calcular_final(tipoPartida *partida){
  bool terminado = false;
  if(partida->aura <= -2000){
    char *final_traidor[] = {
    "\033[91m=== COMITÉ DE SEGURIDAD DEL ESTADO DE LA UNIÓN SOVIÉTICA ===\033[0m",
    "\033[97mInforme Final de Evaluación Disciplinaria\033[0m",
    "",
    "\033[93m>> Estado del aura: -2000 (peligro nacional)\033[0m",
    "",
    "\033[91m>>> Camarada:\033[0m",
    "\033[37mSus decisiones han puesto en riesgo la integridad de nuestra gloriosa nación.\033[0m",
    "\033[37mHa permitido el ingreso de enemigos del pueblo, saboteadores y traidores.\033[0m",
    "\033[37mEl Comité Central lo considera una amenaza para la seguridad estatal.\033[0m",
    "",
    "\033[91mHa sido destituido de su cargo y será juzgado por crímenes contra la patria.\033[0m",
    "",
    "\033[91m=== EL ESTADO NO OLVIDA ===\033[0m",
    NULL};
    imprimir(final_traidor);
    terminado = true;
  }

  if(partida->aura >= 2000){
    char *final_heroe[] = {
    "\033[91m=== COMITÉ DE SEGURIDAD DEL ESTADO DE LA UNIÓN SOVIÉTICA ===\033[0m",
    "\033[97mReconocimiento Oficial del Partido\033[0m",
    "",
    "\033[93m>> Estado del aura: +2000 (excelencia patriótica)\033[0m",
    "",
    "\033[91m>>> Camarada:\033[0m",
    "\033[37mSu incansable labor ha salvaguardado la frontera de la URSS.\033[0m",
    "\033[37mHa identificado y neutralizado amenazas con disciplina ejemplar.\033[0m",
    "\033[37mEl Partido lo reconoce como un verdadero defensor del pueblo.\033[0m",
    "",
    "\033[92mHa sido condecorado con la Medalla al Mérito Fronterizo.\033[0m",
    "\033[92mSe le ha asignado una vivienda digna y raciones dobles para su familia.\033[0m",
    "",
    "\033[91m=== ¡GLORIA AL CAMARADA INSPECTOR! ===\033[0m",
    NULL};
    imprimir(final_heroe);
    terminado = true;
  }

  if(partida->dia_actual == 31){
    char *final_retiro[] = {
    "\033[91m=== COMITÉ DE SEGURIDAD DEL ESTADO DE LA UNIÓN SOVIÉTICA ===\033[0m",
    "\033[97mInforme de Cese de Funciones\033[0m",
    "",
    "\033[93m>> Tiempo de servicio: 11 días continuos\033[0m",
    "",
    "\033[91m>>> Camarada:\033[0m",
    "\033[37mSu período de asignación en el puesto fronterizo ha concluido.\033[0m",
    "\033[37mEl Comité agradece sus servicios, sean cuales hayan sido sus resultados.\033[0m",
    "\033[37mSerá relevado por otro inspector para continuar la vigilancia del puesto.\033[0m",
    "",
    "\033[92mPuede regresar a su hogar bajo supervisión del Partido.\033[0m",
    "",
    "\033[91m=== LA FRONTERA SIEMPRE VIGILA ===\033[0m",
    NULL};
    imprimir(final_retiro);
    terminado = true;
  }

  if(terminado){
    eliminar_partida(partida->nombre_partida);
    exit(1);
  }
}

void mostrar_reglas(int dia) {
    // Título principal en rojo claro
    printf("\033[91mReglas de Inmigración - Día %d\033[0m\n", dia);

    // Reglas para el día 1
    if (dia >= 1) {
        printf("\033[97m1.\033[0m \033[37mNombres deben coincidir en documentos.\033[0m\n");
        printf("\033[97m2.\033[0m \033[37mRechazar motivos de turismo.\033[0m\n");
    }

    // Reglas para el día 2
    if (dia >= 2) {
        printf("\033[97m3.\033[0m \033[37mDNI y pasaporte no deben estar vencidos.\033[0m\n");
        printf("\033[97m4.\033[0m \033[37mNúmeros de documentos deben coincidir.\033[0m\n");
    }

    // Reglas para el día 3
    if (dia >= 3) {
        printf("\033[97m5.\033[0m \033[37mRechazar pasaportes con la letra 'O'.\033[0m\n");
        printf("\033[97m6.\033[0m \033[37mProhibir ingreso a nacidos en agosto.\033[0m\n");
    }

    // Reglas para el día 4
    if (dia >= 4) {
        printf("\033[97m7.\033[0m \033[37mProhibir ingreso a nacionalidad 'Letonia'.\033[0m\n");
        printf("\033[97m8.\033[0m \033[37mRechazar a quienes tengan menos de 800 rublos.\033[0m\n");
        printf("\033[97m9.\033[0m \033[37mRechazar a quienes tengan más de 2500 rublos.\033[0m\n");
        printf("\033[97m10.\033[0m \033[37mRechazar motivos familiares.\033[0m\n");
    }

    // Instrucción final en verde
    printf("\033[92m[Enter] para continuar\033[0m\n");
}

void menu_acciones(Queue *cola, tipoPersona *persona, tipoPartida *partida) {

  char opcion;
  do {
    system("cls");
    printf("\033[93m\nDÍA \033[37m%d\n\033[93m\n\033[0m", partida->dia_actual);
    mostrar_reglas(partida->dia_actual);
    printf("\033[91m=== MENÚ DEL VEREDICTO ===\n\n\033[0m");
    printf("\033[97mInformación del sujeto\n\033[0m");
    printf("\033[37mNombre: %s\n", persona->sujeto->nombre);
    printf("País: %s\n\033[0m\n", persona->dni->pais);
    printf("Dinero: %d\n", persona->sujeto->dinero);
    printf("Motivo de viaje: %s\n", persona->sujeto->motivo);
    printf("\033[37m1. Inspeccionar DNI\n");
    printf("2. Inspeccionar Pasaporte\n\033[0m");
    printf("\033[92m3. Aprobar\n");
    printf("\033[91m4. Rechazar\n\033[0m"); 
    printf("\033[93mIngrese su opción: \033[0m");
    scanf(" %c", &opcion);

    switch (opcion) {
    case '1':
      mostrar_DNI(persona->dni);
      break;
    case '2':
      mostrar_pasaporte(persona->pasaporte);
      break;
    case '3':
      mostrar_sello(persona, partida, true);
      break;
    case '4':
      mostrar_sello(persona, partida, false);
      break;
    default:
      printf("\n Opción no válida. Intente de nuevo.\n");
      break;
    }
    calcular_final(partida);
    presioneTeclaParaContinuar();
  } while (opcion != '3' && opcion != '4');
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
    "\033[37m- Si tu aura cae a \033[91m-2000 o menos\033[37m, pierdes y la partida se elimina.\033[0m",
    "\033[37m- Si tu aura alcanza \033[92m+2000 o más\033[37m, ganas la partida.\033[0m",
    "\033[37m- Tu progreso se guarda únicamente al finalizar el día.\033[0m",
    "\033[37m- Carga partidas anteriores desde el menú principal.\033[0m",
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
    NULL};

  imprimir(reglas);

  printf("\nPresiona Enter para volver al menú principal...");
  getchar();
}
