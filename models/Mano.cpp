// ===========================================
// ARCHIVO: Mano.cpp
// Implementación de la clase Mano
// ===========================================

#include "Mano.h"
#include <iostream>
using namespace std;

// Constructor
Mano::Mano() {}

// Destructor - No elimina las cartas porque son gestionadas por Juego
Mano::~Mano() {
    cartas.clear();
}

// Agrega una carta a la mano
void Mano::agregarCarta(Carta* carta) {
    cartas.push_back(carta);
}

// Calcula el valor total de la mano considerando ases
int Mano::calcularValor() const {
    int valor = 0;
    int ases = 0;
    
    // Sumar valores de todas las cartas
    for (Carta* carta : cartas) {
        valor += carta->getValorNumerico();
        if (carta->getValor() == "A") {
            ases++;
        }
    }
    
    // Ajustar el valor de los ases si es necesario
    // Si el valor supera 21 y hay ases, convertir ases de 11 a 1
    while (valor > 21 && ases > 0) {
        valor -= 10; // Cambiar un As de 11 a 1
        ases--;
    }
    
    return valor;
}

// Obtiene el número de cartas en la mano
int Mano::getNumerCartas() const {
    return cartas.size();
}

// Muestra las cartas de la mano
void Mano::mostrarMano(bool ocultarPrimera) const {
    if (cartas.empty()) {
        cout << "  (Sin cartas)" << endl;
        return;
    }
    
    for (size_t i = 0; i < cartas.size(); i++) {
        if (i == 0 && ocultarPrimera) {
            cout << "  [Carta oculta]" << endl;
        } else {
            cout << "  ";
            cartas[i]->mostrar();
            cout << endl;
        }
    }
}

// Limpia la mano para una nueva ronda
void Mano::limpiar() {
    cartas.clear();
}

// Verifica si la mano tiene Blackjack (21 con 2 cartas)
bool Mano::tieneBlackjack() const {
    return (cartas.size() == 2 && calcularValor() == 21);
}