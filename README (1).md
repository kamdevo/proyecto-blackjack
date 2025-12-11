# 🎰 CASINO BLACKJACK - Juego en C++

## 📋 Descripción General

Este es un **juego de Blackjack completo** implementado en **C++** con arquitectura orientada a objetos. El proyecto está organizado en múltiples clases que representan los elementos del juego: cartas, manos, jugadores, crupier y la lógica general del juego.

### Autores
- Juan Camilo Morales (2515391)
- Jorge Luis Castro (2517065)
- Andrés Felipe Rengifo Rodríguez (2519613)

---

## 🎮 Cómo Funciona el Juego

### Reglas del Blackjack

1. **Objetivo**: Llegar a 21 o lo más cerca posible sin pasarse
2. **Valores de cartas**:
   - Cartas numéricas (2-10): su valor nominal
   - J, Q, K: 10 puntos
   - As (A): 1 u 11 puntos (se calcula automáticamente según lo que sea mejor)
3. **Blackjack**: As + carta de valor 10 (21 con exactamente 2 cartas) = pago 3:2
4. **Reventarse**: Si pasas de 21, pierdes automáticamente
5. **Regla del Crupier**: El crupier debe pedir carta si tiene 16 o menos, y plantarse con 17 o más
6. **Comparación**: Ganas 1:1 si tu valor supera al del crupier sin pasarte
7. **Empate**: Si ambos tienen el mismo valor (≥17), es empate

---

## 🏗️ Arquitectura del Proyecto

### Diagrama de Clases

```
┌─────────────────────────────────────────────────────┐
│                    JUEGO (orquestador)              │
│  - Gestiona mazo, jugadores y crupier              │
│  - Controla flujo de rondas                         │
└─────────────────────────────────────────────────────┘
          │              │              │
          ▼              ▼              ▼
    ┌─────────┐    ┌──────────┐   ┌─────────┐
    │ JUGADOR │    │ CRUPIER  │   │  CARTA  │
    ├─────────┤    ├──────────┤   ├─────────┤
    │ - Mano  │    │ - Mano   │   │- Valor  │
    │ - Apuesta    │ - Lógica │   │- Palo   │
    │         │    │          │   │         │
    └─────────┘    └──────────┘   └─────────┘
         │              │              │
         └──────────────┴──────────────┘
                    │
                    ▼
              ┌──────────┐
              │   MANO   │
              ├──────────┤
              │- Cartas  │
              │- Valor   │
              └──────────┘
```

### Descripción de Clases

#### **1. Carta (Carta.h / Carta.cpp)**
Representa una carta individual de la baraja.
- **Atributos**: valor (A, 2-10, J, Q, K) y palo (♠, ♥, ♦, ♣)
- **Métodos principales**:
  - `getValorNumerico()`: devuelve el valor numérico (1-11 para As, 10 para figuras)
  - `crearMazoCompleto()`: crea 52 cartas (4 palos × 13 valores)
  - `barajarCartas()`: baraja el mazo usando algoritmo Fisher-Yates

#### **2. Mano (Mano.h / Mano.cpp)**
Contiene la colección de cartas de un jugador o crupier.
- **Atributos**: vector de punteros a Carta
- **Métodos principales**:
  - `agregarCarta()`: añade una carta a la mano
  - `calcularValor()`: calcula el valor total según reglas de Blackjack (As = 11 o 1)
  - `tieneBlackjack()`: verifica si hay 21 con exactamente 2 cartas
  - `mostrarMano()`: muestra las cartas (con opción de ocultar la primera)
  - `limpiar()`: vacía la mano para la siguiente ronda

#### **3. Apuesta (Apuesta.h / Apuesta.cpp)**
Gestiona el saldo y las apuestas del jugador.
- **Atributos**: saldo actual, cantidad apostada
- **Métodos principales**:
  - `realizarApuesta()`: deduce la apuesta del saldo
  - `ganarApuesta()`: devuelve apuesta + ganancias (multiplicador 1.0 o 1.5)
  - `perderApuesta()`: procesa derrota (apuesta ya fue deducida)
  - `empate()`: devuelve la apuesta original
  - `getSaldo()`: obtiene saldo disponible
  - `tieneSaldoSuficiente()`: valida fondos para apuesta

