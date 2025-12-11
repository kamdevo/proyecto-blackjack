/*Juan Camilo Morales - 2515391
Jorge Luis Castro - 2517065
Andrés Felipe Rengifo Rodríguez - 2519613
*/

// ===========================================
// ARCHIVO: Apuesta.h
// Descripción: Clase que representa una apuesta en el juego
// ===========================================
/*
CRC - Apuesta

Clase: Apuesta
Responsabilidades:
- Mantener el saldo del jugador y la cantidad apostada.
- Gestionar la lógica de realizar/ganar/perder/empate de apuestas.
- Proveer consultas sobre saldo y validación de fondos.
Colaboradores:
- Jugador: instancia de Apuesta asociada al jugador para registrar montos y actualizar saldo.
- Juego: solicita operaciones de apuesta durante la ronda.
Notas:
- Constructores permiten saldo inicial por defecto.
*/
#ifndef APUESTA_H
#define APUESTA_H

class Apuesta {
private:
    // Atributos privados
    double saldo;    // Saldo actual disponible del jugador
    double cantidad; // Cantidad apostada en la ronda actual

public:
    // Constructor y destructor
    /**
     * Constructor que inicializa la apuesta con un saldo inicial
     * @param saldoInicial Saldo inicial del jugador
     */
    Apuesta(double saldoInicial = 1000.0);
    
    /**
     * Destructor de la clase Apuesta
     */
    ~Apuesta();
    
    // Métodos de gestión de apuestas
    /**
     * Realiza una apuesta deduciendo el monto del saldo si hay fondos suficientes
     * @param monto Cantidad a apostar
     * @return true si la apuesta fue exitosa, false si no hay saldo suficiente
     */
    bool realizarApuesta(double monto);
    
    /**
     * Procesa una apuesta ganada, devolviendo la apuesta más las ganancias
     * @param multiplicador Factor de multiplicación de las ganancias 
     */
    void ganarApuesta(double multiplicador = 1.0);
    
    /**
     * Procesa una apuesta perdida (la cantidad apostada ya fue deducida)
     */
    void perderApuesta();
    
    /**
     * Procesa un empate, devolviendo la apuesta original al saldo
     */
    void empate();
    
    // Métodos de acceso
    /**
     * Obtiene la cantidad apostada en la ronda actual
     * @return Monto apostado
     */
    double getCantidadApuesta() const;
    
    /**
     * Obtiene el saldo actual disponible
     * @return Saldo disponible
     */
    double getSaldo() const;
    
    /**
     * Establece un nuevo saldo
     * @param nuevoSaldo Nuevo saldo a asignar
     */
    void setSaldo(double nuevoSaldo);
    
    /**
     * Verifica si el jugador tiene saldo suficiente para una apuesta
     * @param monto Cantidad a verificar
     * @return true si hay saldo suficiente, false en caso contrario
     */
    bool tieneSaldoSuficiente(double monto) const;
};

#endif // APUESTA_H
