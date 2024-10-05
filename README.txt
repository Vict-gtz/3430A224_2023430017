En la actividad 2, el uso de la organización de los contenedores es completamente manual por el usuario.

El usuario tendrá que mover contenedor por contenedor si es que quisiera mover u eliminar uno en especifico, o también, podría simplemente eliminar los contenedores que están arriba del deseado y después de eliminar/mover el contenedor deseado, ahí volver a insertar los contenedores por medio de la función agregar_contenedor

En el caso de este código quise que fueran 4 colas de máximo 4 contenedores, así que el máximo de contenedores será de 16.


#Detalle de funciones

Menu(): Extiende un menú, el cual, el usuario realizará cierta acción por medio de el número que este elija

Eliminar_contenedor(): La idea de esta función es que, si quisieras acceder rápidamente a un contenedor el cual se encuentre debajo de otros, el usuario podrá simplemente eliminarlos sin necesidad de moverlos a otras pilas

Agregar_contenedor(): Después de que el usuario elimine los contenedores, este podrá volver a insertarlos manualmente si es que eliminó un contenedor por accidente. El usuario podrá agregar nuevos contenedores, limitado por la longitud máxima de la pila (4) y la cantidad de pilas (4)

Mover_contenedor(): Al usuario se le requerirá que indique la pila de la cual quiera mover un contenedor, el contenedor que se mueva siempre va a ser el que se encuentre más arriba/el último que haya sido agregado. Después de que el usuario seleccionara cuál pila mover, se le pedirá una pila de destino, donde el contenedor se agregará arriba de los otros

Mostrar_pilas(): Se le mostrarán al usuario las pilas que hayan, con sus datos actuales. Las pilas se mostrarán en orden de datos más antiguos -> datos más actuales, como simulando contenedores apilados (pero de lado), así que el valor que se encuentre más a la derecha será el accesible, mientras los que se encuentren hacia la izquierda se tendrá primero que realizar alguna acción con el contenedor del extremo derecho/de más arriba.


#Terminal: esto lo agrego mayormente para acordarme yo de como se ejecuta XD

g++ ejercicio2_laboratorio3.cpp -o ejercicio2_laboratorio3

./ejercicio2_laboratorio3 