#### **4. Jugador (Jugador.h / Jugador.cpp)**
Representa a un jugador del juego.
- **Atributos**: nombre, mano, apuesta
- **Métodos principales**:
  - `recibirCarta()`: añade carta a su mano
  - `getValorMano()`: obtiene valor total de la mano
  - `quiereCarta()`: pregunta interactivamente si quiere otra carta
  - `realizarApuesta()`: realiza una apuesta (delega en Apuesta)
  - `ganar()`: procesa victoria
  - `perder()`: procesa derrota
  - `empate()`: procesa empate
  - `mostrarMano()`: muestra sus cartas

#### **5. Crupier (Crupier.h / Crupier.cpp)**
Representa al distribuidor/crupier del casino.
- **Atributos**: mano de cartas
- **Métodos principales**:
  - `recibirCarta()`: añade carta a su mano
  - `getValorMano()`: obtiene valor total
  - `debeTomarCarta()`: retorna true si valor < 17 (automático, no interactivo)
  - `mostrarMano()`: muestra cartas con opción de ocultar la primera

#### **6. Juego (Juego.h / Juego.cpp)**
Clase orquestadora principal que controla el flujo del juego.
- **Atributos**: mazo de cartas, índice de carta actual, crupier, vector de jugadores
- **Métodos principales**:
  - `inicializarCartas()`: crea y baraja el mazo
  - `repartirCarta()`: entrega cartas, rebaraja cuando sea necesario
  - `iniciarRonda()`: solicita apuestas y limpia manos previas
  - `repartirCartasIniciales()`: da 2 cartas a cada participante
  - `turnoJugador()`: gestiona el turno interactivo del jugador
  - `turnoCrupier()`: gestiona el turno automático del crupier
  - `determinarGanadores()`: compara valores y aplica resultados
  - `preguntarNuevaRonda()`: pregunta si continuar
  - `jugarPartida()`: bucle principal que ejecuta múltiples rondas

---

## 📊 Flujo de Ejecución

```
┌─────────────────────────────────────┐
│   Programa Principal (main.cpp)     │
└─────────────────────────────────────┘
            │
            ▼
    ┌───────────────────┐
    │ Mostrar Bienvenida│
    └───────────────────┘
            │
            ▼
    ┌─────────────────────────────────┐
    │ ¿Ver Reglas? (opcional)         │
    └─────────────────────────────────┘
            │
            ▼
    ┌─────────────────────────────────┐
    │ Ingresar Nombre y Saldo Inicial │
    └─────────────────────────────────┘
            │
            ▼
    ┌─────────────────────────────────┐
    │ Crear Juego y Jugador           │
    └─────────────────────────────────┘
            │
            ▼
    ┌─────────────────────────────────┐
    │  Juego → jugarPartida()         │
    └─────────────────────────────────┘
            │
            └─────────────────┬─────────────────┐
                              │ (Bucle)         │
                              ▼                 ▼
                    ┌──────────────────┐
                    │ 1. Iniciar Ronda │
                    │ - Solicitar Apuesta
                    └──────────────────┘
                            │
                            ▼
                    ┌──────────────────┐
                    │ 2. Repartir Cartas│
                    │ - 2 a cada jugador│
                    │ - 2 al crupier    │
                    └──────────────────┘
                            │
                            ▼
                    ┌──────────────────┐
                    │ 3. Turno Jugadores│
                    │ - Pedir/Plantar  │
                    └──────────────────┘
                            │
                            ▼
                    ┌──────────────────┐
                    │ 4. Turno Crupier │
                    │ - Automático     │
                    └──────────────────┘
                            │
                            ▼
                    ┌──────────────────┐
                    │ 5. Determinar Ganadores
                    │ - Actualizar Saldo
                    └──────────────────┘
                            │
                            ▼
                    ┌──────────────────┐
                    │ ¿Nueva Ronda?    │
                    └──────────────────┘
                            │
                    ┌───────┴───────┐
                    │               │
                 Sí ▼               ▼ No
                (vuelta)       ┌─────────┐
                                │  Fin    │
                                └─────────┘
            │
            ▼
    ┌─────────────────────────────────┐
    │ Mostrar Saldo Final y Resultado │
    └─────────────────────────────────┘
            │
            ▼
        ┌──────┐
        │ EXIT │
        └──────┘
```

---

## 💡 Características Destacadas

✅ **Cálculo inteligente del As**: Se ajusta automáticamente entre 1 y 11  
✅ **Blackjack detection**: Se detecta automáticamente el blackjack natural  
✅ **Múltiples rondas**: Permite jugar indefinidamente mientras haya saldo  
✅ **Gestión de saldo**: Seguimiento automático de ganancias/pérdidas  
✅ **Interfaz interactiva**: El jugador toma decisiones en cada momento  
✅ **Reglas de casino**: El crupier sigue la regla de plantarse en 17+  
✅ **Rebarajado automático**: El mazo se rebaraja cuando se acaban las cartas  
✅ **Gestión de memoria**: Uso correcto de punteros y liberación de recursos  

