#include "client_control.h"

Client_control::Client_control(char *nombre_cliente, char *nombre_servidor) : 
protocol(nombre_cliente, nombre_servidor), mensajes_recibidos() {}

void Client_control::mostrar_linea(std::string const &mensaje, std::string const &accion) {
    std::cout << "Un enemigo ha " << accion << ". " << mensaje[POSICION_VIVOS] << 
    " vivo(s) y " << mensaje[POSICION_MUERTOS] << " muerto(s)." << std::endl;
}

void Client_control::mostrar_respuesta() {
    
    for (std::string mensaje :  this->mensajes_recibidos) {
        if (mensaje[POSICION_ACCION] == CARACTER_ELIMINAR) {
            mostrar_linea(mensaje, PALABRA_MUERTO);

        } else if (mensaje[POSICION_ACCION] == CARACTER_REVIVIR) {
            mostrar_linea(mensaje, PALABRA_REVIVIDO);
        }
    }
}

bool Client_control::seleccionar_accion(std::string const &entrada_cliente) {

    // Esta para que se puedan recibir multiples comandos en una linea.   
    std::istringstream string(entrada_cliente);
    std::string accion;
    int cantidad = 0;
    string >> accion >> cantidad;
    bool termino = false;
    
    if (accion == ACCION_ATACAR) {
        this->protocol.enviar(entrada_cliente);
    } else if (accion == ACCION_LEER) {
        this->mensajes_recibidos = 
        this->protocol.esperar_respuesta(cantidad);
        mostrar_respuesta(); 
    } else if (entrada_cliente == ACCION_SALIR) {
        termino = true;
    } 
    
    return termino;
}

void Client_control::recibir_comandos(){

    bool termino = false;   
    std::string entrada_cliente;
    
    while (!termino) {
        
        std::getline(std::cin, entrada_cliente);
        termino = seleccionar_accion(entrada_cliente);

    }
}
