Unwrap
======

- Escoger algoritmo de selección de resultados (después del desdoblamiento:)
    - Averiguar sobre alguritmos basados en parasitos
    - Analisis estadistico (analisis de regresión múltiple robusta):
        - ¿Implementado ya? ¿scipy?
        - Diseñar algoritmos ensayo
        - Correr pruebas

Hardware
========

Usan una camara JAI CV-M50 conectada a un framegrabber Matrox Pulsar. Para
procesar las imagenes usan las librerías MIL32 (?) sobre un windows98.

Estoy descargando las librerías nuevas compatibles con nuevos sistemas
operativos y con nuevos lenguajes.

GNU/Linux soporta nativamente las tarjetas Matrox, en los modelos antiguos
suele ser necesario pasarle una opción "-shift n" para ajustar la imagen a la
pantalla.

En caso de migrar los programas a Python hay que analizar el costo teniendo en
cuenta la aparente paralelidad MIL (Matrox Imaging Library) y PIL (Python
Imaging Library) y los costos asociados al aprendizaje de la nueva interfaz.

Tratamiento
===========

Esta sección está suscripta a lo que suceda con la migración y el soporte del
hard del laboratorio.

- Reconstrucción de imagen
- Auto-enfoque

Reconocimiento de formas
========================

- Analisis de burbujas (bubble analisis)
- ¿Algoritmos geneticos?
- ¿Alternativas?
