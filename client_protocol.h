#ifndef CLIENT_PROTOCOL_H
#define CLIENT_PROTOCOL_H

#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "socket.h"
#include "constantes.h"

class Client_protocol {
    
   private:
    
    Socket socket;
    std::string const hostName;
    bool was_closed;

    void serealizar_mensaje(std::vector<uint8_t> &mensaje_serealizado, 
    std::string const &entrada_cliente);

    std::vector<std::string> devolver_acciones_separadas
    (std::string const &entrada_cliente);

    std::vector<std::string> generar_mensaje_separado
    (std::vector<std::uint8_t> const &mensaje_recibido);
     
   public: 
    
    explicit Client_protocol(std::string const &hostName, std::string const &serverName);

    void enviar(std::string const &entrada_cliente);

    std::vector<std::string>  esperar_respuesta(int cantidad_mensajes);

    //Desactivo el construcor por copia.
    Client_protocol(const Client_protocol&) = delete;
    Client_protocol& operator = (const Client_protocol&) = delete;
};
#endif
