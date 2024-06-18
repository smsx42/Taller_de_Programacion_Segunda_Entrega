#include "server_client.h"

Server_client::Server_client(Socket &&socket, Queue<uint8_t> &queue_compartida, 
Server_protected_queue &protected_queue) : 
peer(std::move(socket)), queue_compartida(queue_compartida), 
protected_queue(protected_queue), 
thread_reciver(nullptr), thread_sender(nullptr) {}

Server_client::Server_client(Server_client&& other) noexcept : peer(std::move(other.peer)), 
queue_compartida(other.queue_compartida), protected_queue(other.protected_queue),
thread_reciver(nullptr), thread_sender(nullptr) {}

void Server_client::kill() {
    this->thread_reciver->kill();
    this->thread_sender->kill();
    this->peer.shutdown(2);
    this->peer.close();
}

bool Server_client::is_deead() {
    // Con el reciver me basta para saber que el cliente esta desconectado.
    return (this->thread_reciver->is_deead());
}

void Server_client::unir_hilo() {
    this->thread_reciver->join();
    this->thread_sender->cerrar_queue_sender();
    this->thread_sender->join();
}

void Server_client::eliminar_hilos() {
    delete this->thread_reciver;
    delete this->thread_sender;
}

void Server_client::iniciar_hilos() {
    this->thread_reciver = new Server_reciver(this->peer, this->queue_compartida);
    this->thread_reciver->start();
    this->thread_sender = new Server_sender(this->peer, this->protected_queue);
    this->thread_sender->start();
}
