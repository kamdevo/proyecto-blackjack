# 📖 Explicación Detallada de Métodos - Proyecto Blackjack

Este documento explica **a detalle qué hace cada método** de cada clase del proyecto.

---

## 🎴 MODELOS (models/)

### Clase: Carta

#### `Carta(string v, string p)`
**Constructor**
- **Parámetros**: 
  - `v`: Valor de la carta (A, 2-10, J, Q, K)
  - `p`: Palo de la carta (Corazones, Diamantes, Tréboles, Picas)
- **Qué hace**: Inicializa una carta con el valor y palo especificados usando lista de inicialización.
- **Ejemplo**: `Carta as("A", "Corazones")` crea el As de Corazones.

#### `int getValorNumerico() const`
**Obtiene el valor numérico para cálculos**
- **Retorna**: Valor numérico según reglas del Blackjack
- **Qué hace**:
  1. Si es "A" → retorna 11 (se ajustará en Mano si es necesario)
  2. Si es "J", "Q" o "K" → retorna 10
  3. Si es numérica (2-10) → convierte string a int con `stoi()` y retorna
- **Ejemplo**: `Carta("K", "Picas").getValorNumerico()` retorna 10

#### `string getValor() const`
**Obtiene el valor como string**
- **Retorna**: El valor textual de la carta
- **Qué hace**: Simplemente retorna el atributo privado `valor`
- **Uso**: Para mostrar la carta al usuario

#### `string getPalo() const`
**Obtiene el palo**
- **Retorna**: El palo de la carta
- **Qué hace**: Retorna el atributo privado `palo`
- **Uso**: Para mostrar la carta completa

#### `void mostrar() const`
**Muestra la carta en consola**
- **Qué hace**: Imprime en formato "Valor de Palo"
- **Ejemplo**: Imprime "A de Corazones"
- **No retorna nada** (void)

#### `static vector<Carta*> crearMazoCompleto()`
**Método estático que crea un mazo completo**
- **Retorna**: Vector con punteros a 52 cartas
- **Qué hace**:
  1. Crea un vector vacío
  2. Define arrays de palos (4) y valores (13)
  3. Usa dos bucles anidados para crear todas las combinaciones
  4. Para cada combinación, crea una nueva carta con `new` y la añade al vector
  5. Retorna el vector completo
- **Importante**: El que llama este método es responsable de liberar la memoria

#### `static void barajarCartas(vector<Carta*>& cartas)`
**Método estático que baraja un mazo**
- **Parámetro**: Referencia a vector de cartas (se modifica)
- **Qué hace**:
  1. Crea un generador de números aleatorios (`random_device` y `mt19937`)
  2. Usa `shuffle()` de STL para mezclar el vector aleatoriamente
  3. Implementa el algoritmo Fisher-Yates internamente
- **No retorna nada**, modifica el vector directamente

---

### Clase: Mano

#### `Mano()`
**Constructor**
- **Qué hace**: Constructor vacío, el vector `cartas` se inicializa automáticamente
- **Resultado**: Mano vacía lista para recibir cartas

#### `~Mano()`
**Destructor**
- **Qué hace**: Llama a `cartas.clear()` para vaciar el vector
- **Importante**: NO elimina las cartas (no hace `delete`), porque las cartas son propiedad de `Juego`

#### `void agregarCarta(Carta* carta)`
**Añade una carta a la mano**
- **Parámetro**: Puntero a la carta a agregar
- **Qué hace**: Usa `push_back()` para añadir el puntero al vector
- **No copia la carta**, solo guarda el puntero

#### `int calcularValor() const`
**Calcula el valor total de la mano**
- **Retorna**: Valor numérico total
- **Qué hace** (algoritmo complejo):
  1. Inicializa `valor = 0` y `ases = 0`
  2. Recorre todas las cartas:
     - Suma el valor numérico de cada carta
     - Cuenta cuántos Ases hay
  3. **Ajuste de Ases**: Mientras el valor > 21 Y hay ases:
     - Resta 10 (convierte un As de 11 a 1)
     - Decrementa el contador de ases
  4. Retorna el valor final
