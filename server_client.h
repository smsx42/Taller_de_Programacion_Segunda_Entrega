#ifndef SERVER_CLIENT_H
#define SERVER_CLIENT_H

#include <vector>
#include <utility>

#include "common_thread.h"
#include "socket.h"
#include "common_queue.h"
#include "server_reciver.h"
#include "server_sender.h"
#include "server_data.h"

class Server_client {

   private:

    Socket peer;
    Queue<uint8_t> &queue_compartida;
    Server_protected_queue &protected_queue;
    Server_reciver* thread_reciver;
    Server_sender* thread_sender;

   public:

    // Constructor por movimiento para realizar el push de los clientes.
    explicit Server_client(Server_client&& other) noexcept;

    explicit Server_client(Socket &&socket, Queue<uint8_t> &queue_compartida, 
    Server_protected_queue &protected_queue);
    
    // Pre: -
    // Pos: Devuelve un bool si el cliente esta muerto.
    bool is_deead();
    
    // Pre: -
    // Pos: Cierra la conexion del socket y hace un shootdown.
    void kill();
    
    // Pre: -
    // Pos: Joinea los del thread sender y thread reciver. Cierra la queue del sender.
    void unir_hilo();
    
    // Pre: -
    // Pos: Realiza un delete de los threads.
    void eliminar_hilos();
    
    // Pre: -
    // Pos: Realiza el start de los threads.
    void iniciar_hilos();

    //Desactivo el constructor por copia.
    Server_client(const Server_client&) = delete;
    Server_client& operator = (const Server_client&) = delete;

};

#endif
