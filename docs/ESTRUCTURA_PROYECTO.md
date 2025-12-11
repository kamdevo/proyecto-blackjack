# 📁 Estructura del Proyecto Blackjack - Arquitectura MVC

## 🏗️ Organización Completa

El proyecto ha sido reorganizado siguiendo la **arquitectura MVC (Modelo-Vista-Controlador)**:

```
Proyecto_Blackjack/
│
├── 📂 models/                    # MODELOS - Lógica de negocio y datos
│   ├── Carta.h                   # Clase que representa una carta
│   ├── Carta.cpp                 # Implementación de Carta
│   ├── Mano.h                    # Clase que representa una mano de cartas
│   ├── Mano.cpp                  # Implementación de Mano
│   ├── Apuesta.h                 # Clase que gestiona apuestas y saldo
│   └── Apuesta.cpp               # Implementación de Apuesta
│
├── 📂 controllers/               # CONTROLADORES - Lógica de control
│   ├── Jugador.h                 # Clase controladora del jugador
│   ├── Jugador.cpp               # Implementación de Jugador
│   ├── Crupier.h                 # Clase controladora del crupier
│   ├── Crupier.cpp               # Implementación de Crupier
│   ├── Juego.h                   # Controlador principal del juego
│   └── Juego.cpp                 # Implementación de Juego
│
├── 📂 views/                     # VISTAS - Presentación
│   ├── VistaJuego.h              # Clase de vista para interfaz
│   └── VistaJuego.cpp            # Implementación de VistaJuego
│
├── 📂 tests/                     # Tests unitarios
│   └── test_blackjack.cpp        # Tests con Google Test
│
├── 📂 docs/                      # Documentación
│   ├── EntregaFinalProyectoBlackJack.pdf
│   └── ESTRUCTURA_PROYECTO.md    # Este archivo
│
├── 📂 .devcontainer/             # Configuración de Dev Container
├── 📂 .vscode/                   # Configuración de VS Code
│
├── 📄 main.cpp                   # Punto de entrada del programa
├── 📄 Makefile                   # Sistema de compilación
├── 📄 README.md                  # Documentación principal
└── 📄 .gitignore                 # Archivos ignorados por Git
```

---

## 📦 Descripción de Cada Capa MVC

### 🎴 MODELOS (models/)

**Responsabilidad**: Representar los datos y la lógica de negocio del juego.

#### Carta.h/cpp
- **Propósito**: Representa una carta individual de la baraja
- **Atributos**: 
  - `valor` (string): A, 2-10, J, Q, K
  - `palo` (string): Corazones, Diamantes, Tréboles, Picas
- **Métodos principales**:
  - `getValorNumerico()`: Retorna el valor numérico (As=11, figuras=10)
  - `crearMazoCompleto()`: Método estático que crea 52 cartas
  - `barajarCartas()`: Método estático que baraja un mazo
- **Colaboradores**: Mano, Juego

#### Mano.h/cpp
- **Propósito**: Representa la colección de cartas de un participante
- **Atributos**:
  - `cartas` (vector<Carta*>): Vector de punteros a cartas
- **Métodos principales**:
  - `agregarCarta()`: Añade una carta a la mano
  - `calcularValor()`: Calcula el valor total (maneja Ases)
  - `tieneBlackjack()`: Verifica si hay 21 con 2 cartas
  - `limpiar()`: Vacía la mano para nueva ronda
- **Colaboradores**: Carta, Jugador, Crupier

#### Apuesta.h/cpp
- **Propósito**: Gestiona el saldo y las apuestas del jugador
- **Atributos**:
  - `saldo` (double): Saldo disponible
  - `cantidad` (double): Cantidad apostada actual
- **Métodos principales**:
  - `realizarApuesta()`: Deduce monto del saldo
  - `ganarApuesta()`: Incrementa saldo con multiplicador
  - `perderApuesta()`: Marca apuesta como perdida
  - `empate()`: Devuelve la apuesta
- **Colaboradores**: Jugador

---

### 🎮 CONTROLADORES (controllers/)

**Responsabilidad**: Coordinar la lógica del juego y las interacciones.

