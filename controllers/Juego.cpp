// ===========================================
// ARCHIVO: Juego.cpp
// Implementación de la clase Juego
// ===========================================

#include "Juego.h"
#include <iostream>
using namespace std;

// Constructor
Juego::Juego() : cartaActual(0) {
    crupier = new Crupier();
    inicializarCartas();
}

// Destructor
Juego::~Juego() {
    // Liberar cartas
    for (Carta* carta : cartas) {
        delete carta;
    }
    cartas.clear();
    
    // Liberar crupier
    delete crupier;
    
    // Liberar jugadores
    for (Jugador* jugador : jugadores) {
        delete jugador;
    }
    jugadores.clear();
}

// Inicializa el conjunto de cartas
void Juego::inicializarCartas() {
    cartas = Carta::crearMazoCompleto();
    barajarCartas();
}

// Baraja las cartas
void Juego::barajarCartas() {
    Carta::barajarCartas(cartas);
    cartaActual = 0;
}

// Reparte una carta
Carta* Juego::repartirCarta() {
    if (cartaActual >= static_cast<int>(cartas.size())) {
        cout << "\n¡No quedan más cartas! Barajando de nuevo..." << endl;
        barajarCartas();
    }
    return cartas[cartaActual++];
}

// Obtiene el número de cartas restantes
int Juego::getCartasRestantes() const {
    return cartas.size() - cartaActual;
}

// Agrega un jugador al juego
void Juego::agregarJugador(Jugador* jugador) {
    jugadores.push_back(jugador);
}

// Inicia una nueva ronda
void Juego::iniciarRonda() {
    cout << "\n========================================" << endl;
    cout << "         NUEVA RONDA DE BLACKJACK       " << endl;
    cout << "========================================\n" << endl;
    
    // Limpiar manos de la ronda anterior
    for (Jugador* jugador : jugadores) {
        jugador->getMano()->limpiar();
    }
    crupier->getMano()->limpiar();
    
    // Solicitar apuestas
    for (Jugador* jugador : jugadores) {
        double apuesta;
        cout << jugador->getNombre() << ", tu saldo es: $" << jugador->getSaldo() << endl;
        cout << "¿Cuánto deseas apostar? $";
        cin >> apuesta;
        
        while (!jugador->realizarApuesta(apuesta)) {
            cout << "Intenta de nuevo. ¿Cuánto deseas apostar? $";
            cin >> apuesta;
        }
        
        cout << "Apuesta realizada: $" << apuesta << endl;
        cout << "Saldo restante: $" << jugador->getSaldo() << "\n" << endl;
    }
}

// Reparte las cartas iniciales
void Juego::repartirCartasIniciales() {
    cout << "\n--- Repartiendo cartas iniciales ---\n" << endl;
    
    // Repartir 2 cartas a cada jugador
    for (Jugador* jugador : jugadores) {
        jugador->recibirCarta(repartirCarta());
        jugador->recibirCarta(repartirCarta());
    }
    
    // Repartir 2 cartas al crupier
    crupier->recibirCarta(repartirCarta());
    crupier->recibirCarta(repartirCarta());
    
    // Mostrar cartas iniciales
    for (Jugador* jugador : jugadores) {
        jugador->mostrarMano();
    }
    
    crupier->mostrarMano(true); // Ocultar primera carta
}

// Gestiona el turno de un jugador
void Juego::turnoJugador(Jugador* jugador) {
    cout << "\n========================================" << endl;
    cout << "     TURNO DE " << jugador->getNombre() << endl;
    cout << "========================================" << endl;
    
    // Verificar Blackjack
    if (jugador->getMano()->tieneBlackjack()) {
        cout << "\n¡BLACKJACK! " << jugador->getNombre() << " tiene 21!" << endl;
        return;
    }
    
    // Jugador pide cartas
    while (jugador->getValorMano() < 21 && jugador->quiereCarta()) {
        jugador->recibirCarta(repartirCarta());
        jugador->mostrarMano();
        
        if (jugador->getValorMano() > 21) {
            cout << "\n¡TE PASASTE! " << jugador->getNombre() << " pierde." << endl;
            return;
        }
    }
    
    cout << "\n" << jugador->getNombre() << " se planta con " << jugador->getValorMano() << " puntos." << endl;
}

