# Sistemas Informáticos Industriales - Práctica 1

![UPM](https://img.shields.io/badge/UPM-ETSIDI-red)
![Curso](https://img.shields.io/badge/Curso-2026--2027-blue)
![Lenguaje](https://img.shields.io/badge/C-Programming-00599C?logo=c)
![Linux](https://img.shields.io/badge/Linux-Ubuntu-E95420?logo=ubuntu)

## 📖 Descripción y Objetivo de la Práctica

Este repositorio contiene la **Práctica 1** de la asignatura Sistemas Informáticos Industriales. 

El objetivo principal de esta práctica ha sido familiarizarse con el entorno de desarrollo bajo Linux, el control de versiones con Git/GitHub y la compilación de proyectos en C++ utilizando CMake y Make.

Como resultado práctico, hemos partido de un código estático en OpenGL y lo hemos convertido en un juego de tenis interactivo, aplicando conocimientos de física básica y programación orientada a objetos.

## 🛠️ Archivos modificados en esta sesión

Para lograr la interactividad del juego, se han editado los siguientes ficheros fuente:

* **`Esfera.cpp`**: Se ha implementado la lógica dentro de la función `Mueve()` para que la pelota cambie su posición (`centro.x` y `centro.y`) en base a su velocidad y al tiempo transcurrido, logrando el movimiento continuo por la pantalla.
* **`Raqueta.cpp`**: Se ha completado la función `Mueve()` para permitir el desplazamiento vertical (`y1` e `y2`) de las raquetas en respuesta a la interacción del usuario con el teclado.
* **`.gitignore`**: Se ha creado este archivo para excluir el directorio de compilación (`workspace/build/`) del control de versiones.

## 🎮 Controles del juego

* **Jugador 1 (Izquierda):** Teclas `W` (arriba) y `S` (abajo)
* **Jugador 2 (Derecha):** Teclas `O` (arriba) y `L` (abajo)

---
*Práctica realizada para la Escuela Técnica Superior de Ingeniería y Diseño Industrial (ETSIDI) - UPM.*