- **Ejemplo**: 
  - As + 9 + 5 = 11 + 9 + 5 = 25 (se pasa)
  - Ajusta: 25 - 10 = 15 (As ahora vale 1)

#### `int getNumerCartas() const`
**Obtiene cantidad de cartas**
- **Retorna**: Tamaño del vector
- **Qué hace**: Retorna `cartas.size()`

#### `void mostrarMano(bool ocultarPrimera = false) const`
**Muestra las cartas en consola**
- **Parámetro**: `ocultarPrimera` - si true, oculta la primera carta (para el crupier)
- **Qué hace**:
  1. Si la mano está vacía, muestra "(Sin cartas)"
  2. Recorre todas las cartas con índice:
     - Si es la primera (i==0) Y `ocultarPrimera` es true → muestra "[Carta oculta]"
     - Sino → llama a `carta->mostrar()` para mostrar la carta
  3. Imprime cada carta en una línea nueva con indentación

#### `void limpiar()`
**Limpia la mano para nueva ronda**
- **Qué hace**: Llama a `cartas.clear()` para vaciar el vector
- **No elimina las cartas** de memoria, solo las quita del vector

#### `bool tieneBlackjack() const`
**Verifica si hay Blackjack natural**
- **Retorna**: true si es Blackjack, false si no
- **Qué hace**: Verifica DOS condiciones:
  1. Exactamente 2 cartas (`cartas.size() == 2`)
  2. Valor total es 21 (`calcularValor() == 21`)
- **Ambas deben cumplirse** para ser Blackjack natural

---

### Clase: Apuesta

#### `Apuesta(double saldoInicial = 1000.0)`
**Constructor con saldo inicial**
- **Parámetro**: `saldoInicial` - saldo inicial (default 1000)
- **Qué hace**: Inicializa `saldo` con el valor dado y `cantidad` en 0

#### `~Apuesta()`
**Destructor**
- **Qué hace**: Nada (destructor vacío)
- **No hay memoria dinámica** que liberar en esta clase

#### `bool realizarApuesta(double monto)`
**Realiza una apuesta**
- **Parámetro**: `monto` - cantidad a apostar
- **Retorna**: true si exitosa, false si no
- **Qué hace**:
  1. **Validación 1**: Si monto ≤ 0 → muestra error y retorna false
  2. **Validación 2**: Si monto > saldo → muestra error y retorna false
  3. Si pasa validaciones:
     - Guarda `cantidad = monto`
     - Deduce del saldo: `saldo -= monto`
     - Retorna true
- **Importante**: La apuesta ya se deduce del saldo aquí

#### `void ganarApuesta(double multiplicador = 1.0)`
**Procesa una victoria**
- **Parámetro**: `multiplicador` - factor de ganancia (1.0 para 1:1, 1.5 para 3:2)
- **Qué hace**:
  1. Calcula ganancia: `ganancia = cantidad * multiplicador`
  2. Devuelve apuesta original: `saldo += cantidad`
  3. Añade ganancia: `saldo += ganancia`
  4. Resetea cantidad: `cantidad = 0`
- **Ejemplo**: Apuesta $100, multiplicador 1.5 → gana $150 + recupera $100 = +$250 total

#### `void perderApuesta()`
**Procesa una derrota**
- **Qué hace**: Solo resetea `cantidad = 0`
- **No toca el saldo** porque ya fue deducido en `realizarApuesta()`

#### `void empate()`
**Procesa un empate**
- **Qué hace**:
  1. Devuelve la apuesta: `saldo += cantidad`
  2. Resetea cantidad: `cantidad = 0`
- **Resultado**: El jugador recupera su apuesta

#### `double getCantidadApuesta() const`
**Obtiene la cantidad apostada**
- **Retorna**: Monto apostado actualmente
- **Qué hace**: Retorna el atributo `cantidad`

#### `double getSaldo() const`
**Obtiene el saldo actual**
- **Retorna**: Saldo disponible
- **Qué hace**: Retorna el atributo `saldo`

#### `void setSaldo(double nuevoSaldo)`
**Establece un nuevo saldo**
- **Parámetro**: `nuevoSaldo` - nuevo valor del saldo
- **Qué hace**: Asigna `saldo = nuevoSaldo`
- **Uso**: Para reiniciar o ajustar saldo manualmente

