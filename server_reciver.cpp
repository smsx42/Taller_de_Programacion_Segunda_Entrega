#include "server_reciver.h"

Server_reciver::Server_reciver(Socket &peer, Queue<uint8_t> &queue_compartida) : 
peer(peer), keep_talking(true), is_alive(true),  queue_reciver(queue_compartida)  {}

void Server_reciver::kill() {
    this->keep_talking = false;
}

bool Server_reciver::is_deead() {
    return (!this->is_alive);
}

void Server_reciver::run() {
        
    uint8_t buf;
    while (this->keep_talking) {
            
        bool was_closed = false;
        this->peer.recvall(&buf, sizeof(buf), &was_closed);
        if (!was_closed) {
            this->queue_reciver.push(buf);
        }
        this->keep_talking = !was_closed;
    }

    this->is_alive = false;
}
