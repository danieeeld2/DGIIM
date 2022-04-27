# FIS Ejercicio 3

###### Daniel Alconchel Vázquez

---

Dado el modelo conceptual de la siguiente figura, indique los errores que se observan en el diagrama y represente el correcto.

![Captura de pantalla de 2022-04-22 01-48-34.png](./.sources/Captura%20de%20pantalla%20de%202022-04-22%2001-48-34.png)

Yo he considerado los siguientes errores:

- La multiplicidad de la relación entre cliente y habitación debería ser de varios a uno. Esto se debe a que un cliente podría reservar varias habitaciones, pero una habitación no puede ser reservada por más de un cliente al mismo tiempo.

- En la clase Reserva se debe indicar el tipo de dato que es tanto fechaEntrada como fechaSalida

- La herencia entre habitación y hotel no es correcta, ya que estaríamos considerando que las habitaciones son hoteles. Lo correcto sería considerar una relación varios a uno

En mi caso, considero que el diagrama correcto sería el siguiente:

<img title="" src="./.sources/Class%20Diagram1.jpg" alt="Class Diagram1.jpg" width="699">




