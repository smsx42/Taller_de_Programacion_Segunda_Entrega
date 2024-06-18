#ifndef SERVER_RECIVER_H
#define SERVER_RECIVER_H

#include "common_thread.h"
#include "socket.h"
#include "common_queue.h"

class Server_reciver : public Thread{

   private:

    Socket &peer;
    std::atomic<bool> keep_talking;
    std::atomic<bool> is_alive;
    Queue<uint8_t> &queue_reciver;

   public:

    explicit Server_reciver(Socket &peer, Queue<uint8_t> &queue_compartida);
    
    // Pre: -
    // Pos: Devuelve un bool indicando si se sigue usando el reciver.
    bool is_deead();
    
    // Pre: -
    // Pos: Modifica el valor de keep_talking.
    void kill();
    
    virtual void run() override;

    //Desactivo el constructor por copia.
    Server_reciver(const Server_reciver&) = delete;
    Server_reciver& operator = (const Server_reciver&) = delete;
};

#endif
