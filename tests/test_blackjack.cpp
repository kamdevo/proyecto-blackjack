// ===========================================
// test_blackjack.cpp
// Tests unitarios para el proyecto Blackjack
// ===========================================

#include <gtest/gtest.h>
#include "../models/Carta.h"
#include "../models/Mano.h"
#include "../models/Apuesta.h"
#include "../controllers/Jugador.h"
#include "../controllers/Crupier.h"

// ============================================
// TESTS PARA LA CLASE CARTA
// ============================================

TEST(CartaTest, CrearMazoCompleto) {
    vector<Carta*> mazo = Carta::crearMazoCompleto();
    EXPECT_EQ(mazo.size(), 52);
    
    // Liberar memoria
    for (Carta* carta : mazo) {
        delete carta;
    }
}

TEST(CartaTest, ValorNumericoAs) {
    Carta as("A", "Corazones");
    EXPECT_EQ(as.getValorNumerico(), 11);
}

TEST(CartaTest, ValorNumericoFiguras) {
    Carta jota("J", "Picas");
    Carta reina("Q", "Diamantes");
    Carta rey("K", "Treboles");
    
    EXPECT_EQ(jota.getValorNumerico(), 10);
    EXPECT_EQ(reina.getValorNumerico(), 10);
    EXPECT_EQ(rey.getValorNumerico(), 10);
}

TEST(CartaTest, ValorNumericoNumericas) {
    Carta dos("2", "Corazones");
    Carta cinco("5", "Picas");
    Carta diez("10", "Diamantes");
    
    EXPECT_EQ(dos.getValorNumerico(), 2);
    EXPECT_EQ(cinco.getValorNumerico(), 5);
    EXPECT_EQ(diez.getValorNumerico(), 10);
}

// ============================================
// TESTS PARA LA CLASE MANO
// ============================================

TEST(ManoTest, ManoVacia) {
    Mano mano;
    EXPECT_EQ(mano.getNumerCartas(), 0);
    EXPECT_EQ(mano.calcularValor(), 0);
}

TEST(ManoTest, AgregarCartas) {
    Mano mano;
    Carta* carta1 = new Carta("5", "Corazones");
    Carta* carta2 = new Carta("7", "Picas");
    
    mano.agregarCarta(carta1);
    mano.agregarCarta(carta2);
    
    EXPECT_EQ(mano.getNumerCartas(), 2);
    EXPECT_EQ(mano.calcularValor(), 12);
    
    delete carta1;
    delete carta2;
}

TEST(ManoTest, BlackjackNatural) {
    Mano mano;
    Carta* as = new Carta("A", "Corazones");
    Carta* rey = new Carta("K", "Picas");
    
    mano.agregarCarta(as);
    mano.agregarCarta(rey);
    
    EXPECT_TRUE(mano.tieneBlackjack());
    EXPECT_EQ(mano.calcularValor(), 21);
    
    delete as;
    delete rey;
}

TEST(ManoTest, AjusteDeAs) {
    Mano mano;
    Carta* as = new Carta("A", "Corazones");
    Carta* nueve = new Carta("9", "Picas");
    Carta* cinco = new Carta("5", "Diamantes");
    
    mano.agregarCarta(as);
    mano.agregarCarta(nueve);
    // As vale 11, total = 20
    EXPECT_EQ(mano.calcularValor(), 20);
    
    mano.agregarCarta(cinco);
    // As cambia a 1, total = 15 (1 + 9 + 5)
    EXPECT_EQ(mano.calcularValor(), 15);
    
    delete as;
    delete nueve;
    delete cinco;
}

TEST(ManoTest, LimpiarMano) {
    Mano mano;
    Carta* carta = new Carta("5", "Corazones");
    
    mano.agregarCarta(carta);
    EXPECT_EQ(mano.getNumerCartas(), 1);
    
    mano.limpiar();
    EXPECT_EQ(mano.getNumerCartas(), 0);
    
    delete carta;
}

// ============================================
// TESTS PARA LA CLASE APUESTA
// ============================================

TEST(ApuestaTest, SaldoInicial) {
    Apuesta apuesta(1000.0);
    EXPECT_EQ(apuesta.getSaldo(), 1000.0);
}

