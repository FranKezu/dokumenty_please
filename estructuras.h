#ifndef ESTRUCTURAS_H
#define ESTRUCTURAS_H

#include "include/hashmap.h"
#include <stdbool.h>

// Estructura que representa los datos de una persona que desea ingresar al país
typedef struct {
  int dinero; // Cantidad de dinero que posee la persona.
  char *nombre; // Nombre completo del sujeto.
  char *genero; // Indica el género del sujeto, femenino o masculino.
  char *motivo; // Contiene la razón del viaje en una palabra. 
  bool habilitado; // Indica si debería ingresar o no (el jugador no lo sabe).
} tipoSujeto;

// Estructura que representa el DNI de una persona.
typedef struct {     
  char *nombre; // Nombre completo del sujeto.
  char *genero; // Indica el género del sujeto, femenino o masculino.
  char *documento; // Número de documento.
  char *nacimiento; // Fecha de nacimiento.
  char *pais; // País de origen.
  char *caducidad; // Fecha de vencimiento del DNI.
} tipoDNI;

// Estructura que representa el pasaporte de una persona.
typedef struct {
  char *nombre; // Nombre completo del sujeto.
  char *pais; // País emisor del pasaporte.
  char *documento; // Número de documento del DNI.
  char *pasaporte; // Número del pasaporte.
  char *caducidad; // Fecha de expiración del pasaporte.
} tipoPasaporte;

// Almacena los datos de una persona que fue admitida o rechazada por el jugador
typedef struct {
  tipoSujeto persona; // Contiene los datos de la persona.
  char *motivo; // Motivo asociado a la decisión.
  int dia; // Día en que se tomó la decisión.
  bool decision; // Registra la decisión del jugador, true si fue admitido, false si fue rechazado.
} tipoProcesado;

// Archivo de guardado con la información del progreso del jugador
typedef struct {
  char *nombre_partida; // Nombre de la partida.
  int dia_actual; // Día actual en la partida.
  int aura; // Representa la puntuación acumulada.
} tipoPartida;

// Estructura que contiene el registro de cada persona (sujeto/dni/pasaporte)
typedef struct {
  tipoSujeto *sujeto;
  tipoDNI *dni;
  tipoPasaporte *pasaporte; 
} tipoPersona;

// Encapsulamiento de mapas
typedef struct {
  HashMap *mapa_partidas;
  //HashMap *mapa_procesados;
  HashMap *mapa_sujetos;
  HashMap *mapa_pasaportes; 
  HashMap *mapa_dni;
} tipoMapas;

#endif // ESTRUCTURAS_H