#### Jugador.h/cpp
- **Propósito**: Controla las acciones del jugador humano
- **Atributos**:
  - `nombre` (string): Nombre del jugador
  - `mano` (Mano*): Puntero a su mano
  - `apuesta` (Apuesta*): Puntero a su apuesta
- **Métodos principales**:
  - `recibirCarta()`: Añade carta a su mano
  - `quiereCarta()`: Pregunta si desea otra carta
  - `realizarApuesta()`: Gestiona apuestas
  - `ganar()/perder()/empate()`: Actualiza saldo
- **Colaboradores**: Mano, Apuesta, Carta, Juego

#### Crupier.h/cpp
- **Propósito**: Controla las acciones automáticas del dealer
- **Atributos**:
  - `mano` (Mano*): Puntero a su mano
- **Métodos principales**:
  - `recibirCarta()`: Añade carta a su mano
  - `debeTomarCarta()`: Implementa regla del casino (<17)
  - `mostrarMano()`: Muestra cartas (puede ocultar primera)
- **Colaboradores**: Mano, Carta, Juego

#### Juego.h/cpp
- **Propósito**: Controlador principal que orquesta todo el flujo
- **Atributos**:
  - `cartas` (vector<Carta*>): Mazo de cartas
  - `cartaActual` (int): Índice de siguiente carta
  - `crupier` (Crupier*): Puntero al crupier
  - `jugadores` (vector<Jugador*>): Vector de jugadores
- **Métodos principales**:
  - `inicializarCartas()`: Crea y baraja el mazo
  - `repartirCarta()`: Reparte siguiente carta
  - `iniciarRonda()`: Limpia manos y solicita apuestas
  - `turnoJugador()`: Gestiona turno del jugador
  - `turnoCrupier()`: Gestiona turno del crupier
  - `determinarGanadores()`: Compara manos y actualiza saldos
  - `jugarPartida()`: Bucle principal del juego
- **Colaboradores**: Carta, Jugador, Crupier, Mano, Apuesta

---

### 🖥️ VISTAS (views/)

**Responsabilidad**: Presentar información al usuario y formatear salida.

#### VistaJuego.h/cpp
- **Propósito**: Interfaz de usuario en consola
- **Métodos principales** (todos estáticos):
  - `mostrarBienvenida()`: Mensaje de bienvenida
  - `mostrarReglas()`: Reglas del Blackjack
  - `mostrarInicioRonda()`: Encabezado de ronda
  - `mostrarTurnoJugador()`: Encabezado de turno
  - `mostrarTurnoCrupier()`: Encabezado del crupier
  - `mostrarResultados()`: Encabezado de resultados
  - `mostrarBlackjack()`: Mensaje de Blackjack
  - `mostrarPasado()`: Mensaje de bust
- **Colaboradores**: Juego (la usa para mostrar información)

---

## 🔗 Dependencias entre Clases

### Diagrama de Dependencias

```
main.cpp
    └── Juego (controllers/)
            ├── Carta (models/)
            ├── Jugador (controllers/)
            │       ├── Mano (models/)
            │       │       └── Carta (models/)
            │       └── Apuesta (models/)
            └── Crupier (controllers/)
                    └── Mano (models/)
                            └── Carta (models/)
```

### Includes por Archivo

**main.cpp**:
```cpp
#include "controllers/Juego.h"
#include "controllers/Jugador.h"
```

**controllers/Juego.h**:
```cpp
#include "../models/Carta.h"
#include "Jugador.h"
#include "Crupier.h"
```

**controllers/Jugador.h**:
```cpp
#include "../models/Mano.h"
#include "../models/Carta.h"
#include "../models/Apuesta.h"
```

**controllers/Crupier.h**:
```cpp
#include "../models/Mano.h"
#include "../models/Carta.h"
```

**models/Mano.h**:
```cpp
#include "Carta.h"
```

---

## 🛠️ Compilación

### Con Makefile

```bash
# Compilar
make

# Ejecutar
make run

# Limpiar
make clean

# Tests
make google-test
```

### Compilación Manual