TEST(ApuestaTest, RealizarApuestaValida) {
    Apuesta apuesta(1000.0);
    bool resultado = apuesta.realizarApuesta(100.0);
    
    EXPECT_TRUE(resultado);
    EXPECT_EQ(apuesta.getSaldo(), 900.0);
    EXPECT_EQ(apuesta.getCantidadApuesta(), 100.0);
}

TEST(ApuestaTest, RealizarApuestaInvalida) {
    Apuesta apuesta(100.0);
    bool resultado = apuesta.realizarApuesta(200.0);
    
    EXPECT_FALSE(resultado);
    EXPECT_EQ(apuesta.getSaldo(), 100.0);
}

TEST(ApuestaTest, GanarApuesta) {
    Apuesta apuesta(1000.0);
    apuesta.realizarApuesta(100.0);
    apuesta.ganarApuesta(1.0); // Pago 1:1
    
    EXPECT_EQ(apuesta.getSaldo(), 1100.0);
}

TEST(ApuestaTest, GanarBlackjack) {
    Apuesta apuesta(1000.0);
    apuesta.realizarApuesta(100.0);
    apuesta.ganarApuesta(1.5); // Pago 3:2
    
    EXPECT_EQ(apuesta.getSaldo(), 1250.0);
}

TEST(ApuestaTest, PerderApuesta) {
    Apuesta apuesta(1000.0);
    apuesta.realizarApuesta(100.0);
    apuesta.perderApuesta();
    
    EXPECT_EQ(apuesta.getSaldo(), 900.0);
}

TEST(ApuestaTest, Empate) {
    Apuesta apuesta(1000.0);
    apuesta.realizarApuesta(100.0);
    apuesta.empate();
    
    EXPECT_EQ(apuesta.getSaldo(), 1000.0);
}

// ============================================
// TESTS PARA LA CLASE JUGADOR
// ============================================

TEST(JugadorTest, CrearJugador) {
    Jugador jugador("Juan", 1000.0);
    EXPECT_EQ(jugador.getNombre(), "Juan");
    EXPECT_EQ(jugador.getSaldo(), 1000.0);
}

TEST(JugadorTest, RecibirCartas) {
    Jugador jugador("Juan", 1000.0);
    Carta* carta1 = new Carta("5", "Corazones");
    Carta* carta2 = new Carta("7", "Picas");
    
    jugador.recibirCarta(carta1);
    jugador.recibirCarta(carta2);
    
    EXPECT_EQ(jugador.getValorMano(), 12);
    
    delete carta1;
    delete carta2;
}

TEST(JugadorTest, RealizarApuesta) {
    Jugador jugador("Juan", 1000.0);
    bool resultado = jugador.realizarApuesta(100.0);
    
    EXPECT_TRUE(resultado);
    EXPECT_EQ(jugador.getSaldo(), 900.0);
}

// ============================================
// TESTS PARA LA CLASE CRUPIER
// ============================================

TEST(CrupierTest, CrearCrupier) {
    Crupier crupier;
    EXPECT_EQ(crupier.getValorMano(), 0);
}

TEST(CrupierTest, DebeTomarCarta) {
    Crupier crupier;
    Carta* carta = new Carta("10", "Corazones");
    
    crupier.recibirCarta(carta);
    EXPECT_TRUE(crupier.debeTomarCarta()); // 10 < 17
    
    Carta* carta2 = new Carta("7", "Picas");
    crupier.recibirCarta(carta2);
    EXPECT_FALSE(crupier.debeTomarCarta()); // 17 >= 17
    
    delete carta;
    delete carta2;
}

TEST(CrupierTest, NoDebeTomarCartaCon17) {
    Crupier crupier;
    Carta* carta1 = new Carta("10", "Corazones");
    Carta* carta2 = new Carta("7", "Picas");
    
    crupier.recibirCarta(carta1);
    crupier.recibirCarta(carta2);
    
    EXPECT_EQ(crupier.getValorMano(), 17);
    EXPECT_FALSE(crupier.debeTomarCarta());
    
    delete carta1;
    delete carta2;
}

// ============================================
// MAIN DE GOOGLE TEST
// ============================================

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
