#ifndef SERVER_GAMELOOP_H
#define SERVER_GAMELOOP_H

#include <vector>
#include <mutex>
#include <utility>
#include <string>

#include "common_queue.h"
#include "common_thread.h"
#include "server_enemigo.h"
#include "constantes.h"
#include "server_data.h"
#include "server_protected_queue.h"

class Server_gameloop : public Thread {

   private:

    Queue<uint8_t> &queue_server;
    Server_protected_queue &protected_queue;
    int cantidad_enemigos_vivos;
    int cantidad_enemigos_muertos;
    bool termino_juego;
    Enemigo enemigos[MAX_ENEMIGOS];
    uint8_t byte_recibido;
    
    // Pre: -
    // Pos: Elimina al un enemigo dado el ataque del cliente.
    void eliminar_enemigo();
    
    // Pre: EL enemigo tiene que estar eliminado.
    // Pos: Revive a un enemigo muerto 15 iteraciones despues de ser 
    // eliminado (3 segundos aproximadamente)
    void revivir_enemigo(Enemigo &enemigo);
    
    // Pre: -
    // Pos: Realiza un broadcast con los clientes segun la accion ocurrida
    // en el servidor por los clientes.
    void realizar_broadcast(uint8_t const &byte_accion);
    
    // Pre: -
    // Pos: Muestra una linea de la accion realizada por algun cliente-
    void mostrar_linea(std::string const &accion);

   public:

    explicit Server_gameloop(Queue<uint8_t> &queue_server, 
    Server_protected_queue &protected_queue);

    //Desactivo el constructor por copia.
    Server_gameloop(const Server_gameloop&) = delete;
    Server_gameloop& operator = (const Server_gameloop&) = delete;
    

    virtual void run() override;
};
#endif 
