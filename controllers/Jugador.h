/*Juan Camilo Morales - 2515391
Jorge Luis Castro - 2517065
Andrés Felipe Rengifo Rodríguez - 2519613
*/

// ===========================================
// ARCHIVO: Jugador.h
// Descripción: Clase que representa a un jugador
// ===========================================
/*
CRC - Jugador

Clase: Jugador
Responsabilidades:
- Representar un jugador con nombre, mano y apuesta asociada.
- Recibir cartas y mostrar su mano.
- Gestionar decisiones de juego (p. ej. si quiere carta).
- Manejar la interacción con la apuesta (realizar, ganar, perder, empate).
Colaboradores:
- Mano: almacena las cartas del jugador.
- Apuesta: gestiona saldo y cantidad apostada.
- Carta: elementos que componen la mano.
- Juego: orquesta turnos y solicita acciones del jugador.
Notas:
- Métodos de apuesta delegan en Apuesta para actualizar saldo.
*/
#ifndef JUGADOR_H
#define JUGADOR_H

#include <string>
#include "../models/Mano.h"
#include "../models/Carta.h"
#include "../models/Apuesta.h"
using namespace std;

class Jugador {
private:
    // Atributos privados
    string nombre;      // Nombre del jugador
    Mano* mano;        // Puntero a la mano de cartas del jugador
    Apuesta* apuesta;  // Puntero al objeto que gestiona las apuestas y saldo

public:
    // Constructor y destructor
    /**
     * Constructor que inicializa un jugador con nombre y saldo inicial
     * @param n Nombre del jugador
     * @param saldoInicial Saldo inicial para las apuestas (por defecto 1000.0)
     */
    Jugador(string n, double saldoInicial = 1000.0);
    
    /**
     * Destructor que libera la memoria de mano y apuesta
     */
    ~Jugador();
    
    // Métodos de gestión de cartas
    /**
     * Añade una carta a la mano del jugador
     * @param carta Puntero a la carta a recibir
     */
    void recibirCarta(Carta* carta);
    
    /**
     * Obtiene el valor total de la mano del jugador
     * @return Valor numérico de la mano
     */
    int getValorMano() const;
    
    /**
     * Muestra las cartas del jugador en consola
     */
    void mostrarMano() const;
    
    // Métodos de interacción
    /**
     * Pregunta al jugador si desea recibir otra carta
     * @return true si quiere carta, false si se planta
     */
    bool quiereCarta() const;
    
    // Métodos de apuestas
    /**
     * Realiza una apuesta para la ronda actual
     * @param cantidad Monto a apostar
     * @return true si la apuesta fue exitosa, false si no hay saldo suficiente
     */
    bool realizarApuesta(double cantidad);
    
    /**
     * Procesa una victoria, incrementando el saldo
     * @param multiplicador Factor de multiplicación de ganancias 
     */
    void ganar(double multiplicador = 1.0);
    
    /**
     * Procesa una derrota (la apuesta ya fue deducida al realizarla)
     */
    void perder();
    
    /**
     * Procesa un empate, devolviendo la apuesta al jugador
     */
    void empate();
    
    // Métodos de acceso
    /**
     * Obtiene el saldo actual del jugador
     * @return Saldo disponible
     */
    double getSaldo() const;
    
    /**
     * Obtiene la cantidad apostada en la ronda actual
     * @return Monto apostado
     */
    double getApuestaActual() const;
    
    /**
     * Obtiene el nombre del jugador
     * @return String con el nombre
     */
    string getNombre() const;
    
    /**
     * Obtiene el puntero a la mano del jugador
     * @return Puntero a objeto Mano
     */
    Mano* getMano() const;
};

#endif // JUGADOR_H
