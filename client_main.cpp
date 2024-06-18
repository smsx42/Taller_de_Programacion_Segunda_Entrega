#include <stdexcept>
#include <iostream>

#include "client_control.h"

int main(int argc, char *argv[]) {

    char *nombre_cliente;
    char *nombre_servidor;
    try {
        if (argc == 3) {
           nombre_cliente = argv[1];
           nombre_servidor = argv[2];
        } else {
            throw std::invalid_argument("Error al crear el cliente.");

        }
    } catch(const std::invalid_argument &error) {
        std::cerr << "ERROR: " << error.what() << std::endl;
        return -1;
    }

    Client_control control(nombre_cliente, nombre_servidor);

    control.recibir_comandos();
    
    return 0;
}