---

## 🔹 Compilación y Ejecución

### Requisitos previos

1. [Docker](https://docs.docker.com/get-docker/) instalado y corriendo.  
2. [Visual Studio Code](https://code.visualstudio.com/) instalado.  
3. Extensiones recomendadas:  
   - [Dev Containers](https://marketplace.visualstudio.com/items?itemName=ms-vscode-remote.remote-containers)  
   - [C/C++](https://marketplace.visualstudio.com/items?itemName=ms-vscode.cpptools)  

### Compilar y Ejecutar

Dentro del Dev Container:

```bash
make           # Compila con símbolos de depuración
make run       # Ejecuta el binario
make clean     # Limpia binarios
```

El binario generado es `main`.

---

## 📝 Ejemplo de Ejecución

```
========================================
    BIENVENIDO AL CASINO BLACKJACK     
========================================

¿Deseas ver las reglas del juego? (s/n): s

--- REGLAS DEL BLACKJACK ---
1. El objetivo es llegar a 21 o lo mas cerca posible sin pasarse
2. Las cartas numericas valen su numero
3. J, Q, K valen 10 puntos
4. El As vale 1 u 11 (se calcula automaticamente)
5. Blackjack = As + carta de valor 10 (21 con 2 cartas)
6. Si te pasas de 21, pierdes automaticamente
7. El crupier debe pedir carta con menos de 17
8. Ganas 1:1 normalmente, 3:2 con Blackjack
9. Empate si ambos tienen el mismo valor >= 17

Ingrese su nombre: Juan
Ingrese su saldo inicial: $1000

¡Perfecto, Juan! Comencemos a jugar.
Tu saldo inicial es: $1000

========================================
         NUEVA RONDA DE BLACKJACK       
========================================

Juan, tu saldo es: $1000
¿Cuánto deseas apostar? $100
Apuesta realizada: $100
Saldo restante: $900

--- Repartiendo cartas iniciales ---

Juan tiene: A♠ + K♥ = 21 (BLACKJACK)

El Crupier tiene: 7♦ + [OCULTA]

========================================
     TURNO DE Juan
========================================

¡BLACKJACK! Juan tiene 21!

========================================
          TURNO DEL CRUPIER             
========================================

El Crupier tiene: 7♦ + 9♣ = 16

El crupier pide una carta...
El Crupier tiene: 7♦ + 9♣ + 5♠ = 21

El Crupier se planta con 21 puntos.

========================================
            RESULTADOS                  
========================================

Juan (21) vs Crupier (21): EMPATE - Ambos tienen Blackjack
Saldo actual: $1000

¿Deseas jugar otra ronda? (s/n): n

========================================
         FIN DEL JUEGO                  
========================================
Saldo final de Juan: $1000

Terminaste con el mismo saldo con el que empezaste.

¡Gracias por jugar! Vuelve pronto.
```

---

## 🔹 Estructura de Archivos

```
.
├── main.cpp                 # Programa principal - punto de entrada
├── Juego.h / Juego.cpp     # Clase orquestadora del juego
├── Jugador.h / Jugador.cpp # Clase del jugador
├── Crupier.h / Crupier.cpp # Clase del distribuidor
├── Mano.h / Mano.cpp       # Clase que representa la mano de cartas
├── Carta.h / Carta.cpp     # Clase que representa una carta
├── Apuesta.h / Apuesta.cpp # Clase que gestiona apuestas y saldo
├── Makefile                # Configuración de compilación
├── README.md               # Este archivo
└── tests/
    └── test_main.cpp       # Tests unitarios (Google Test)
```

---

## 🔹 Debugging en VS Code
El archivo `.vscode/launch.json` ya incluye la configuración de depuración:
- Debug (gdbserver :2345) → Permite depuración remota con `gdbserver`.
1. En una terminal del contenedor, compila y lanza `gdbserver`:
```bash
make gdbserver
```
Esto mostrará algo como:
```bash
Listening on port 2345
Waiting for gdb connection...
```
2. En VS Code pulsa **F5**. Se conectará al puerto *2345* y podrás depurar de forma remota.

## 🔹 Google Testing
Se debe modificar el archivo `tests/test_main.cpp` con los test que requeridos.

Dentro del Dev Container:

```bash
make google-test       # Ejecuta los test con la librería gtest de google
```

El binario generado es `test_runner`.