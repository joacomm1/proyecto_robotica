# proyecto_robotica

Para este proyecto, se tuvo que desarrollar un código para que un robot, proporcionado por el profesor, pudiera realizar un recorrido.

El robot contaba con un sensor como se muestra en la Imagen N°1. La regleta constaba de 8 sensores, de los cuales se utilizaron 6. Se realizaron 3 promedios: el primero con los dos sensores de la izquierda, el segundo promedio con los sensores del medio, y el tercero promedio con los dos sensores de la derecha. Se descartaron los sensores extremos.
![Diagrama](imagenes/sensor.jpg)
Imagen N°1 (referencia del sensor)

Además, el robot contaba con dos motores, lo cual hacía que el robot fuera diferencial. También se utilizó un H-bridge para poder controlar las direcciones de las ruedas y la potencia que se les daba en cada situación.

El problema se resolvió primero calibrando los sensores. De esta manera, el robot tomaba los valores de los sensores cuando estaba en el camino y cuando no lo estaba, y con esos valores creaba un nuevo rango calibrado. La diferencia entre el valor que entregan los sensores cuando están en el camino y cuando no lo están es más amplia, por lo que es más fácil de trabajar y hay más margen de error. Además, se creó una máquina de estados, que incluía avanzar, girar a la derecha, girar a la izquierda y detenerse.

Una vez calibrado, el robot avanzaba y cambiaba de estado dependiendo de los valores del promedio de los sensores. Si el promedio del sensor de la izquierda era menor a 500 (blanco) y los otros dos promedios eran superiores a 500 (negro), entonces el robot giraba a la derecha. Lo mismo ocurría si el promedio de la derecha era menor a 500 (blanco) y los otros dos promedios eran superiores a 500 (negro); entonces giraba a la izquierda. En el caso de que los tres promedios fueran inferiores a 500 (blanco), el robot se detenía. En cualquier otro caso, el robot avanzaba.

![Diagrama](imagenes/recorrido.png)

Imagen N°2 (referencia del recorrido)
