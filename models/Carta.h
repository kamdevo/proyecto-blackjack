/*Juan Camilo Morales - 2515391
Jorge Luis Castro - 2517065
Andrés Felipe Rengifo Rodríguez - 2519613
*/

// ===========================================
// ARCHIVO: Carta.h
// Descripción: Clase que representa una carta individual
// ===========================================
/*
CRC - Carta

Clase: Carta
Responsabilidades:
- Representar una carta de la baraja (valor y palo).
- Proveer acceso al valor (texto y valor numérico) y al palo.
- Crear un mazo completo estático y operaciones de barajar.
Colaboradores:
- Mano: contiene y usa objetos Carta.
- Juego / Crupier / Jugador: reciben y muestran cartas.
Notas:
- Métodos estáticos devuelven vectores de punteros a Carta (gestión de memoria en el proyecto).
*/
#ifndef CARTA_H
#define CARTA_H

#include <string>
#include <vector>

using namespace std;

class Carta {
private:
    // Atributos privados
    string valor;
    string palo;

public:
    // Constructor
    /**
     * Constructor que inicializa una carta con valor y palo específicos
     * @param v Valor de la carta 
     * @param p Palo de la carta 
     */
    Carta(string v, string p);
    
    // Métodos de acceso
    /**
     * Obtiene el valor numérico de la carta para el cálculo del blackjack
     * @return Valor numérico
     */
    int getValorNumerico() const;
    
    /**
     * Obtiene el valor textual de la carta
     * @return String con el valor (A, 2-10, J, Q, K)
     */
    string getValor() const;
    
    /**
     * Obtiene el palo de la carta
     * @return String con el nombre del palo
     */
    string getPalo() const;
    
    // Método para mostrar la carta
    /**
     * Imprime en consola la representación visual de la carta
     */
    void mostrar() const;
    
    // Métodos estáticos para crear y manipular mazos
    /**
     * Crea y retorna un mazo completo de 52 cartas (4 palos x 13 valores)
     * @return Vector de punteros a Carta con todas las cartas del mazo
     */
    static vector<Carta*> crearMazoCompleto();
    
    /**
     * Baraja aleatoriamente un vector de cartas usando algoritmo Fisher-Yates
     * @param cartas Vector de punteros a Carta que será barajado (modificado por referencia)
     */
    static void barajarCartas(vector<Carta*>& cartas);
};

#endif // CARTA_H
