#include "server_protected_queue.h"

Server_protected_queue::Server_protected_queue(std::vector<Queue<Server_data>*> &queues_senders) : 
queues_senders(queues_senders) {}

void Server_protected_queue::realizar_push(Queue<Server_data> &queue_sender) {
    std::lock_guard<std::mutex> lock(mutex);     
    this->queues_senders.push_back(&queue_sender);
}
  
void Server_protected_queue::eliminar_queue(Queue<Server_data> &queue_sender) {
    std::lock_guard<std::mutex> lock(mutex);
    this->queues_senders.erase(std::remove(this->queues_senders.begin(), 
    this->queues_senders.end(), &queue_sender), this->queues_senders.end());
}

void Server_protected_queue::realizar_broadcast(Server_data const &dato) { 
    std::lock_guard<std::mutex> lock(mutex);  
    for (Queue<Server_data>* &queue : this->queues_senders) {
        queue->push(dato);
    }
}
