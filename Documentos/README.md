# 🃏 Proyecto Blackjack - C++

**Implementación del juego de cartas Blackjack (21) en C++ utilizando Programación Orientada a Objetos y Arquitectura MVC**

---

## 👥 Autores

- **Juan Camilo Morales** - 2515391
- **Jorge Luis Castro** - 2517065
- **Andrés Felipe Rengifo Rodríguez** - 2519613

---

## 📋 Descripción

Este proyecto implementa el clásico juego de casino **Blackjack** (también conocido como 21) en C++. El juego simula una partida de casino donde un jugador humano compite contra el crupier (dealer) siguiendo las reglas oficiales del Blackjack.

El proyecto está desarrollado siguiendo principios de **Programación Orientada a Objetos** y utiliza la **arquitectura MVC (Modelo-Vista-Controlador)** para separar la lógica de negocio, la presentación y el control del flujo del juego.

---

## ✨ Características

- ✅ **Mazo completo de 52 cartas** (4 palos × 13 valores)
- ✅ **Reglas oficiales del Blackjack**
- ✅ **Sistema de apuestas** con saldo dinámico
- ✅ **Blackjack natural** paga 3:2
- ✅ **Crupier automático** (pide con <17, se planta con ≥17)
- ✅ **Manejo flexible del As** (vale 1 u 11 según convenga)
- ✅ **Múltiples rondas** de juego consecutivas
- ✅ **Gestión de memoria dinámica** con punteros
- ✅ **Arquitectura MVC** bien estructurada
- ✅ **Documentación CRC** en cada clase

---

## 🏗️ Arquitectura del Proyecto

El proyecto sigue el patrón **MVC (Modelo-Vista-Controlador)**:

```
Proyecto_Blackjack/
├── models/              # MODELOS - Lógica de negocio y datos
│   ├── Carta.h/cpp      # Representa una carta individual
│   ├── Mano.h/cpp       # Colección de cartas de un participante
│   └── Apuesta.h/cpp    # Gestiona saldo y apuestas
│
├── controllers/         # CONTROLADORES - Lógica de control
│   ├── Jugador.h/cpp    # Controla al jugador humano
│   ├── Crupier.h/cpp    # Controla al dealer automático
│   └── Juego.h/cpp      # Orquesta el flujo completo del juego
│
├── views/               # VISTAS - Presentación
│   └── VistaJuego.h/cpp # Interfaz de usuario en consola
│
├── tests/               # Tests unitarios
│   └── test_blackjack.cpp
│
├── docs/                # Documentación
│   └── EntregaFinalProyectoBlackJack.pdf
│
├── main.cpp             # Punto de entrada del programa
├── Makefile             # Sistema de compilación
└── README.md            # Este archivo
```

---

## 📦 Clases Implementadas

### 🎴 MODELOS (models/)

| Clase | Responsabilidad | Archivo |
|-------|----------------|---------|
| **Carta** | Representa una carta con valor y palo. Crea y baraja mazos. | `Carta.h/cpp` |
| **Mano** | Colección de cartas. Calcula valor total y detecta Blackjack. | `Mano.h/cpp` |
| **Apuesta** | Gestiona saldo del jugador y operaciones de apuesta. | `Apuesta.h/cpp` |

### 🎮 CONTROLADORES (controllers/)

| Clase | Responsabilidad | Archivo |
|-------|----------------|---------|
| **Jugador** | Representa al jugador humano. Gestiona decisiones y apuestas. | `Jugador.h/cpp` |
| **Crupier** | Representa al dealer. Implementa lógica automática del casino. | `Crupier.h/cpp` |
| **Juego** | Controlador principal. Orquesta turnos, rondas y determina ganadores. | `Juego.h/cpp` |

### 🖥️ VISTAS (views/)

| Clase | Responsabilidad | Archivo |
|-------|----------------|---------|
| **VistaJuego** | Presenta información al usuario. Formatea salida en consola. | `VistaJuego.h/cpp` |

---

## 🔧 Compilación y Ejecución

### Requisitos Previos

- **Compilador C++** con soporte para C++20 (g++ 10 o superior)
- **Make** (sistema de compilación)
- **Google Test** (opcional, para tests unitarios)

### Comandos de Compilación

```bash
# Compilar el proyecto
make

# Compilar y ejecutar
make run

# Limpiar archivos compilados
make clean

# Ejecutar tests unitarios (requiere Google Test)
make google-test

# Depuración con GDB
make debug

# Depuración remota con gdbserver
make gdbserver
```

### Ejecución Manual

```bash
# Después de compilar con 'make'
./blackjack
```

---

## 🎲 Reglas del Juego

### Objetivo
Obtener **21 puntos** o acercarse lo más posible sin pasarse.

### Valores de las Cartas
- **Cartas numéricas (2-10)**: Valen su número
- **Figuras (J, Q, K)**: Valen 10 puntos
- **As (A)**: Vale 1 u 11 (se ajusta automáticamente)

### Reglas Especiales
1. **Blackjack Natural**: As + carta de 10 (21 con 2 cartas) → Paga 3:2
2. **Bust (Pasarse)**: Si superas 21, pierdes automáticamente
3. **Regla del Crupier**: Debe pedir carta con menos de 17
4. **Empate (Push)**: Si ambos tienen el mismo valor ≥ 17, se devuelve la apuesta