#### `bool tieneSaldoSuficiente(double monto) const`
**Verifica si hay saldo suficiente**
- **Parámetro**: `monto` - cantidad a verificar
- **Retorna**: true si hay suficiente, false si no
- **Qué hace**: Compara `saldo >= monto`

---

## 🎮 CONTROLADORES (controllers/)

### Clase: Jugador

#### `Jugador(string n, double saldoInicial = 1000.0)`
**Constructor**
- **Parámetros**:
  - `n`: Nombre del jugador
  - `saldoInicial`: Saldo inicial (default 1000)
- **Qué hace**:
  1. Inicializa `nombre = n` (lista de inicialización)
  2. Crea nueva Mano: `mano = new Mano()`
  3. Crea nueva Apuesta: `apuesta = new Apuesta(saldoInicial)`
- **Memoria dinámica**: Crea objetos en el heap

#### `~Jugador()`
**Destructor**
- **Qué hace**:
  1. Libera la mano: `delete mano`
  2. Libera la apuesta: `delete apuesta`
- **Importante**: Previene fugas de memoria

#### `void recibirCarta(Carta* carta)`
**Recibe una carta**
- **Parámetro**: Puntero a la carta
- **Qué hace**: Delega a la mano: `mano->agregarCarta(carta)`
- **Patrón**: Delegación a objeto contenido

#### `int getValorMano() const`
**Obtiene valor de la mano**
- **Retorna**: Valor numérico total
- **Qué hace**: Delega a la mano: `return mano->calcularValor()`

#### `void mostrarMano() const`
**Muestra la mano del jugador**
- **Qué hace**:
  1. Imprime "Mano de [nombre]:"
  2. Llama a `mano->mostrarMano(false)` (sin ocultar cartas)
  3. Imprime "Valor total: [valor]"

#### `bool quiereCarta() const`
**Pregunta si quiere otra carta**
- **Retorna**: true si quiere, false si no
- **Qué hace**:
  1. Declara variable `char respuesta`
  2. Muestra mensaje: "[nombre], ¿quieres otra carta? (s/n):"
  3. Lee respuesta con `cin`
  4. Retorna true si es 's' o 'S', false en otro caso

#### `bool realizarApuesta(double cantidad)`
**Realiza una apuesta**
- **Parámetro**: `cantidad` - monto a apostar
- **Retorna**: true si exitosa, false si no
- **Qué hace**: Delega a apuesta: `return apuesta->realizarApuesta(cantidad)`

#### `void ganar(double multiplicador = 1.0)`
**Procesa victoria**
- **Parámetro**: `multiplicador` - factor de ganancia
- **Qué hace**: Delega a apuesta: `apuesta->ganarApuesta(multiplicador)`

#### `void perder()`
**Procesa derrota**
- **Qué hace**: Delega a apuesta: `apuesta->perderApuesta()`

#### `void empate()`
**Procesa empate**
- **Qué hace**: Delega a apuesta: `apuesta->empate()`

#### `double getSaldo() const`
**Obtiene saldo**
- **Retorna**: Saldo actual
- **Qué hace**: Delega a apuesta: `return apuesta->getSaldo()`

#### `double getApuestaActual() const`
**Obtiene apuesta actual**
- **Retorna**: Monto apostado
- **Qué hace**: Delega a apuesta: `return apuesta->getCantidadApuesta()`

#### `string getNombre() const`
**Obtiene nombre**
- **Retorna**: Nombre del jugador
- **Qué hace**: Retorna el atributo `nombre`

#### `Mano* getMano() const`
**Obtiene puntero a la mano**
- **Retorna**: Puntero a Mano
- **Qué hace**: Retorna el puntero `mano`
- **Uso**: Para que Juego pueda acceder a la mano directamente

---

### Clase: Crupier

#### `Crupier()`
**Constructor**
- **Qué hace**: Crea nueva Mano: `mano = new Mano()`
- **Memoria dinámica**: Crea objeto en el heap

#### `~Crupier()`
**Destructor**
- **Qué hace**: Libera la mano: `delete mano`

