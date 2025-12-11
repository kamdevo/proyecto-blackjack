// ===========================================
// ARCHIVO: Crupier.cpp
// Implementación de la clase Crupier
// ===========================================

#include "Crupier.h"
#include <iostream>
using namespace std;

// Constructor
Crupier::Crupier() {
    mano = new Mano();
}

// Destructor
Crupier::~Crupier() {
    delete mano;
}

// Recibe una carta y la agrega a su mano
void Crupier::recibirCarta(Carta* carta) {
    mano->agregarCarta(carta);
}

// Obtiene el valor de la mano
int Crupier::getValorMano() const {
    return mano->calcularValor();
}

// Muestra la mano del crupier
void Crupier::mostrarMano(bool ocultarPrimera) const {
    cout << "\nMano del Crupier:" << endl;
    mano->mostrarMano(ocultarPrimera);
    
    if (!ocultarPrimera) {
        cout << "Valor total: " << mano->calcularValor() << endl;
    } else {
        // Mostrar solo el valor de la carta visible
        if (mano->getNumerCartas() >= 2) {
            cout << "Carta visible muestra un valor parcial" << endl;
        }
    }
}

// Determina si el crupier debe tomar otra carta
// Regla: el crupier debe pedir carta si tiene menos de 17
bool Crupier::debeTomarCarta() const {
    return mano->calcularValor() < 17;
}

// Obtiene la mano del crupier
Mano* Crupier::getMano() const {
    return mano;
}