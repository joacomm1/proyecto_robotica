
Para que el robot realice un recorrido en cuadrado en lugar de un óvalo, se deben realizar algunos ajustes en las condiciones de los sensores y en el control de las ruedas.

Primero, se deben modificar las condiciones de los sensores para determinar cuándo el robot debe girar a la izquierda o a la derecha:

Si el promedio del sensor izquierdo y el promedio del sensor del medio son mayores a 500 (negro), el robot debe girar a la izquierda. En este caso, la rueda derecha debe estar a máxima velocidad y la rueda izquierda debe estar detenida.
Si el promedio del sensor derecho y el promedio del sensor del medio son mayores a 500 (negro), el robot debe girar a la derecha. En este caso, la rueda izquierda debe estar a máxima velocidad y la rueda derecha debe estar detenida.
En cualquier otro caso, el robot debe avanzar derecho. Esto significa que ambas ruedas deben estar a una velocidad normal, permitiendo que el robot avance en línea recta.
Además, se debe calcular un delay para los giros. Este delay debe permitir girar lo suficiente para mantenerse dentro del recorrido y no salirse de él.
