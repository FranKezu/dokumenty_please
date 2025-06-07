#include "include/extra.h"
#include "include/hashmap.h"
#include "include/heap.h"
#include "include/list.h"
#include "include/map.h"
#include "include/menu.h"


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <conio.h>
#include <windows.h>



#define ARRIBA 72
#define ABAJO 80
#define ENTER 13

void inicio_turno(int dia);

void partida_nueva(){

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
}

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
    partida_nueva();
    // si se les ocurre como vaya avanzando los dias porque coloque como valor el 1 del primer dia como recien se inicia la partida
    inicio_turno(1);
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
