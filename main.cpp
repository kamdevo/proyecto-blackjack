// ===========================================
// main.cpp
// Programa principal del juego Blackjack
// ===========================================

#include <iostream>
#include <string>
#include "controllers/Juego.h"
#include "controllers/Jugador.h"

using namespace std;

void mostrarBienvenida() {
    cout << "\n";
    cout << "========================================\n";
    cout << "    BIENVENIDO AL CASINO BLACKJACK     \n";
    cout << "========================================\n";
    cout << "\n";
}

void mostrarReglas() {
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

int main() {
    mostrarBienvenida();
    
    char verReglas;
    cout << "¿Deseas ver las reglas del juego? (s/n): ";
    cin >> verReglas;
    
    if (verReglas == 's' || verReglas == 'S') {
        mostrarReglas();
    }
    
    // Solicitar información del jugador
    string nombreJugador;
    double saldoInicial;
    
    cout << "\nIngrese su nombre: ";
    cin.ignore(); // Limpiar el buffer
    getline(cin, nombreJugador);
    
    cout << "Ingrese su saldo inicial: $";
    cin >> saldoInicial;
    
    // Validar saldo inicial
    while (saldoInicial <= 0) {
        cout << "El saldo debe ser mayor a 0. Ingrese nuevamente: $";
        cin >> saldoInicial;
    }
    
    // Crear el juego
    Juego* juego = new Juego();
    
    // Crear y agregar el jugador
    Jugador* jugador = new Jugador(nombreJugador, saldoInicial);
    juego->agregarJugador(jugador);
    
    cout << "\n¡Perfecto, " << nombreJugador << "! Comencemos a jugar.\n";
    cout << "Tu saldo inicial es: $" << saldoInicial << "\n";
    
    // Iniciar el juego
    juego->jugarPartida();
    
    // Mostrar saldo final
    cout << "\n========================================\n";
    cout << "         FIN DEL JUEGO                  \n";
    cout << "========================================\n";
    cout << "Saldo final de " << nombreJugador << ": $" << jugador->getSaldo() << "\n";
    
    if (jugador->getSaldo() > saldoInicial) {
        cout << "¡Felicidades! Ganaste $" << (jugador->getSaldo() - saldoInicial) << "\n";
    } else if (jugador->getSaldo() < saldoInicial) {
        cout << "Perdiste $" << (saldoInicial - jugador->getSaldo()) << "\n";
    } else {
        cout << "Terminaste con el mismo saldo con el que empezaste.\n";
    }
    
    cout << "\n¡Gracias por jugar! Vuelve pronto.\n";
    
    // Liberar memoria
    delete juego;  // El destructor de Juego se encarga de liberar jugador
    
    return 0;
}

