#ifndef CONSTANTES_H
#define CONSTANTES_H

#include <cstdint>

#define MAX_SIZE 50

char const ACCION_ATACAR[] = "Atacar";
char const PALABRA_MUERTO[] = "muerto";
char const PALABRA_REVIVIDO[] = "revivido";
char const ACCION_LEER[] = "Leer";
char const ACCION_SALIR[] = "Salir";

char const CARACTER_SALIDA = 'q';

const int MAX_ENEMIGOS = 5;
const int TIEMPO_LOOP = 200;
const int MAX_ITERACIONES = 15;

uint8_t const BYTE_ATACAR = 0x03;
uint8_t const BYTE_ELIMINAR = 0x04;
uint8_t const BYTE_REVIVIR = 0x05;
uint8_t const BYTE_ENVIAR = 0x06;

char const CARACTER_ELIMINAR = '4';
char const CARACTER_REVIVIR = '5';

int const POSICION_VIVOS = 2;
int const POSICION_MUERTOS = 4;
int const POSICION_ACCION = 5;

#endif
