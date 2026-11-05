# Sistemas Informáticos Industriales - Prácticas 1, 2 y 3

![UPM](https://img.shields.io/badge/UPM-ETSIDI-red)
![Curso](https://img.shields.io/badge/Curso-2026--2027-blue)
![Lenguaje](https://img.shields.io/badge/C-Programming-00599C?logo=c)
![Linux](https://img.shields.io/badge/Linux-Ubuntu-E95420?logo=ubuntu)

## 📖 Descripción y Objetivo de las Prácticas

Este repositorio contiene el código de la asignatura Sistemas Informáticos Industriales. 

* **Práctica 1:** Familiarización con el entorno Linux, Git/GitHub, y compilación en C++ con CMake/Make. Se implementó la física básica y el control por teclado para crear un juego de tenis interactivo basado en OpenGL.
* **Práctica 2:** Implementación de un proceso de comunicación interprocesos (IPC) utilizando tuberías con nombre (FIFO). Se ha desarrollado un programa independiente (`logger`) que recibe y registra las puntuaciones del juego en tiempo real. Adicionalmente, el juego finaliza automáticamente cuando un jugador alcanza los 3 puntos.
* **Práctica 3:** Implementación de comunicación interprocesos mediante memoria compartida (ficheros proyectados en memoria con `mmap`). Se ha creado un programa independiente (`bot`) que analiza la posición de la pelota y controla la raqueta izquierda de forma automática.

## 🛠️ Archivos modificados

* **`Esfera.cpp` y `Raqueta.cpp`:** Lógica de movimiento original en base a la velocidad y entrada por teclado. Se ha añadido `#pragma once` en las cabeceras para evitar redefiniciones.
* **`Mundo.cpp` y `Mundo.h`:** Gestión de la lógica del juego, apertura de tuberías (logger) y ficheros de memoria compartida. Sincronización continua de las coordenadas para la toma de decisiones.
* **`logger.cpp`:** Ejecutable que recibe los mensajes de puntos a través de una tubería FIFO y los imprime.
* **`bot.cpp` y `DatosMemCompartida.h`:** Nuevo ejecutable y estructura de datos que leen la posición de la esfera en memoria compartida para determinar automáticamente el movimiento de la raqueta.
* **`CMakeLists.txt`:** Actualizado para compilar simultáneamente el juego principal (`tenis`), el `logger` y el `bot`.
* **`.gitignore`:** Exclusión del directorio de compilación (`workspace/build/`).

## 🎮 Controles del juego

* **Jugador 1 (Izquierda):** Controlado automáticamente por el Bot (Inteligencia Artificial).
* **Jugador 2 (Derecha):** Teclas `O` (arriba) y `L` (abajo)

---
*Práctica realizada para la Escuela Técnica Superior de Ingeniería y Diseño Industrial (ETSIDI) - UPM.*
