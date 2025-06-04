#include <stdio.h>
#include <conio.h>
#include <windows.h> // Solo funciona en windows

#define ARRIBA 72
#define ABAJO 80
#define ENTER 13

// Imprime el menú con la opción seleccionada resaltada (con colores)
void mostrar_menu(int seleccion) {
  // Array con las opciones del menú
  char * opciones[] = {
    "Jugar",
    "Cargar partida",
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

int main() {
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
    break;
  case 1:
    printf("Has seleccionado: Cargar partida\n");
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
