# Sistemas Informáticos Industriales - Prácticas 1, 2, 3 y 4

![UPM](https://img.shields.io/badge/UPM-ETSIDI-red)
![Curso](https://img.shields.io/badge/Curso-2026--2027-blue)
![Lenguaje](https://img.shields.io/badge/C-Programming-00599C?logo=c)
![Linux](https://img.shields.io/badge/Linux-Ubuntu-E95420?logo=ubuntu)

## 📖 Descripción y Objetivo de las Prácticas

Este repositorio contiene el código de la asignatura Sistemas Informáticos Industriales. 

* **Práctica 1:** Familiarización con el entorno Linux, Git/GitHub, y compilación en C++ con CMake/Make. Se implementó la física básica y el control por teclado para crear un juego de tenis interactivo basado en OpenGL.
* **Práctica 2:** Implementación de comunicación interprocesos (IPC) mediante tuberías con nombre (FIFO) con un programa independiente (`logger`) que registra las puntuaciones en tiempo real y finaliza la partida a los 3 puntos.
* **Práctica 3:** Comunicación interprocesos mediante memoria compartida (`mmap`) con un programa independiente (`bot`) que analiza la posición de la pelota y controla la raqueta izquierda automáticamente.
* **Práctica 4:** Arquitectura Cliente-Servidor y programación concurrente con hilos (`pthread`). El juego se ha dividido en dos procesos (`servidor` y `cliente`) que se comunican de forma bidireccional mediante dos tuberías FIFO (coordenadas y teclas). El servidor gestiona la física y el `logger`, mientras que el cliente captura el teclado y se comunica con el `bot`.

## 🛠️ Archivos del proyecto

* **`Esfera.cpp` y `Raqueta.cpp`:** Lógica de movimiento y colisiones.
* **`servidor.cpp`, `MundoServidor.cpp` y `MundoServidor.h`:** Motor del juego. Envía coordenadas al cliente por FIFO, recibe teclas de forma concurrente mediante un hilo (`pthread`) y notifica los puntos al `logger`.
* **`cliente.cpp`, `MundoCliente.cpp` y `MundoCliente.h`:** Interfaz de usuario. Recibe las coordenadas del servidor para dibujar la escena, envía las teclas pulsadas por FIFO y se sincroniza con el `bot` mediante memoria compartida.
* **`logger.cpp`:** Registra y muestra por pantalla los puntos enviados por el servidor.
* **`bot.cpp` y `DatosMemCompartida.h`:** Controla automáticamente la raqueta del Jugador 1 leyendo la memoria compartida del cliente.
* **`CMakeLists.txt`:** Configurado para compilar `servidor` (enlazado con `pthread`), `cliente`, `logger` y `bot`.
* **`.gitignore`:** Exclusión del directorio de compilación (`workspace/build/`).

## 🎮 Controles del juego

* **Jugador 1 (Izquierda):** Controlado automáticamente por el Bot.
* **Jugador 2 (Derecha):** Teclas `O` (arriba) y `L` (abajo) desde la ventana del Cliente.

---
*Práctica realizada para la Escuela Técnica Superior de Ingeniería y Diseño Industrial (ETSIDI) - UPM.*
