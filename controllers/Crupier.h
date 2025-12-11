/*Juan Camilo Morales - 2515391
Jorge Luis Castro - 2517065
Andrés Felipe Rengifo Rodríguez - 2519613
*/

// ===========================================
// ARCHIVO: Crupier.h
// Descripción: Clase que representa al crupier/dealer
// ===========================================
/*
CRC - Crupier

Clase: Crupier
Responsabilidades:
- Mantener y gestionar la mano del crupier.
- Recibir cartas y decidir si debe tomar más según la lógica del juego.
- Mostrar la mano (con opción de ocultar la primera carta).
Colaboradores:
- Mano: almacena las cartas del crupier y calcula su valor.
- Carta: objetos que forman la mano.
- Juego: el flujo principal invoca las acciones del crupier en su turno.
Notas:
- La lógica de "debeTomarCarta" implementa las reglas del casino (p.ej. pedir hasta 17).
*/
#ifndef CRUPIER_H
#define CRUPIER_H

#include "../models/Mano.h"
#include "../models/Carta.h"
using namespace std;

class Crupier {
private:
    // Atributos privados
    Mano* mano; // Puntero a la mano de cartas del crupier

public:
    // Constructor y destructor
    /**
     * Constructor que inicializa el crupier con una mano vacía
     */
    Crupier();
    
    /**
     * Destructor que libera la memoria de la mano
     */
    ~Crupier();
    
    // Métodos de gestión de cartas
    /**
     * Añade una carta a la mano del crupier
     * @param carta Puntero a la carta a recibir
     */
    void recibirCarta(Carta* carta);
    
    /**
     * Obtiene el valor total de la mano del crupier
     * @return Valor numérico de la mano
     */
    int getValorMano() const;
    
    /**
     * Muestra las cartas del crupier en consola
     * @param ocultarPrimera Si es true, oculta la primera carta (por defecto true)
     */
    void mostrarMano(bool ocultarPrimera = true) const;
    
    // Métodos de lógica del crupier
    /**
     * Determina si el crupier debe tomar otra carta según las reglas del casino
     * Típicamente debe pedir carta si tiene 16 o menos y plantarse con 17 o más
     * @return true si debe tomar carta, false si debe plantarse
     */
    bool debeTomarCarta() const;
    
    // Métodos de acceso
    /**
     * Obtiene el puntero a la mano del crupier
     * @return Puntero a objeto Mano
     */
    Mano* getMano() const;
};

#endif // CRUPIER_H
