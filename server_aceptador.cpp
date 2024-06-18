#include "server_aceptador.h"

Aceptador::Aceptador(Socket &srv, Queue<uint8_t> &queue_compartida, 
Server_protected_queue &protected_queue) : 
srv(srv), aceptar_jugadores(true), queue_compartida(queue_compartida), 
protected_queue(protected_queue){}

void Aceptador::reap_dead() {

    this->clientes.remove_if([](Server_client &cliente) {
        
        if (cliente.is_deead()) {
            cliente.unir_hilo();
            cliente.eliminar_hilos();
            return true;
        }
        return false;

    });
}

void Aceptador::kill_all() {
    
    for (auto& cliente : this->clientes) {
        cliente.kill();
        cliente.unir_hilo();
        cliente.eliminar_hilos();
    }

    this->clientes.clear();
}

void Aceptador::run() {
        
    try {
        while (aceptar_jugadores) {
            
            Socket peer = this->srv.accept();
            Server_client cliente(std::move(peer), this->queue_compartida, this->protected_queue);
            this->clientes.push_back(std::move(cliente));
            this->clientes.back().iniciar_hilos();
            reap_dead();
        }
    } catch (LibError& error) {
        if (this->aceptar_jugadores) {
            std::cerr << "Se cerro el server." << std::endl;   
            //El reap dead es para evitar un caso particual en donde se rompia el programa
            //si los clientes salian y no se une nadie mas, y se aprieta q en el server. 
            reap_dead();
        } 
    } 
    kill_all();
}


