# Control FIS

###### Daniel Alconchel Vázquez

---

##### Apartado 1:

<img title="" src="./.sources/Gestión%20de%20Almacenes.jpg" alt="Gestión de Almacenes.jpg" width="700" data-align="center">

- El enunciado nos dice que, de cada pedido, se anotan las incidencias que los empleados observan. He decidido crear una clase incidencia y realizar una composición de la misma con la clase pedido, ya que una incidencia no tiene sentido sin estar asociado a un pedido.

- También, he decidido crear una clase producto asociada a la clase pedido mediante una agregación. Esto se debe a que en el enunciado se especifica que un pedido puede estar formado de varios productos (La clase pedido representa el *todo* mientras que la clase producto representa las *partes*)

- He decidio unir el cliente a la cuenta corriente mediante una relación débil, ya que representa una relación débil y poca duradera en el tiempo, es decir, el cliente usará instancias de la clase cuenta corriente, pero solo en momentos muy puntuales, que, en este caso, es al realizar el pago.

- Algunos comentarios ya menos relevantes son, la decisión de relacionar empleado-pedido-cliente ya que en el enunciado con las respectivas cardinalidades que aparecen en el diagrama, ya que en el enunciado se especifica que cada cliente tiene asignado a un empleado, que actúa como representante de ventas del cliente, aunque cualquier empleado puede gestionar una venta y encargarse de su control desde que se crea hasta que se envían los productos al cliente.

- También, he decidido crear una clase llamada almacena, que se relaciona con almacén y producto para llevar un registo total de todo lo almacena el proveedor en un determinado almacén.

##### Apartado 2:

![Captura de pantalla de 2022-05-05 18-56-32.png](./.sources/Captura%20de%20pantalla%20de%202022-05-05%2018-56-32.png)

![Captura de pantalla de 2022-05-05 18-56-41.png](./.sources/Captura%20de%20pantalla%20de%202022-05-05%2018-56-41.png)
