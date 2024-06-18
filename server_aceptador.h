#ifndef SERVER_ACEPTADOR_H
#define SERVER_ACEPTADOR_H

#include <list>
#include <vector>
#include <utility>

#include "socket.h"
#include "liberror.h"
#include "common_thread.h"
#include "common_queue.h"
#include "server_client.h"
#include "server_data.h"

class Aceptador : public Thread{

   private:
    
    Socket &srv;
    std::list<Server_client> clientes;
    bool aceptar_jugadores;
    Queue<uint8_t> &queue_compartida;
    Server_protected_queue &protected_queue;
   
   public:

    explicit Aceptador(Socket &srv, Queue<uint8_t> &queue_compartida, 
    Server_protected_queue &protected_queue);
    
    // Pre: -
    // Pos: Cosecha conexiones muertas, joineando los hilos y eliminandolos 
    // de la lista de clientes.
    void reap_dead();

    // Pre: -
    // Pos: Cierra la conexion del socket y hace un shootdown.
    void kill_all();
    
    virtual void run() override;
    
    //Desactivo el constructor por copia.
    Aceptador(const Aceptador&) = delete;
    Aceptador& operator = (const Aceptador&) = delete;
};
#endif 
