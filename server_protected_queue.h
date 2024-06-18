#ifndef SERVER_PROTECTED_QUEUE_H
#define SERVER_PROTECTED_QUEUE_H

#include <vector>
#include <algorithm>
#include <mutex>

#include "common_queue.h"
#include "server_data.h"

/* Aclaraciones:
 -La clase esta dedicada al unico recurso compartido de la entrega.
 -La clase es un Monitor ya que cada Critical Section es un metodo publico y
  no hay otros metodos publicos.
 -Las queues de por si son Monitors, con lo cual no hay
  necesidad de proteger los push/pop.
 -Se tuvo en cuenta que solo hay un unico hilo aceptador.
 -Se tuvo en cuenta que solo hay un unico hilo gameloop.
*/

class Server_protected_queue {

   private:

    std::mutex mutex;
    std::vector<Queue<Server_data>*> &queues_senders;

   public:

    explicit Server_protected_queue(std::vector<Queue<Server_data>*> &queues_senders);
    
    // Pre: -
    // Pos: Reliza el broadcast de las queues senders.
    void realizar_broadcast(Server_data const &dato);
    
    // Pre: La queue sender es valida.
    // Pos: Agrega una queue al vector de queues senders.
    void realizar_push(Queue<Server_data> &queue_sender);
    
    // Pre: La queue sender es valida.
    // Pos: Elimina una queue del vector de queues senders.
    void eliminar_queue(Queue<Server_data> &queue_sender);

    //Desactivo el constructor por copia.
    Server_protected_queue(const Server_protected_queue&) = delete;
    Server_protected_queue& operator = (const Server_protected_queue&) = delete;

};
#endif
