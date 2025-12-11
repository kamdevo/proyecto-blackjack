// ===========================================
// ARCHIVO: Apuesta.cpp
// Implementación de la clase Apuesta
// ===========================================

#include "Apuesta.h"
#include <iostream>
using namespace std;

// Constructor
Apuesta::Apuesta(double saldoInicial) : saldo(saldoInicial), cantidad(0.0) {}

// Destructor
Apuesta::~Apuesta() {}

// Realiza una apuesta si hay saldo suficiente
bool Apuesta::realizarApuesta(double monto) {
    if (monto <= 0) {
        cout << "La apuesta debe ser mayor a 0." << endl;
        return false;
    }
    
    if (monto > saldo) {
        cout << "Saldo insuficiente. Tu saldo actual es: $" << saldo << endl;
        return false;
    }
    
    cantidad = monto;
    saldo -= monto;
    return true;
}

// Gana la apuesta con un multiplicador
void Apuesta::ganarApuesta(double multiplicador) {
    double ganancia = cantidad * multiplicador;
    saldo += cantidad; // Devolver la apuesta original
    saldo += ganancia; // Agregar la ganancia
    cantidad = 0.0;
}

// Pierde la apuesta
void Apuesta::perderApuesta() {
    // La apuesta ya fue restada del saldo en realizarApuesta()
    cantidad = 0.0;
}

// Empate - devuelve la apuesta
void Apuesta::empate() {
    saldo += cantidad; // Devolver la apuesta
    cantidad = 0.0;
}

// Obtiene la cantidad apostada actualmente
double Apuesta::getCantidadApuesta() const {
    return cantidad;
}

// Obtiene el saldo actual
double Apuesta::getSaldo() const {
    return saldo;
}

// Establece un nuevo saldo
void Apuesta::setSaldo(double nuevoSaldo) {
    saldo = nuevoSaldo;
}

// Verifica si tiene saldo suficiente
bool Apuesta::tieneSaldoSuficiente(double monto) const {
    return saldo >= monto;
}