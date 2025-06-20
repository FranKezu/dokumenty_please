#ifndef ESTRUCTURAS_H
#define ESTRUCTURAS_H

#include "include/hashmap.h"
#include <stdbool.h>

typedef struct {
  int dinero; // Cantidad de dinero que posee la persona.
  char *nombre; // Nombre completo del sujeto.
  char *genero; // Indica el género del sujeto.
  char *motivo; // Contiene la razón del viaje.     
  bool habilitado; // Indica si puede ingresar o no.
} tipoSujeto;

// Estructura que representa a una persona que desea ingresar al país
typedef struct {     
  char *nombre; // Nombre completo del sujeto.
  char *documento; // Número de documento.
  char *nacimiento; // Fecha de nacimiento.
  char *pais; // País de origen.
  char *caducidad; // Fecha de vencimiento del documento.
} tipoDNI;

// Estructura que representa el pasaporte de la persona que desea ingresar.
typedef struct {
  char *nombre; // Nombre completo del sujeto.
  char *pais; // País emisor del pasaporte.
  char *documento; // Número de documento del pasaporte.
  char *pasaporte; // Número del pasaporte.
  char *emision; // Fecha de emisión del pasaporte.
  char *caducidad; // Fecha de expiración del pasaporte.
} tipoPasaporte;

// Almacena los datos de una persona que fue admitida o rechazada por el jugador
typedef struct {
  tipoSujeto persona; // Contiene los datos de la persona.
  char *motivo; // Motivo asociado a la decisión.
  int dia; // Día en que se tomó la decisión.
  bool decision; // true si fue admitido, false si fue rechazado.
} tipoProcesado;

// Archivo de guardado con la información del progreso del jugador
typedef struct {
  char *nombre_partida; // Nombre de la partida.
  int dia_actual; // Día actual en la partida.
  int aura; // Puntuación acumulada.
  // tipoProcesado *listaPersonas; // Lista de personas procesadas (implementarla luego).
} tipoPartida;

// Estructura que contiene el registro de cada persona (sujeto/dni/pasaporte)
typedef struct {
  tipoSujeto *sujeto;
  tipoDNI *dni;
  tipoPasaporte *pasaporte; 
} tipoPersona;

typedef struct {
  HashMap *mapa_partidas;
  //HashMap *mapa_procesados;
  
  HashMap *mapa_sujetos;
  HashMap *mapa_pasaportes; 
  HashMap *mapa_dni;
} tipoMapas;

#endif // ESTRUCTURAS_H