#### `void recibirCarta(Carta* carta)`
**Recibe una carta**
- **Parámetro**: Puntero a la carta
- **Qué hace**: Delega a la mano: `mano->agregarCarta(carta)`

#### `int getValorMano() const`
**Obtiene valor de la mano**
- **Retorna**: Valor numérico total
- **Qué hace**: Delega a la mano: `return mano->calcularValor()`

#### `void mostrarMano(bool ocultarPrimera = true) const`
**Muestra la mano del crupier**
- **Parámetro**: `ocultarPrimera` - si ocultar primera carta (default true)
- **Qué hace**:
  1. Imprime "Mano del Crupier:"
  2. Llama a `mano->mostrarMano(ocultarPrimera)`
  3. Si NO oculta primera:
     - Imprime "Valor total: [valor]"
  4. Si SÍ oculta primera:
     - Imprime mensaje indicando carta visible

#### `bool debeTomarCarta() const`
**Determina si debe pedir carta**
- **Retorna**: true si debe pedir, false si debe plantarse
- **Qué hace**: Retorna `mano->calcularValor() < 17`
- **Regla del casino**: Pide con menos de 17, se planta con 17 o más

#### `Mano* getMano() const`
**Obtiene puntero a la mano**
- **Retorna**: Puntero a Mano
- **Qué hace**: Retorna el puntero `mano`

---

### Clase: Juego (Controlador Principal)

#### `Juego()`
**Constructor**
- **Qué hace**:
  1. Inicializa `cartaActual = 0` (lista de inicialización)
  2. Crea nuevo Crupier: `crupier = new Crupier()`
  3. Llama a `inicializarCartas()` para crear el mazo

#### `~Juego()`
**Destructor**
- **Qué hace**:
  1. **Libera cartas**: Recorre vector `cartas`, hace `delete` de cada una, luego `clear()`
  2. **Libera crupier**: `delete crupier`
  3. **Libera jugadores**: Recorre vector `jugadores`, hace `delete` de cada uno, luego `clear()`
- **Importante**: Limpia toda la memoria dinámica

#### `void inicializarCartas()`
**Inicializa el mazo**
- **Qué hace**:
  1. Llama a `Carta::crearMazoCompleto()` y asigna a `cartas`
  2. Llama a `barajarCartas()` para mezclar

#### `void barajarCartas()`
**Baraja el mazo**
- **Qué hace**:
  1. Llama a `Carta::barajarCartas(cartas)` para mezclar
  2. Resetea `cartaActual = 0` para empezar desde el principio

#### `Carta* repartirCarta()`
**Reparte la siguiente carta**
- **Retorna**: Puntero a la siguiente carta
- **Qué hace**:
  1. Verifica si `cartaActual >= cartas.size()` (se acabaron las cartas)
  2. Si se acabaron: muestra mensaje y llama a `barajarCartas()`
  3. Retorna `cartas[cartaActual++]` (retorna carta actual e incrementa índice)
- **Post-incremento**: Retorna primero, luego incrementa

#### `int getCartasRestantes() const`
**Obtiene cartas restantes**
- **Retorna**: Cantidad de cartas sin repartir
- **Qué hace**: Retorna `cartas.size() - cartaActual`

#### `void agregarJugador(Jugador* jugador)`
**Añade un jugador**
- **Parámetro**: Puntero al jugador
- **Qué hace**: Añade al vector: `jugadores.push_back(jugador)`

#### `void iniciarRonda()`
**Inicia una nueva ronda**
- **Qué hace**:
  1. Muestra encabezado de nueva ronda
  2. **Limpia manos**: Recorre jugadores y llama a `getMano()->limpiar()`, también limpia mano del crupier
  3. **Solicita apuestas**: Para cada jugador:
     - Muestra su saldo
     - Pide monto a apostar
     - Llama a `realizarApuesta()`
     - Si falla, pide de nuevo (bucle while)
     - Muestra confirmación y saldo restante

