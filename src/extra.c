#include "../include/extra.h"
#include "../include/hashmap.h"
#include "../estructuras.h"

#define MAX_LINE_LENGTH 1024
#define MAX_FIELDS 300

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
  FILE *archivo = fopen("data/partida.csv", "r");

  if (!archivo) {
    printf("Error al abrir el archivo %s\n", "data/partida.csv");
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

char **leer_linea_csv(FILE *archivo, char separador) {
  static char linea[MAX_LINE_LENGTH];
  static char *campos[MAX_FIELDS];
  char *ptr, *start;
  int idx = 0;

  if (fgets(linea, MAX_LINE_LENGTH, archivo) == NULL) {
    return NULL; // No hay más líneas para leer
  }

  // Eliminar salto de linea
  linea[strcspn(linea, "\n")] = '\0';

  ptr = start = linea;
  while (*ptr) {
    if (idx >= MAX_FIELDS - 1)
      break;

    if (*ptr == '\"') { // Inicio de un campo entrecomillado
      start = ++ptr;    // Saltar la comilla inicial
      while (*ptr && !(*ptr == '\"' && *(ptr + 1) == separador))
        ptr++;
    } else { // Campo sin comillas
      start = ptr;
      while (*ptr && *ptr != separador)
        ptr++;
    }

    if (*ptr) {
      *ptr = '\0'; // Reemplazar comilla final o separador por terminación
      ptr++;
      if (*ptr == separador)
        ptr++;
    }

    // Quitar comilla final si existe
    if (*(ptr - 2) == '\"') {
      *(ptr - 2) = '\0';
    }

    campos[idx++] = start;
  }

  campos[idx] = NULL; // Marcar el final del array
  return campos;
}

List *split_string(const char *str, const char *delim) {
  List *result = list_create();
  char *token = strtok((char *)str, delim);

  while (token != NULL) {
    // Eliminar espacios en blanco al inicio del token
    while (*token == ' ') {
      token++;
    }

    // Eliminar espacios en blanco al final del token
    char *end = token + strlen(token) - 1;
    while (*end == ' ' && end > token) {
      *end = '\0';
      end--;
    }

    // Copiar el token en un nuevo string
    char *new_token = strdup(token);

    // Agregar el nuevo string a la lista
    list_pushBack(result, new_token);

    // Obtener el siguiente token
    token = strtok(NULL, delim);
  }

  return result;
}

// Función para limpiar la pantalla
void limpiarPantalla() {
  #if defined(_WIN32) || defined(_WIN64)
      system("cls");  // Windows (32 o 64 bits)
  #else
      system("clear");  // Linux / MacOS
  #endif
}

void presioneTeclaParaContinuar() {
  puts("Presione una tecla para continuar...");
  getchar(); // Consume el '\n' del buffer de entrada
  getchar(); // Espera a que el usuario presione una tecla
}