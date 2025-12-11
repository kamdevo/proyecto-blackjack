// ===========================================
// ARCHIVO: Jugador.cpp
// Implementación de la clase Jugador
// ===========================================

#include "Jugador.h"
#include <iostream>
using namespace std;

// Constructor
Jugador::Jugador(string n, double saldoInicial) : nombre(n) {
    mano = new Mano();
    apuesta = new Apuesta(saldoInicial);
}

// Destructor
Jugador::~Jugador() {
    delete mano;
    delete apuesta;
}

// Recibe una carta y la agrega a su mano
void Jugador::recibirCarta(Carta* carta) {
    mano->agregarCarta(carta);
}

// Obtiene el valor de la mano
int Jugador::getValorMano() const {
    return mano->calcularValor();
}

// Muestra la mano del jugador
void Jugador::mostrarMano() const {
    cout << "\nMano de " << nombre << ":" << endl;
    mano->mostrarMano(false);
    cout << "Valor total: " << mano->calcularValor() << endl;
}

// Pregunta al jugador si quiere otra carta
bool Jugador::quiereCarta() const {
    char respuesta;
    cout << "\n" << nombre << ", ¿quieres otra carta? (s/n): ";
    cin >> respuesta;
    return (respuesta == 's' || respuesta == 'S');
}

// Realiza una apuesta
bool Jugador::realizarApuesta(double cantidad) {
    return apuesta->realizarApuesta(cantidad);
}

// Gana la apuesta
void Jugador::ganar(double multiplicador) {
    apuesta->ganarApuesta(multiplicador);
}

// Pierde la apuesta
void Jugador::perder() {
    apuesta->perderApuesta();
}

// Empate
void Jugador::empate() {
    apuesta->empate();
}

// Obtiene el saldo actual
double Jugador::getSaldo() const {
    return apuesta->getSaldo();
}

// Obtiene la cantidad apostada actualmente
double Jugador::getApuestaActual() const {
    return apuesta->getCantidadApuesta();
}

// Obtiene el nombre del jugador
string Jugador::getNombre() const {
    return nombre;
}

// Obtiene la mano del jugador
Mano* Jugador::getMano() const {
    return mano;
}