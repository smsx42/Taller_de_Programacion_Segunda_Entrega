#include "server_sender.h"
Server_sender::Server_sender(Socket &peer, Server_protected_queue &protected_queue) : 
peer(peer), keep_talking(true), is_alive(true), 
protected_queue(protected_queue), queue_sender(MAX_SIZE) {}

void Server_sender::cerrar_queue_sender() {
    if (&this->queue_sender != nullptr)  {
        this->queue_sender.close();
        this->protected_queue.eliminar_queue(this->queue_sender);
    }
}

void Server_sender::kill() {
    this->keep_talking = false;
}

bool Server_sender::is_deead() {
    return (!this->is_alive);
}

void Server_sender::run() {

    this->protected_queue.realizar_push(this->queue_sender);

    this->is_alive = this->keep_talking = true;
    bool was_closed = false;
    try {
        while (this->keep_talking) {
                
            std::vector<uint8_t> mensajes_almacenados;
            if (!was_closed) {
                    
                Server_data dato = queue_sender.pop();
                mensajes_almacenados = dato.generar_mensaje();
            }
            peer.sendall(mensajes_almacenados.data(), mensajes_almacenados.size(), &was_closed);
        }
    } catch(ClosedQueue &error) {
        
        kill();
        this->is_alive = false;
    }
}
