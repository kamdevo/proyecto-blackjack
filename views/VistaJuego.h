/*Juan Camilo Morales - 2515391
Jorge Luis Castro - 2517065
Andrés Felipe Rengifo Rodríguez - 2519613
*/

// ===========================================
// ARCHIVO: VistaJuego.h
// Descripción: Clase de vista para mostrar información del juego
// ===========================================
/*
CRC - VistaJuego

Clase: VistaJuego
Responsabilidades:
- Mostrar mensajes y menús al usuario
- Presentar información del estado del juego
- Formatear la salida en consola
Colaboradores:
- Juego: utiliza la vista para mostrar información
- Jugador: la vista muestra información del jugador
Notas:
- Separa la lógica de presentación de la lógica de negocio
*/
#ifndef VISTAJUEGO_H
#define VISTAJUEGO_H

#include <string>
#include <iostream>
using namespace std;

class VistaJuego {
public:
    /**
     * Muestra el mensaje de bienvenida del juego
     */
    static void mostrarBienvenida();
    
    /**
     * Muestra las reglas del Blackjack
     */
    static void mostrarReglas();
    
    /**
     * Muestra el encabezado de una nueva ronda
     */
    static void mostrarInicioRonda();
    
    /**
     * Muestra el encabezado del turno de un jugador
     * @param nombreJugador Nombre del jugador
     */
    static void mostrarTurnoJugador(const string& nombreJugador);
    
    /**
     * Muestra el encabezado del turno del crupier
     */
    static void mostrarTurnoCrupier();
    
    /**
     * Muestra el encabezado de resultados
     */
    static void mostrarResultados();
    
    /**
     * Muestra el mensaje de fin del juego
     */
    static void mostrarFinJuego();
    
    /**
     * Muestra un separador visual
     */
    static void mostrarSeparador();
    
    /**
     * Muestra un mensaje de Blackjack
     * @param nombreJugador Nombre del jugador con Blackjack
     */
    static void mostrarBlackjack(const string& nombreJugador);
    
    /**
     * Muestra un mensaje cuando alguien se pasa de 21
     * @param nombreJugador Nombre del jugador que se pasó
     */
    static void mostrarPasado(const string& nombreJugador);
};

#endif // VISTAJUEGO_H
