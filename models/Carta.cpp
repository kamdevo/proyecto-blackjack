
// ===========================================
// ARCHIVO: Carta.cpp
// Implementación de la clase Carta
// ===========================================

#include "Carta.h"
#include <iostream>
#include <algorithm>
#include <random>
#include <ctime>
using namespace std;

// Constructor
Carta::Carta(string v, string p) : valor(v), palo(p) {}

// Obtiene el valor numérico de la carta según las reglas del Blackjack
int Carta::getValorNumerico() const {
    if (valor == "A") {
        return 11; // El As vale 11 por defecto, se ajusta en Mano si es necesario
    } else if (valor == "J" || valor == "Q" || valor == "K") {
        return 1; // Ahora las letras valen 1 punto
    } else {
        return stoi(valor); // Convierte string a int para cartas numéricas
    }
}

// Obtiene el valor de la carta como string
string Carta::getValor() const {
    return valor;
}

// Obtiene el palo de la carta
string Carta::getPalo() const {
    return palo;
}

// Muestra la carta en consola
void Carta::mostrar() const {
    cout << valor << " de " << palo;
}

// Método estático para crear un mazo completo de 52 cartas
vector<Carta*> Carta::crearMazoCompleto() {
    vector<Carta*> mazo;
    string palos[] = {"Corazones", "Diamantes", "Treboles", "Picas"};
    string valores[] = {"A", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K"};
    
    // Crear 52 cartas (4 palos x 13 valores)
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 13; j++) {
            mazo.push_back(new Carta(valores[j], palos[i]));
        }
    }
    
    return mazo;
}

// Método estático para barajar un conjunto de cartas
void Carta::barajarCartas(vector<Carta*>& cartas) {
    // Usar random_device para mejor aleatoriedad
    random_device rd;
    mt19937 g(rd());
    
    // Barajar el vector de cartas
    shuffle(cartas.begin(), cartas.end(), g);
}