### Sistema de Pagos
- **Victoria normal**: 1:1 (recuperas tu apuesta + ganas lo mismo)
- **Blackjack**: 3:2 (recuperas tu apuesta + ganas 1.5 veces)
- **Empate**: Recuperas tu apuesta
- **Derrota**: Pierdes tu apuesta

---

## 📊 Diagrama de Clases (CRC)

Cada clase incluye su **tarjeta CRC** (Class-Responsibility-Collaborator) en el archivo de cabecera correspondiente, documentando:

- **Responsabilidades**: Qué hace la clase
- **Colaboradores**: Con qué otras clases interactúa
- **Notas**: Detalles de implementación importantes

---

## 🎯 Flujo del Juego

1. **Bienvenida**: El jugador ingresa su nombre y saldo inicial
2. **Inicio de Ronda**:
   - El jugador realiza su apuesta
   - Se reparten 2 cartas a cada participante
   - Se muestra una carta del crupier oculta
3. **Turno del Jugador**:
   - Decide si pedir carta (hit) o plantarse (stand)
   - Puede pedir cartas hasta plantarse o pasarse de 21
4. **Turno del Crupier**:
   - Revela su carta oculta
   - Pide cartas automáticamente hasta tener 17 o más
5. **Determinación de Ganador**:
   - Se comparan las manos
   - Se actualizan los saldos según el resultado
6. **Nueva Ronda**: El jugador decide si continuar o terminar

---

## 💡 Características Técnicas

### Programación Orientada a Objetos
- ✅ **Encapsulamiento**: Atributos privados con métodos públicos
- ✅ **Abstracción**: Interfaces claras y bien definidas
- ✅ **Composición**: Jugador tiene Mano y Apuesta
- ✅ **Gestión de memoria**: Uso correcto de `new`/`delete`
- ✅ **Constructores y destructores**: Inicialización y limpieza adecuadas

### Arquitectura MVC
- **Modelos**: Datos y lógica de negocio independientes
- **Vistas**: Presentación separada de la lógica
- **Controladores**: Coordinan modelos y vistas

### Buenas Prácticas
- ✅ Documentación Doxygen en todos los métodos
- ✅ Nombres descriptivos de variables y funciones
- ✅ Código modular y reutilizable
- ✅ Separación de responsabilidades
- ✅ Comentarios explicativos

---

## 🧪 Tests Unitarios

El proyecto incluye tests unitarios con **Google Test**. Para ejecutarlos:

```bash
make google-test
```

Los tests verifican:
- Creación correcta del mazo (52 cartas)
- Cálculo de valores de las manos
- Detección de Blackjack
- Gestión de apuestas y saldos
- Lógica del crupier

---

## 📝 Ejemplo de Uso

```
========================================
    BIENVENIDO AL CASINO BLACKJACK     
========================================

¿Deseas ver las reglas del juego? (s/n): s

--- REGLAS DEL BLACKJACK ---
1. El objetivo es llegar a 21 o lo mas cerca posible sin pasarse
[...]

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

Mano de Juan:
  A de Corazones
  K de Picas
Valor total: 21

Mano del Crupier:
  [Carta oculta]
  7 de Diamantes

¡BLACKJACK! Juan tiene 21!

========================================
            RESULTADOS                  
========================================

Juan (21) vs Crupier (18): ¡GANAS CON BLACKJACK! (Pago 3:2)
Saldo actual: $1150

¿Deseas jugar otra ronda? (s/n): n

========================================
         FIN DEL JUEGO                  
========================================
Saldo final de Juan: $1150
¡Felicidades! Ganaste $150

¡Gracias por jugar! Vuelve pronto.
```

---

## 📚 Documentación Adicional

Para más detalles sobre los requisitos del proyecto, consulta:
- `docs/EntregaFinalProyectoBlackJack.pdf`

---

## 🐛 Depuración

### Con GDB
```bash
make debug
# Dentro de GDB:
(gdb) break main
(gdb) run
(gdb) next
```

### Con GDB Server (depuración remota)
```bash
# Terminal 1:
make gdbserver

# Terminal 2 (o VS Code):
# Conectar al puerto 2345
```

---

## 🔄 Gestión de Memoria

El proyecto utiliza **memoria dinámica** correctamente:
- Las cartas son creadas por `Juego` y liberadas en su destructor
- `Jugador` y `Crupier` gestionan sus propias `Mano` y `Apuesta`
- No hay fugas de memoria (memory leaks)
- Uso apropiado de punteros y referencias

---

## 📄 Licencia

Proyecto académico desarrollado para la **Universidad del Valle**  
Curso: Programación Orientada a Objetos  
Año: 2024

---

## 🤝 Contribuciones

Este es un proyecto académico. Para sugerencias o mejoras, contactar a los autores.
./blackjack
---

## 📞 Contacto

- Juan Camilo Morales - 2515391
- Jorge Luis Castro - 2517065
- Andrés Felipe Rengifo Rodríguez - 2519613

---

**¡Disfruta jugando Blackjack! 🎰**
