#include "../include/extra.h"
#include "../include/hashmap.h"
#include "../estructuras.h"

#define MAX_LINE_LENGTH 1024
#define MAX_FIELDS 300

char *leer_char() {
  char buffer[51];
  while (1) {
    //fflush(stdout); // Asegura que el mensaje se imprima antes del input

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

HashMap *leer_sujetos() {
  FILE *archivo = fopen("data/sujetos.csv", "r");

  if (!archivo) {
    printf("Error al abrir el archivo %s\n", "data/sujetos.csv");
    return NULL;
  }

  HashMap *mapa = createMap(2000);
  char **campos;
  // Leer y descartar encabezado
  campos = leer_linea_csv(archivo, ',');
  int i = 0;
  while ((campos = leer_linea_csv(archivo, ',')) != NULL) {
    if (!campos[0]) continue;
      tipoSujeto *sujeto = malloc(sizeof(tipoSujeto));
      sujeto->nombre = strdup(campos[0]);
      sujeto->genero = strdup(campos[1]);
      sujeto->motivo = strdup(campos[2]);
      sujeto->dinero = atof(campos[3]);
      sujeto->habilitado = false;
      
      char ID[10];
      sprintf(ID, "%d", i);
      insertMap(mapa, ID, sujeto);
      i++;
  }
  fclose(archivo);
  return mapa;
}

HashMap *leer_pasaportes() {
  FILE *archivo = fopen("data/pasaportes.csv", "r");

  if (!archivo) {
    printf("Error al abrir el archivo %s\n", "data/pasaportes.csv");
    return NULL;
  }

  HashMap *mapa = createMap(2000);
  char **campos;
  // Leer y descartar encabezado
  campos = leer_linea_csv(archivo, ',');
  int i = 0;
  while ((campos = leer_linea_csv(archivo, ',')) != NULL) {
    if (!campos[0]) continue;
      tipoPasaporte *pasaporte = malloc(sizeof(tipoPasaporte));
      pasaporte->nombre = strdup(campos[0]);
      pasaporte->pais = strdup(campos[1]);
      pasaporte->pasaporte = strdup(campos[2]);
      pasaporte->documento = strdup(campos[3]);
      pasaporte->caducidad = strdup(campos[4]);
      char ID[10];
      sprintf(ID, "%d", i);
      insertMap(mapa, ID, pasaporte);
      i++;
  }
  fclose(archivo);
  return mapa;
}

HashMap *leer_dni() {
  FILE *archivo = fopen("data/DNI.csv", "r");

  if (!archivo) {
    printf("Error al abrir el archivo %s\n", "data/DNI.csv");
    return NULL;
  }

  HashMap *mapa = createMap(2000);
  char **campos;
  // Leer y descartar encabezado
  campos = leer_linea_csv(archivo, ',');
  int i = 0;
  while ((campos = leer_linea_csv(archivo, ',')) != NULL) {
    if (!campos[0]) continue;
      tipoDNI *dni = malloc(sizeof(tipoDNI));
      dni->nombre = strdup(campos[0]);
      dni->documento = strdup(campos[1]);
      dni->nacimiento = strdup(campos[2]);
      dni->pais = strdup(campos[3]);
      dni->caducidad = strdup(campos[4]);
      dni->genero = strdup(campos[5]);
      char ID[10];
      sprintf(ID, "%d", i);
      insertMap(mapa, ID, dni);
      i++;
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

void eliminar_partida(char *nombre_partida) {
    FILE *archivo = fopen("data/partida.csv", "r");
    if (!archivo) {
        printf("\033[91m>> Error al abrir el archivo de partidas.\033[0m\n");
        return;
    }

    FILE *temp = fopen("data/temp.csv", "w");
    if (!temp) {
        printf("\033[91m>> Error al crear el archivo temporal.\033[0m\n");
        fclose(archivo);
        return;
    }

    char linea[256];
    int encontrada = 0;

    while (fgets(linea, sizeof(linea), archivo)) {
        // Crear una copia limpia de la línea
        char copia[256];
        strcpy(copia, linea);

        // Eliminar salto de línea (\n o \r\n)
        copia[strcspn(copia, "\r\n")] = '\0';

        List *campos = split_string(copia, ",");
        if (!campos || list_size(campos) == 0) {
            list_destroy(campos, free);
            continue;
        }

        char *nombre = list_get(campos, 0);
        if (nombre && strcmp(nombre, nombre_partida) == 0) {
            encontrada = 1;  // No escribir esta línea
            list_destroy(campos, free);
            continue;
        }

        // Línea no coincide: la escribimos completa y tal cual
        fputs(linea, temp);
        list_destroy(campos, free);
    }

    fclose(archivo);
    fclose(temp);

    remove("data/partida.csv");
    rename("data/temp.csv", "data/partida.csv");

    if (encontrada) {
        printf("\033[91m>> La partida \"%s\" ha sido eliminada por temas confidenciales .\033[0m\n", nombre_partida);
    } else {
        printf("\033[93m>> No se encontró la partida \"%s\" en el registro.\033[0m\n", nombre_partida);
    }
}

void autoguardado(tipoPartida *partida) {
    FILE *archivo_lectura = fopen("data/partida.csv", "r");
    FILE *archivo_temp = fopen("data/partida_temp.csv", "w");
    
    if (!archivo_lectura || !archivo_temp) {
        printf("Error al abrir los archivos para autoguardado\n");
        if (archivo_lectura) fclose(archivo_lectura);
        if (archivo_temp) fclose(archivo_temp);
        return;
    }

    char **campos;
    // Copiar encabezado
    campos = leer_linea_csv(archivo_lectura, ',');
    if (campos) {
        fprintf(archivo_temp, "%s,%s,%s,\n", campos[0], campos[1], campos[2]);
    }

    // Procesar cada línea
    while ((campos = leer_linea_csv(archivo_lectura, ',')) != NULL) {
        if (!campos[0]) continue;
        
        // Si es la partida que queremos actualizar
        if (strcmp(campos[0], partida->nombre_partida) == 0) {
            // Escribir los datos actualizados
            fprintf(archivo_temp, "%s,%d,%d,\n", 
                   partida->nombre_partida,
                   partida->dia_actual,
                   partida->aura);
        } else {
            // Copiar la línea sin cambios, incluyendo la coma final
            fprintf(archivo_temp, "%s,%s,%s,\n", campos[0], campos[1], campos[2]);
        }
    }

    fclose(archivo_lectura);
    fclose(archivo_temp);

    // Reemplazar el archivo original con el temporal
    remove("data/partida.csv");
    rename("data/partida_temp.csv", "data/partida.csv");
}


void presioneTeclaParaContinuar() {
  puts("Presione una tecla para continuar...");
  getchar(); // Consume el '\n' del buffer de entrada
  getchar(); // Espera a que el usuario presione una tecla
}

