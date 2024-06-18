#ifndef SERVER_ENEMIGO_H
#define SERVER_ENEMIGO_H

class Enemigo {

   private:

    bool esta_vivo;
    int cantidad_iteraciones;

   public:

    Enemigo();
    
    // Pre: -
    // Pos: Devuelve un bool dependiedno de si esta vivo o no el enemigo.
    bool verificar_vivo();
    
    // Pre: -
    // Pos: Devuelve la cantidad de iteraciones.
    int get_cantidad_iteraciones();
    
    // Pre: -
    // Pos: Setea en false esta_vivo.
    void eliminar();
    
    // Pre: -
    // Pos: Setea en true esta_vivo.
    void revivir();
      
    // Pre: -
    // Pos: Suma una iteracion.
    void aumnentar_itearciones();
    
    // Pre: -
    // Pos: Setea en 0 la cantidad de iteraciones.
    void resetear_iteraciones();

    //Desactivo el constructor por copia.
    Enemigo(const Enemigo&) = delete;
    Enemigo& operator = (const Enemigo&) = delete;
};
#endif