#### `void repartirCartasIniciales()`
**Reparte 2 cartas iniciales**
- **Qué hace**:
  1. Muestra mensaje "Repartiendo cartas iniciales"
  2. **A cada jugador**: Reparte 2 cartas con `recibirCarta(repartirCarta())`
  3. **Al crupier**: Reparte 2 cartas
  4. **Muestra manos**: Llama a `mostrarMano()` de cada jugador
  5. **Muestra mano del crupier**: Con primera carta oculta (`mostrarMano(true)`)

#### `void turnoJugador(Jugador* jugador)`
**Gestiona turno de un jugador**
- **Parámetro**: Puntero al jugador
- **Qué hace**:
  1. Muestra encabezado con nombre del jugador
  2. **Verifica Blackjack**: Si `tieneBlackjack()` → muestra mensaje y retorna
  3. **Bucle de decisiones**: Mientras valor < 21 Y quiere carta:
     - Reparte carta con `recibirCarta(repartirCarta())`
     - Muestra mano actualizada
     - Si valor > 21 → muestra "TE PASASTE" y retorna
  4. Si termina bucle sin pasarse → muestra "se planta con X puntos"

#### `void turnoCrupier()`
**Gestiona turno del crupier**
- **Qué hace**:
  1. Muestra encabezado "TURNO DEL CRUPIER"
  2. Muestra mano completa (sin ocultar): `mostrarMano(false)`
  3. **Verifica Blackjack**: Si tiene, muestra mensaje y retorna
  4. **Bucle automático**: Mientras `debeTomarCarta()` (< 17):
     - Muestra mensaje "pide una carta"
     - Reparte carta
     - Muestra mano actualizada
     - Si > 21 → muestra "se pasó" y retorna
  5. Si termina sin pasarse → muestra "se planta con X puntos"

#### `void determinarGanadores()`
**Determina ganadores y actualiza saldos**
- **Qué hace** (algoritmo complejo):
  1. Muestra encabezado "RESULTADOS"
  2. Obtiene valor y estado del crupier (pasado, blackjack)
  3. **Para cada jugador**:
     - Obtiene su valor y estado
     - Muestra comparación: "Jugador (X) vs Crupier (Y):"
     - **Evalúa resultado** (en orden de prioridad):
       a. Si jugador pasado → PIERDE (`perder()`)
       b. Si jugador tiene Blackjack y crupier no → GANA 3:2 (`ganar(1.5)`)
       c. Si crupier pasado → GANA 1:1 (`ganar(1.0)`)
       d. Si ambos tienen Blackjack → EMPATE (`empate()`)
       e. Si jugador > crupier → GANA 1:1
       f. Si jugador < crupier → PIERDE
       g. Si iguales:
          - Si >= 17 → EMPATE
          - Si < 17 → PIERDE
     - Muestra saldo actualizado

#### `bool preguntarNuevaRonda() const`
**Pregunta si jugar otra ronda**
- **Retorna**: true si continuar, false si terminar
- **Qué hace**:
  1. **Verifica saldos**: Recorre jugadores para ver si alguno tiene saldo > 0
  2. Si nadie tiene saldo → muestra mensaje y retorna false
  3. Si alguien tiene saldo:
     - Pregunta "¿Deseas jugar otra ronda? (s/n):"
     - Lee respuesta
     - Retorna true si 's' o 'S', false en otro caso

#### `void jugarPartida()`
**Bucle principal del juego**
- **Qué hace** (orquesta todo):
  1. **Bucle do-while**:
     a. Llama a `iniciarRonda()`
     b. Llama a `repartirCartasIniciales()`
     c. **Turnos de jugadores**: Para cada jugador, si no se pasó, llama a `turnoJugador()`
     d. **Verifica si alguien sigue en juego**: Recorre jugadores para ver si alguno tiene valor ≤ 21
     e. **Turno del crupier**: Solo si alguien sigue en juego, llama a `turnoCrupier()`
     f. Llama a `determinarGanadores()`
  2. **Condición del bucle**: Mientras `preguntarNuevaRonda()` retorne true
- **Este es el método principal** que coordina todo el flujo

---

## 🖥️ VISTAS (views/)

### Clase: VistaJuego

**Nota**: Todos los métodos son **estáticos** (no requieren instancia).

#### `static void mostrarBienvenida()`
**Muestra mensaje de bienvenida**
- **Qué hace**: Imprime banner ASCII con "BIENVENIDO AL CASINO BLACKJACK"

