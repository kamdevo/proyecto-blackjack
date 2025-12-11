/*Juan Camilo Morales - 2515391
Jorge Luis Castro - 2517065
Andrés Felipe Rengifo Rodríguez - 2519613
*/

// ===========================================
// ARCHIVO: Mano.h
// Descripción: Clase que representa la mano de cartas
// ===========================================
/*
CRC - Mano

Clase: Mano
Responsabilidades:
- Mantener una colección de punteros a Carta que representa la mano.
- Añadir y limpiar cartas.
- Calcular el valor total de la mano y detectar blackjack.
- Mostrar la mano (con opción de ocultar la primera carta).
Colaboradores:
- Carta: cada entrada en la mano es una Carta.
- Jugador / Crupier: poseen y usan objetos Mano para la lógica del juego.

*/
#ifndef MANO_H
#define MANO_H

#include <vector>
#include "Carta.h"
using namespace std;

class Mano {
private:
    // Atributos privados
    vector<Carta*> cartas; // Colección de punteros a las cartas en la mano

public:
    // Constructor y destructor
    /**
     * Constructor que inicializa una mano vacía
     */
    Mano();
    
    /**
     * Destructor que limpia la mano 
     */
    ~Mano();
    
    // Métodos principales
    /**
     * Añade una carta a la mano
     * @param carta Puntero a la carta a agregar
     */
    void agregarCarta(Carta* carta);
    
    /**
     * Calcula el valor total de la mano según las reglas del blackjack
     * Considera el As como 11 si no hace pasar de 21, de lo contrario como 1
     * @return Valor numérico total de la mano
     */
    int calcularValor() const;
    
    /**
     * Obtiene el número de cartas en la mano
     * @return Cantidad de cartas
     */
    int getNumerCartas() const;
    
    /**
     * Muestra todas las cartas de la mano en consola
     * @param ocultarPrimera Si es true, oculta la primera carta (útil para el crupier)
     */
    void mostrarMano(bool ocultarPrimera = false) const;
    
    /**
     * Limpia todas las cartas de la mano (vacía el vector)
     */
    void limpiar();
    
    /**
     * Verifica si la mano tiene blackjack (21 con exactamente 2 cartas)
     * @return true si es blackjack natural, false en caso contrario
     */
    bool tieneBlackjack() const;
};

#endif // MANO_H
