#include "client_protocol.h"

Client_protocol::Client_protocol(std::string const &hostName, std::string const &serverName) : 
socket(hostName.c_str(), serverName.c_str()), hostName(hostName), was_closed(false){}

std::vector<std::string> Client_protocol::devolver_acciones_separadas
(std::string const &entrada_cliente) {
    
    std::vector<std::string> palabras;
    std::istringstream iss(entrada_cliente);
    std::string palabra;
    while (iss >> palabra) {
        palabras.push_back(palabra);
    }

    return palabras;
}

void Client_protocol::serealizar_mensaje(std::vector<uint8_t> &mensaje_serealizado, 
std::string const &entrada_cliente) {
    
    std::vector<std::string> palabras = devolver_acciones_separadas(entrada_cliente);
    for (std::string palabra : palabras) {
        if (palabra == ACCION_ATACAR) {
            mensaje_serealizado.push_back(BYTE_ATACAR);
        }
    }
}

void Client_protocol::enviar(std::string const &entrada_cliente) {
    std::vector<uint8_t> mensaje_serealizado;
    serealizar_mensaje(mensaje_serealizado, entrada_cliente);
    for (uint8_t buf : mensaje_serealizado) {
        socket.sendall(&buf, sizeof(buf), &was_closed);
    }
}

std::vector<std::string> Client_protocol::generar_mensaje_separado
(std::vector<std::uint8_t> const &mensaje_recibido) {

    std::stringstream ss;
    for (size_t i = 0; i < mensaje_recibido.size(); i++) {
        
        if (mensaje_recibido[i] == BYTE_ENVIAR) {
            ss << " ";
        }
        ss << std::hex << static_cast<int>(mensaje_recibido[i]);
    }
    std::vector<std::string> bytes_separados;
    std::string bytes;
    while (ss >> bytes) {
        bytes_separados.push_back(bytes); 
    }

    return bytes_separados;


}
std::vector<std::string> Client_protocol::esperar_respuesta(int cantidad_mensajes) {
    
    uint8_t buf;
    bool termino = false;
    int canitdad_totales_bytes = 0;

    std::vector<uint8_t> mensaje_recibido;

    while (!termino) {
        int cantidad_bytes = socket.recvall(&buf, sizeof(buf), &was_closed);
        canitdad_totales_bytes += cantidad_bytes;
        mensaje_recibido.push_back(buf);
        if (canitdad_totales_bytes == cantidad_mensajes * 6) {
            termino = true;
             
        }
    }
    std::vector<std::string> numeros = generar_mensaje_separado(mensaje_recibido);
    
    return numeros;
 
}
