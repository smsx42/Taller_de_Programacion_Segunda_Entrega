#include "server_data.h"

Server_data::Server_data(int cantidad_enemigos_vivos, int cantidad_enemigos_muertos, 
uint8_t byte_accion) : cantidad_enemigos_vivos(cantidad_enemigos_vivos), 
cantidad_enemigos_muertos(cantidad_enemigos_muertos), byte_accion(byte_accion) {}

std::vector<uint8_t> Server_data::generar_mensaje() {
    
    uint8_t byte1 = (this->cantidad_enemigos_muertos >> 8) & 0xFF;
    uint8_t byte2 = this->cantidad_enemigos_muertos & 0xFF;
    uint8_t byte3 = (this->cantidad_enemigos_vivos >> 8) & 0xFF;
    uint8_t byte4 = this->cantidad_enemigos_vivos & 0xFF;

    mensaje.push_back(BYTE_ENVIAR);
    mensaje.push_back(byte3);
    mensaje.push_back(byte4);
    mensaje.push_back(byte1);
    mensaje.push_back(byte2);
    mensaje.push_back(byte_accion);

    return mensaje;
}
