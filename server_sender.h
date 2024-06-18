#ifndef SERVER_SENDER_H
#define SERVER_SENDER_H

#include <vector>
#include <algorithm>

#include "socket.h"
#include "server_data.h"
#include "server_protected_queue.h"
#include "common_thread.h"
#include "common_queue.h"

class Server_sender : public Thread {

   private:

    Socket &peer;
    std::atomic<bool> keep_talking;
    std::atomic<bool> is_alive;
    Server_protected_queue &protected_queue;
    Queue<Server_data> queue_sender;

   public:

    explicit Server_sender(Socket &peer, Server_protected_queue &protected_queue);

    // Pre: -
    // Pos: Devuelve un bool indicando si se sigue usando el reciver.
    bool is_deead();
    
    // Pre: -
    // Pos: Modifica el valor de keep_talking.
    void kill();
    
    // Pre: -
    // Pos: Cierra la queue del sender.
    void cerrar_queue_sender();

    virtual void run() override;

    //Desactivo el constructor por copia.
    Server_sender(const Server_sender&) = delete;
    Server_sender& operator = (const Server_sender&) = delete;
};
#endif 
