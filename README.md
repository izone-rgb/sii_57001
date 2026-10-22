# Sistemas Informáticos Industriales - Prácticas 1 y 2

![UPM](https://img.shields.io/badge/UPM-ETSIDI-red)
![Curso](https://img.shields.io/badge/Curso-2026--2027-blue)
![Lenguaje](https://img.shields.io/badge/C-Programming-00599C?logo=c)
![Linux](https://img.shields.io/badge/Linux-Ubuntu-E95420?logo=ubuntu)

## 📖 Descripción y Objetivo de las Prácticas

Este repositorio contiene el código de la asignatura Sistemas Informáticos Industriales. 

* **Práctica 1:** Familiarización con el entorno Linux, Git/GitHub, y compilación en C++ con CMake/Make. Se implementó la física básica y el control por teclado para crear un juego de tenis interactivo basado en OpenGL.
* **Práctica 2:** Implementación de un proceso de comunicación interprocesos (IPC) utilizando tuberías con nombre (FIFO). Se ha desarrollado un programa independiente (`logger`) que recibe y registra las puntuaciones del juego en tiempo real. Adicionalmente, el juego finaliza automáticamente cuando un jugador alcanza los 3 puntos.

## 🛠️ Archivos modificados

* **`Esfera.cpp` y `Raqueta.cpp`:** Lógica de movimiento en base a la velocidad, tiempo y entrada por teclado.
* **`Mundo.cpp` y `Mundo.h`:** Gestión de la lógica del juego, apertura de la tubería FIFO en modo escritura, envío de los datos de puntuación mediante `write` y control de cierre al llegar a 3 puntos.
* **`logger.cpp`:** Nuevo ejecutable que crea (`mkfifo`), abre en modo lectura y lee los mensajes enviados por el juego para mostrarlos por pantalla.
* **`CMakeLists.txt`:** Actualizado para compilar simultáneamente el juego principal (`tenis`) y el nuevo programa `logger`.
* **`.gitignore`:** Exclusión del directorio de compilación (`workspace/build/`).

## 🎮 Controles del juego

* **Jugador 1 (Izquierda):** Teclas `W` (arriba) y `S` (abajo)
* **Jugador 2 (Derecha):** Teclas `O` (arriba) y `L` (abajo)

---
*Práctica realizada para la Escuela Técnica Superior de Ingeniería y Diseño Industrial (ETSIDI) - UPM.*