// Gestiona el turno del crupier
void Juego::turnoCrupier() {
    cout << "\n========================================" << endl;
    cout << "          TURNO DEL CRUPIER             " << endl;
    cout << "========================================" << endl;
    
    crupier->mostrarMano(false); // Mostrar todas las cartas
    
    // Verificar Blackjack del crupier
    if (crupier->getMano()->tieneBlackjack()) {
        cout << "\n¡El Crupier tiene BLACKJACK!" << endl;
        return;
    }
    
    // Crupier pide cartas según la regla (menos de 17)
    while (crupier->debeTomarCarta()) {
        cout << "\nEl crupier pide una carta..." << endl;
        crupier->recibirCarta(repartirCarta());
        crupier->mostrarMano(false);
        
        if (crupier->getValorMano() > 21) {
            cout << "\n¡El Crupier se pasó de 21!" << endl;
            return;
        }
    }
    
    cout << "\nEl Crupier se planta con " << crupier->getValorMano() << " puntos." << endl;
}

// Determina los ganadores y aplica resultados
void Juego::determinarGanadores() {
    cout << "\n========================================" << endl;
    cout << "            RESULTADOS                  " << endl;
    cout << "========================================\n" << endl;
    
    int valorCrupier = crupier->getValorMano();
    bool crupierPasado = valorCrupier > 21;
    bool crupierBlackjack = crupier->getMano()->tieneBlackjack();
    
    for (Jugador* jugador : jugadores) {
        int valorJugador = jugador->getValorMano();
        bool jugadorPasado = valorJugador > 21;
        bool jugadorBlackjack = jugador->getMano()->tieneBlackjack();
        
        cout << jugador->getNombre() << " (" << valorJugador << ") vs Crupier (" << valorCrupier << "): ";
        
        // Jugador se pasó
        if (jugadorPasado) {
            cout << "PIERDES - Te pasaste de 21" << endl;
            jugador->perder();
        }
        // Jugador tiene Blackjack
        else if (jugadorBlackjack && !crupierBlackjack) {
            cout << "¡GANAS CON BLACKJACK! (Pago 3:2)" << endl;
            jugador->ganar(1.5); // Pago 3:2
        }
        // Crupier se pasó
        else if (crupierPasado) {
            cout << "¡GANAS! - El crupier se pasó" << endl;
            jugador->ganar(1.0); // Pago 1:1
        }
        // Ambos tienen Blackjack
        else if (jugadorBlackjack && crupierBlackjack) {
            cout << "EMPATE - Ambos tienen Blackjack" << endl;
            jugador->empate();
        }
        // Comparar valores
        else if (valorJugador > valorCrupier) {
            cout << "¡GANAS!" << endl;
            jugador->ganar(1.0); // Pago 1:1
        }
        else if (valorJugador < valorCrupier) {
            cout << "PIERDES" << endl;
            jugador->perder();
        }
        else { // Valores iguales
            if (valorJugador >= 17) {
                cout << "EMPATE" << endl;
                jugador->empate();
            } else {
                cout << "PIERDES - Empate con menos de 17" << endl;
                jugador->perder();
            }
        }
        
        cout << "Saldo actual: $" << jugador->getSaldo() << "\n" << endl;
    }
}

// Pregunta si se desea jugar otra ronda
bool Juego::preguntarNuevaRonda() const {
    // Verificar si algún jugador tiene saldo
    bool alguienTieneSaldo = false;
    for (Jugador* jugador : jugadores) {
        if (jugador->getSaldo() > 0) {
            alguienTieneSaldo = true;
            break;
        }
    }
    
    if (!alguienTieneSaldo) {
        cout << "\n¡No tienes saldo para continuar!" << endl;
        return false;
    }
    
    char respuesta;
    cout << "\n¿Deseas jugar otra ronda? (s/n): ";
    cin >> respuesta;
    return (respuesta == 's' || respuesta == 'S');
}

// Ejecuta el ciclo completo del juego
void Juego::jugarPartida() {
    do {
        iniciarRonda();
        repartirCartasIniciales();
        
        // Turnos de los jugadores
        for (Jugador* jugador : jugadores) {
            if (jugador->getValorMano() <= 21) {
                turnoJugador(jugador);
            }
        }
        
        // Turno del crupier solo si algún jugador no se pasó
        bool algunoEnJuego = false;
        for (Jugador* jugador : jugadores) {
            if (jugador->getValorMano() <= 21) {
                algunoEnJuego = true;
                break;
            }
        }
        
        if (algunoEnJuego) {
            turnoCrupier();
        }
        
        // Determinar ganadores
        determinarGanadores();
        
    } while (preguntarNuevaRonda());
}