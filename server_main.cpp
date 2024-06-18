#include <iostream>
#include <vector>
#include <stdexcept>

#include "socket.h"
#include "constantes.h"
#include "common_thread.h"
#include "server_aceptador.h"
#include "server_gameloop.h"
#include "common_queue.h"

#define MAX_SIZE 50

int main(int argc, char *argv[]) {
    char *nombre_servidor;
    try {
        if (argc == 2) {
           nombre_servidor = argv[1];
        } else {
            throw std::invalid_argument("Error al crear el servidor.");
        }
    } catch(const std::invalid_argument &error) {
        std::cerr << "ERROR: " << error.what() << std::endl;
        return -1;
    }
    Socket srv(nombre_servidor);
    Queue<uint8_t> queue_compartida(MAX_SIZE);
    
    std::vector<Queue<Server_data>*> queue_senders;
    Server_protected_queue protected_queue(queue_senders);

    auto *server_gameloop = new Server_gameloop(queue_compartida, protected_queue);
    server_gameloop->start();

    auto *aceptador = new Aceptador(srv, queue_compartida, protected_queue);
    aceptador->start();
    
    char c = '0';
    while (c != CARACTER_SALIDA) {
        std::cin >> c;

    }
    srv.shutdown(2);
    srv.close();
    queue_compartida.close();
    server_gameloop->join();
    delete server_gameloop;
    aceptador->join();
    delete aceptador;

    return 0;
}
