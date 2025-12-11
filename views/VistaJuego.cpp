// ===========================================
// ARCHIVO: VistaJuego.cpp
// Implementación de la clase VistaJuego
// ===========================================

#include "VistaJuego.h"

void VistaJuego::mostrarBienvenida() {
    cout << "\n";
    cout << "========================================\n";
    cout << "    BIENVENIDO AL CASINO BLACKJACK     \n";
    cout << "========================================\n";
    cout << "\n";
}

void VistaJuego::mostrarReglas() {
    cout << "\n--- REGLAS DEL BLACKJACK ---\n";
    cout << "1. El objetivo es llegar a 21 o lo mas cerca posible sin pasarse\n";
    cout << "2. Las cartas numericas valen su numero\n";
    cout << "3. J, Q, K valen 10 puntos\n";
    cout << "4. El As vale 1 u 11 (se calcula automaticamente)\n";
    cout << "5. Blackjack = As + carta de valor 10 (21 con 2 cartas)\n";
    cout << "6. Si te pasas de 21, pierdes automaticamente\n";
    cout << "7. El crupier debe pedir carta con menos de 17\n";
    cout << "8. Ganas 1:1 normalmente, 3:2 con Blackjack\n";
    cout << "9. Empate si ambos tienen el mismo valor >= 17\n";
    cout << "\n";
}

void VistaJuego::mostrarInicioRonda() {
    cout << "\n========================================" << endl;
    cout << "         NUEVA RONDA DE BLACKJACK       " << endl;
    cout << "========================================\n" << endl;
}

void VistaJuego::mostrarTurnoJugador(const string& nombreJugador) {
    cout << "\n========================================" << endl;
    cout << "     TURNO DE " << nombreJugador << endl;
    cout << "========================================" << endl;
}

void VistaJuego::mostrarTurnoCrupier() {
    cout << "\n========================================" << endl;
    cout << "          TURNO DEL CRUPIER             " << endl;
    cout << "========================================" << endl;
}

void VistaJuego::mostrarResultados() {
    cout << "\n========================================" << endl;
    cout << "            RESULTADOS                  " << endl;
    cout << "========================================\n" << endl;
}

void VistaJuego::mostrarFinJuego() {
    cout << "\n========================================\n";
    cout << "         FIN DEL JUEGO                  \n";
    cout << "========================================\n";
}

void VistaJuego::mostrarSeparador() {
    cout << "----------------------------------------" << endl;
}

void VistaJuego::mostrarBlackjack(const string& nombreJugador) {
    cout << "\n¡BLACKJACK! " << nombreJugador << " tiene 21!" << endl;
}

void VistaJuego::mostrarPasado(const string& nombreJugador) {
    cout << "\n¡TE PASASTE! " << nombreJugador << " pierde." << endl;
}
