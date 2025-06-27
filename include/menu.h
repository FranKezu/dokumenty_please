#ifndef MENU_H
#define MENU_H
#include <windows.h>
#include <conio.h>
#include "queue.h"
#include "../estructuras.h"
#include "hashmap.h"

void mostrar_barra_progreso(float segundos);

void imprimir(char **texto);

void menu_principal(int seleccion);

void menu_acciones(Queue *, tipoPersona *, tipoPartida *);

void mostrar_guia();

#endif