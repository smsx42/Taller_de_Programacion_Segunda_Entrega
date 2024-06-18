#ifndef SERVER_DATA_H
#define SERVER_DATA_H

#include <vector>
#include <iostream>

#include "constantes.h"

/*Aclaracion: 
El mensaje para enviar podria generarse en el sender pero generandolo
en esta clase puedo aprovechar los atributos.
*/

class Server_data {

    private:

    std::vector<uint8_t> mensaje;
    int cantidad_enemigos_vivos;
    int cantidad_enemigos_muertos;
    uint8_t byte_accion;

    public:

    Server_data(int cantidad_enemigos_vivos, int cantidad_enemigos_muertos, uint8_t byte_accion);
    
    // Pre: -
    // Pos: Genera el mensaje en bytes a enviar al usuario.
    std::vector<uint8_t> generar_mensaje();
};
#endif
