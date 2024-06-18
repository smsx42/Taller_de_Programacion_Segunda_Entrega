#include "server_enemigo.h"

Enemigo::Enemigo() : esta_vivo(true), cantidad_iteraciones(0) {}

bool Enemigo::verificar_vivo() {
    return this->esta_vivo;
}

int Enemigo::get_cantidad_iteraciones() {
    return this->cantidad_iteraciones;
}
void Enemigo::aumnentar_itearciones() {
    this->cantidad_iteraciones ++;
}

void Enemigo::resetear_iteraciones() {
    this->cantidad_iteraciones = 0;
}

void Enemigo::eliminar() {
    this->esta_vivo = false;
}

void Enemigo::revivir() {
    this->esta_vivo = true;
}