#### `static void mostrarReglas()`
**Muestra las reglas del juego**
- **Qué hace**: Imprime lista numerada con las 9 reglas principales del Blackjack

#### `static void mostrarInicioRonda()`
**Muestra encabezado de ronda**
- **Qué hace**: Imprime banner con "NUEVA RONDA DE BLACKJACK"

#### `static void mostrarTurnoJugador(const string& nombreJugador)`
**Muestra encabezado de turno**
- **Parámetro**: Nombre del jugador
- **Qué hace**: Imprime banner con "TURNO DE [nombre]"

#### `static void mostrarTurnoCrupier()`
**Muestra encabezado del crupier**
- **Qué hace**: Imprime banner con "TURNO DEL CRUPIER"

#### `static void mostrarResultados()`
**Muestra encabezado de resultados**
- **Qué hace**: Imprime banner con "RESULTADOS"

#### `static void mostrarFinJuego()`
**Muestra mensaje de fin**
- **Qué hace**: Imprime banner con "FIN DEL JUEGO"

#### `static void mostrarSeparador()`
**Muestra línea separadora**
- **Qué hace**: Imprime línea de guiones para separar secciones

#### `static void mostrarBlackjack(const string& nombreJugador)`
**Muestra mensaje de Blackjack**
- **Parámetro**: Nombre del jugador
- **Qué hace**: Imprime "¡BLACKJACK! [nombre] tiene 21!"

#### `static void mostrarPasado(const string& nombreJugador)`
**Muestra mensaje de bust**
- **Parámetro**: Nombre del jugador
- **Qué hace**: Imprime "¡TE PASASTE! [nombre] pierde."

---

## 📝 main.cpp

### `void mostrarBienvenida()`
**Función auxiliar de bienvenida**
- **Qué hace**: Imprime el banner de bienvenida del juego

### `void mostrarReglas()`
**Función auxiliar de reglas**
- **Qué hace**: Imprime las reglas del Blackjack

### `int main()`
**Función principal del programa**
- **Qué hace** (flujo completo):
  1. Llama a `mostrarBienvenida()`
  2. Pregunta si quiere ver reglas (s/n)
  3. Si sí, llama a `mostrarReglas()`
  4. **Solicita datos del jugador**:
     - Pide nombre (con `getline` para nombres con espacios)
     - Pide saldo inicial
     - Valida que saldo > 0 (bucle while)
  5. **Crea el juego**: `Juego* juego = new Juego()`
  6. **Crea el jugador**: `Jugador* jugador = new Jugador(nombre, saldo)`
  7. **Agrega jugador al juego**: `juego->agregarJugador(jugador)`
  8. Muestra confirmación
  9. **Inicia el juego**: `juego->jugarPartida()` (aquí ocurre todo)
  10. **Muestra resultados finales**:
      - Saldo final
      - Ganancia o pérdida total
      - Mensaje de despedida
  11. **Libera memoria**: `delete juego` (el destructor de Juego libera el jugador)
  12. Retorna 0 (éxito)

---

## 🔄 Flujo Completo de una Partida

1. **main()** crea Juego y Jugador
2. **Juego::jugarPartida()** inicia bucle principal
3. **Juego::iniciarRonda()** limpia manos y solicita apuestas
4. **Juego::repartirCartasIniciales()** da 2 cartas a todos
5. **Juego::turnoJugador()** para cada jugador:
   - Verifica Blackjack
   - Pregunta si quiere cartas
   - Reparte cartas hasta plantarse o pasarse
6. **Juego::turnoCrupier()** si alguien sigue en juego:
   - Muestra mano completa
   - Pide cartas automáticamente hasta 17+
7. **Juego::determinarGanadores()** compara manos:
   - Evalúa cada caso (Blackjack, bust, valores)
   - Actualiza saldos con `ganar()`, `perder()` o `empate()`
8. **Juego::preguntarNuevaRonda()** pregunta si continuar
9. Si sí, vuelve al paso 3; si no, termina
10. **main()** muestra resultados finales y libera memoria

---

**Documento completo de explicación de métodos** ✅
