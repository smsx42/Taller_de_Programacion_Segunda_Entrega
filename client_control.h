#ifndef CLIENT_CONTROL_H
#define CLIENT_CONTROL_H

#include <string>
#include <vector>
#include <iostream>
#include <sstream>

#include "client_protocol.h"
#include "constantes.h"

class Client_control {

   private:
    
    Client_protocol protocol;
    std::vector<std::string> mensajes_recibidos;

    // Pre: -.
    // Pos: Muestra la linea de la respuesta segun la accion.
    void mostrar_linea(std::string const &mensaje, std::string const &accion);

    // Pre: El mensaje esta bien formado.
    // Pos: Muestra lo que debe imprimir el cliente.
    void mostrar_respuesta();
    
    // Pre: -
    // Pos: Devuelve true si la accion es salir y false en otro caso.
    bool seleccionar_accion(std::string const &entrada_cliente);
   
   public:
 
    Client_control(char *nombre_cliente, char* nombre_servidor);
    
    // Pre: -
    // Pos: Genera el loop para recibir comandos.
    void recibir_comandos();

    //Desactivo el constructor por copia.
    Client_control(const Client_control&) = delete;
    Client_control& operator = (const Client_control&) = delete;
};
#endif
