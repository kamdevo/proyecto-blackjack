# 🐳 Solución: Error "spawn docker ENOENT"

## ❌ Problema

```
Error checking Docker version: spawn docker ENOENT
```

Este error aparece al intentar usar "Reopen in Container" en VS Code.

## 🔍 Causa

**Docker NO está instalado** en tu sistema Linux.

---

## ✅ SOLUCIONES

### Opción 1: Instalar Docker (Recomendado para uso del contenedor)

#### Paso 1: Instalar Docker

```bash
# Actualizar repositorios
sudo apt update

# Instalar Docker
sudo apt install docker.io -y

# Verificar instalación
docker --version
```

#### Paso 2: Configurar permisos (para no usar sudo)

```bash
# Agregar tu usuario al grupo docker
sudo usermod -aG docker $USER

# Aplicar cambios (necesitas cerrar sesión y volver a entrar)
newgrp docker

# Verificar que funciona sin sudo
docker ps
```

#### Paso 3: Iniciar servicio Docker

```bash
# Iniciar Docker
sudo systemctl start docker

# Habilitar Docker al inicio
sudo systemctl enable docker

# Verificar estado
sudo systemctl status docker
```

#### Paso 4: Usar Dev Container en VS Code

1. Abre el proyecto en VS Code
2. Presiona `F1` o `Ctrl+Shift+P`
3. Escribe: "Dev Containers: Reopen in Container"
4. Espera a que se construya el contenedor
5. ¡Listo! Ahora puedes compilar y ejecutar

```bash
# Dentro del contenedor
make
./blackjack
```

---

### Opción 2: Compilar SIN Docker (Más Rápido)

Si no quieres instalar Docker, puedes compilar directamente en tu sistema:

#### Paso 1: Instalar herramientas de compilación

```bash
# Instalar g++, make y Google Test
sudo apt update
sudo apt install -y build-essential libgtest-dev libcurl4-openssl-dev

# Compilar Google Test
cd /usr/src/gtest
sudo cmake .
sudo make
sudo mv lib/*.a /usr/lib
cd -
```

#### Paso 2: Compilar el proyecto

```bash
# Ir al directorio del proyecto
cd /home/kamdevo/Desktop/coding/Proyecto_Blackjack

# Compilar
make

# Ejecutar
./blackjack
```

#### Paso 3: Ejecutar tests

```bash
make google-test
```

---

### Opción 3: Usar Docker Desktop (Windows/Mac)

Si estás en Windows o Mac, instala **Docker Desktop**:

1. Descarga de: https://www.docker.com/products/docker-desktop
2. Instala Docker Desktop
3. Inicia Docker Desktop
4. Vuelve a VS Code y usa "Reopen in Container"

---

## 🚀 Comandos Rápidos

### Si instalaste Docker:

```bash
# Verificar Docker
docker --version
docker ps

# Construir imagen manualmente
cd /home/kamdevo/Desktop/coding/Proyecto_Blackjack
docker build -t blackjack-cpp .devcontainer/

# Ejecutar contenedor
docker run -it --rm \
  -v $(pwd):/home/dev/project \
  -w /home/dev/project \
  blackjack-cpp bash

# Dentro del contenedor
make
./blackjack
```

### Si NO instalaste Docker:

```bash
# Compilar directamente
cd /home/kamdevo/Desktop/coding/Proyecto_Blackjack
make
./blackjack

# Tests
make google-test

# Limpiar
make clean
```

---

## 📋 Verificación

### Verificar que Docker está instalado:

```bash
docker --version
# Debe mostrar: Docker version X.X.X

docker ps
# Debe mostrar lista de contenedores (puede estar vacía)

sudo systemctl status docker
# Debe mostrar: active (running)
```

### Verificar que puedes compilar sin Docker:

```bash
g++ --version
# Debe mostrar: g++ (Ubuntu X.X.X)

make --version
# Debe mostrar: GNU Make X.X

cd /home/kamdevo/Desktop/coding/Proyecto_Blackjack
make
# Debe compilar sin errores
```

---

## 🎯 Recomendación

**Para este proyecto académico:**

### Si tienes tiempo y quieres aprender Docker:
✅ **Instala Docker** (Opción 1)
- Experiencia profesional
- Entorno aislado
- Reproducible en cualquier sistema

### Si necesitas compilar rápido:
✅ **Compila directamente** (Opción 2)
- Más rápido
- Sin dependencias adicionales
- Funciona igual de bien

---

## ⚠️ Nota Importante

**El proyecto funciona perfectamente SIN Docker.**

Docker es solo una **opción adicional** para tener un entorno de desarrollo consistente, pero **NO es necesario** para:
- ✅ Compilar el proyecto
- ✅ Ejecutar el juego
- ✅ Correr los tests
- ✅ Entregar el proyecto

---

## 🔧 Solución del Error Específico

El error **"spawn docker ENOENT"** se soluciona con **UNA** de estas opciones:

1. **Instalar Docker:**
   ```bash
   sudo apt install docker.io -y
   sudo systemctl start docker
   sudo usermod -aG docker $USER
   ```

2. **O simplemente NO usar Dev Container:**
   - Cierra el mensaje de error
   - Compila directamente con `make`
   - El proyecto funciona igual

---

## 📚 Recursos Adicionales

### Documentación de Docker:
- https://docs.docker.com/engine/install/ubuntu/

### Documentación de VS Code Dev Containers:
- https://code.visualstudio.com/docs/devcontainers/containers

### Compilación manual del proyecto:
- Ver `README.md` sección "Compilación y Ejecución"

---

## ✅ Resumen

| Opción | Tiempo | Dificultad | Recomendado para |
|--------|--------|------------|------------------|
| Instalar Docker | 10-15 min | Media | Aprender Docker |
| Compilar directo | 5 min | Fácil | **Entregar rápido** |
| Docker Desktop | 20 min | Fácil | Windows/Mac |

**Elige la opción que mejor se adapte a tus necesidades.** ✨

---

**El proyecto está listo para compilar y ejecutar con o sin Docker.** 🎉