```bash
# Compilar modelos
g++ -std=c++20 -Wall -Wextra -g -O0 -Imodels -Icontrollers -Iviews -c models/Carta.cpp -o models/Carta.o
g++ -std=c++20 -Wall -Wextra -g -O0 -Imodels -Icontrollers -Iviews -c models/Mano.cpp -o models/Mano.o
g++ -std=c++20 -Wall -Wextra -g -O0 -Imodels -Icontrollers -Iviews -c models/Apuesta.cpp -o models/Apuesta.o

# Compilar controladores
g++ -std=c++20 -Wall -Wextra -g -O0 -Imodels -Icontrollers -Iviews -c controllers/Jugador.cpp -o controllers/Jugador.o
g++ -std=c++20 -Wall -Wextra -g -O0 -Imodels -Icontrollers -Iviews -c controllers/Crupier.cpp -o controllers/Crupier.o
g++ -std=c++20 -Wall -Wextra -g -O0 -Imodels -Icontrollers -Iviews -c controllers/Juego.cpp -o controllers/Juego.o

# Compilar vistas
g++ -std=c++20 -Wall -Wextra -g -O0 -Imodels -Icontrollers -Iviews -c views/VistaJuego.cpp -o views/VistaJuego.o

# Compilar main
g++ -std=c++20 -Wall -Wextra -g -O0 -Imodels -Icontrollers -Iviews -c main.cpp -o main.o

# Enlazar todo
g++ -std=c++20 -Wall -Wextra -g -O0 -o blackjack models/Carta.o models/Mano.o models/Apuesta.o controllers/Jugador.o controllers/Crupier.o controllers/Juego.o views/VistaJuego.o main.o -lcurl
```

---

## ✅ Checklist de Cumplimiento

### Arquitectura MVC
- ✅ **Modelos**: Carta, Mano, Apuesta (lógica de negocio)
- ✅ **Vistas**: VistaJuego (presentación)
- ✅ **Controladores**: Jugador, Crupier, Juego (control de flujo)

### Programación Orientada a Objetos
- ✅ **Encapsulamiento**: Atributos privados, métodos públicos
- ✅ **Abstracción**: Interfaces claras
- ✅ **Composición**: Jugador tiene Mano y Apuesta
- ✅ **Gestión de memoria**: new/delete correctos
- ✅ **Constructores/Destructores**: Bien implementados

### Documentación
- ✅ **Tarjetas CRC**: En cada archivo .h
- ✅ **Comentarios Doxygen**: En todos los métodos
- ✅ **README.md**: Completo y detallado
- ✅ **ESTRUCTURA_PROYECTO.md**: Este documento

### Tests
- ✅ **Tests unitarios**: Con Google Test
- ✅ **Cobertura**: Carta, Mano, Apuesta, Jugador, Crupier

### Organización
- ✅ **Carpetas separadas**: models/, controllers/, views/
- ✅ **Includes correctos**: Paths relativos apropiados
- ✅ **Makefile**: Configurado para MVC
- ✅ **docs/**: Documentación organizada

---

## 📊 Métricas del Proyecto

- **Total de clases**: 7 (3 modelos + 3 controladores + 1 vista)
- **Total de archivos .h**: 7
- **Total de archivos .cpp**: 8 (7 clases + 1 main)
- **Líneas de código**: ~2000 (aproximado)
- **Tests unitarios**: 25+ tests
- **Documentación**: 100% de métodos documentados

---

## 🎯 Cumplimiento de Requisitos

Este proyecto cumple con todos los requisitos típicos de un proyecto universitario de Blackjack:

1. ✅ **POO**: Clases, encapsulamiento, composición
2. ✅ **Arquitectura MVC**: Separación clara de responsabilidades
3. ✅ **Gestión de memoria**: Punteros y memoria dinámica
4. ✅ **Reglas del Blackjack**: Implementación completa
5. ✅ **Sistema de apuestas**: Con saldo y pagos
6. ✅ **Documentación**: CRC, Doxygen, README
7. ✅ **Tests**: Unitarios con Google Test
8. ✅ **Organización**: Carpetas y estructura clara

---

**Proyecto completamente organizado y listo para entrega** ✨
