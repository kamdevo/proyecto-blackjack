/*Juan Camilo Morales - 2515391
Jorge Luis Castro - 2517065
Andrés Felipe Rengifo Rodríguez - 2519613
*/

// ===========================================
// ARCHIVO: Juego.h
// Descripción: Clase principal que coordina el juego
// ===========================================
/*
CRC - Juego

Clase: Juego
Responsabilidades:
- Inicializar y gestionar el mazo de cartas.
- Coordinar jugadores y crupier durante las rondas.
- Repartir cartas, gestionar turnos y determinar ganadores.
- Exponer operaciones de alto nivel para jugar partidas y repetir rondas.
Colaboradores:
- Carta: representación de las cartas del mazo.
- Jugador: entidades participantes en la partida.
- Crupier: ejecuta las acciones del dealer.
- Mano / Apuesta: usadas por jugadores y crupier para estado y apuestas.
Notas:
- Mantiene un vector de punteros a Carta y un índice de carta actual para reparto.
*/
#ifndef JUEGO_H
#define JUEGO_H

#include <vector>
#include "../models/Carta.h"
#include "Jugador.h"
#include "Crupier.h"
using namespace std;

class Juego {
private:
    // Atributos privados
    vector<Carta*> cartas;       // Mazo de cartas para la partida
    int cartaActual;             // Índice de la siguiente carta a repartir
    Crupier* crupier;            // Puntero al crupier de la partida
    vector<Jugador*> jugadores;  // Vector de punteros a los jugadores participantes

public:
    // Constructor y destructor
    /**
     * Constructor que inicializa el juego con mazo vacío, sin crupier ni jugadores
     */
    Juego();
    
    /**
     * Destructor que libera toda la memoria (cartas, crupier, jugadores)
     */
    ~Juego();
    
    // Métodos de gestión del mazo
    /**
     * Crea e inicializa el mazo completo de 52 cartas
     */
    void inicializarCartas();
    
    /**
     * Baraja aleatoriamente el mazo de cartas
     */
    void barajarCartas();
    
    /**
     * Reparte y retorna la siguiente carta del mazo
     * @return Puntero a la siguiente carta disponible
     */
    Carta* repartirCarta();
    
    /**
     * Obtiene el número de cartas restantes en el mazo
     * @return Cantidad de cartas que aún no han sido repartidas
     */
    int getCartasRestantes() const;
    
    // Métodos de configuración
    /**
     * Añade un jugador a la partida
     * @param jugador Puntero al jugador a agregar
     */
    void agregarJugador(Jugador* jugador);
    
    // Métodos de flujo del juego
    /**
     * Inicia una nueva ronda: limpia manos, solicita apuestas y reparte cartas iniciales
     */
    void iniciarRonda();
    
    /**
     * Reparte dos cartas iniciales a cada jugador y al crupier
     */
    void repartirCartasIniciales();
    
    /**
     * Ejecuta el turno de un jugador específico: muestra su mano y gestiona sus decisiones
     * @param jugador Puntero al jugador que va a jugar su turno
     */
    void turnoJugador(Jugador* jugador);
    
    /**
     * Ejecuta el turno del crupier según las reglas del casino
     */
    void turnoCrupier();
    
    /**
     * Compara manos y determina ganadores, perdedores y empates
     * Actualiza los saldos de los jugadores según el resultado
     */
    void determinarGanadores();
    
    /**
     * Orquesta una partida completa: inicializa, ejecuta rondas hasta que no quedan jugadores
     */
    void jugarPartida();
    
    /**
     * Pregunta a los jugadores si desean jugar otra ronda
     * @return true si al menos un jugador quiere continuar, false en caso contrario
     */
    bool preguntarNuevaRonda() const;
};

#endif // JUEGO_H
