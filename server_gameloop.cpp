#include "server_gameloop.h"

Server_gameloop::Server_gameloop(Queue<uint8_t> &queue, 
Server_protected_queue &protected_queue) : queue_server(queue), 
protected_queue(protected_queue), cantidad_enemigos_vivos(MAX_ENEMIGOS), 
cantidad_enemigos_muertos(0), termino_juego(false), byte_recibido(0x00) {}

void Server_gameloop::realizar_broadcast(uint8_t const &byte_accion) {
    
    Server_data dato(this->cantidad_enemigos_vivos, this->cantidad_enemigos_muertos, byte_accion);
    this->protected_queue.realizar_broadcast(std::move(dato));
}

void Server_gameloop::mostrar_linea(std::string const &accion) {

    std::cout << "Un enemigo ha " << accion << ". " << this->cantidad_enemigos_vivos << 
    " vivo(s) y " << this->cantidad_enemigos_muertos << " muerto(s)." << std::endl;
}
 
void Server_gameloop::eliminar_enemigo() {
    
    this->cantidad_enemigos_vivos --;     
    this->cantidad_enemigos_muertos ++;
    for (int i = 0; i < MAX_ENEMIGOS; i++) {
        if (this->enemigos[i].verificar_vivo()) {
            this->enemigos[i].eliminar();
            break;
        }
    }

    this->byte_recibido = 0x00;
    realizar_broadcast(BYTE_ELIMINAR);
    mostrar_linea(PALABRA_MUERTO);
}

void Server_gameloop::revivir_enemigo(Enemigo &enemigo) {

    if (enemigo.get_cantidad_iteraciones() == MAX_ITERACIONES) {
        enemigo.resetear_iteraciones();
                
        if (this->cantidad_enemigos_vivos < MAX_ENEMIGOS) {
            this->cantidad_enemigos_vivos ++;
            this->cantidad_enemigos_muertos --;
            this->byte_recibido = 0x00;
            enemigo.revivir();
            realizar_broadcast(BYTE_REVIVIR);
            mostrar_linea(PALABRA_REVIVIDO);          
        }
    }
}

void Server_gameloop::run() {


    while (!termino_juego) {

        try {
            queue_server.try_pop(this->byte_recibido);
        } catch (ClosedQueue &error) { 
            termino_juego = true;
            byte_recibido = 0x00;
        }

        if (this->byte_recibido == BYTE_ATACAR && cantidad_enemigos_muertos != MAX_ENEMIGOS) {
            eliminar_enemigo();
        }
            
        for (int i = 0; i < MAX_ENEMIGOS; i++) {
            if (!enemigos[i].verificar_vivo()) {
                enemigos[i].aumnentar_itearciones();
            }
        }

        for (int i = 0; i < MAX_ENEMIGOS; i++) {
            revivir_enemigo(this->enemigos[i]);
        } 
        std::this_thread::sleep_for(std::chrono::milliseconds(TIEMPO_LOOP));
    }
}
