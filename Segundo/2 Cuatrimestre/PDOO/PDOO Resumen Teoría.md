# PDOO: Resumen Teoría

### <u>Atributos y Métodos</u>

Los **atributos** son variables que están asociadas a cada objeto de la clase (*instancias de la clase*). Mediante sus valores se describe el estado de cada instancia.

Llamaremos **métodos de instancia** a funciones definidad en una clase y que estan ligadas a los objetos de la misma. Se llaman desde las propias instancias de la clase.

Llamamos **atributo de clase** a aquellas variables que almacenan información asociada a la propia clase, pero no de cada instancia. **Se recurre a ellas cuando se necesita almacenar información que siempre va a ser común a todas las instancias de la clase, ya que no tendría sentido que cada instancia guardase una copia de dicho valor, además de que sería bastante costosa la actualizacion de la misma.**

En Ruby existen dos tipos de atributos de clase:

- **Atributos de clase (@@atributo_de_clase):** Son accesibles desde el ámbito de clase y de instancia. Además, **se comparten entre las subclases**.

- **Atributos de instancia de la clase(@atributo_instancia_de_clase): ** No se comparten entre las subclases y solo se puede acceder desde el ámbito de clase.

  ```ruby
  class Clase
      @@variable = "De clase"
      @variable = "De instancia de clase"
      
      def initialize
          @variable = "De instancia"
      end
      def muestraValores
          puts @@variable # De clase
          puts @variable # De instancia
      end
      def self.muestraValores
          puts @@variable # De clase
          puts @variable # De instancia de la clase
      end
  ```

Llamamos **métodos de clase** a aquellas funciones asociadas a la propia clase. A estas funciones se acceden directamente desde la clase.

- En Java se usa **static** para referirse al ámbito de clase.

Llamaremos **pseudovariables** a las palabras reservadas:

- **this** en Java
- **self** en Ruby

### <u>Constructores</u>

Los **constructores** son métodos especiales, que se encargan de la inicialización de las instancias. (*Recuerda que debes inicializar todos los atributos de instancia*)

En **Java**:

- Tienen el mismo nombre de la clase y no devuelven nada.
- Se permite sobrecarga (Puede haber varios constructores con el mismo nombre, pero distintos parámetros).
- Se puede llamar a un constructor desde otro.
- Existe un constructor por defecto, sin parámetros.

```java
class Point3D{
    private int x;
    private int y;
    private int z;
    
    Point3D(int a, int b, int c){
        x=a;
        y=b;
        z=c;
    }
}
...
Point3D p1 = new Point3D(1,1,1);
```

En **Ruby**:

- Existe un método especial llamado **initialize**.
- Es un método de instancia privado que es llamado automáticamente por **new** y debe encargarse de la creación e inicialización de todos los atributos.
- No puede sobrecargarse, pero podemos crear varios constructores mediante métodos de clase que hagan una llamada a initialize.

```ruby
class Point3D
    def initialize(a,b,c)	# Para inicializer un valor por defecto se iguala directamente
    	@x=a
    	@y=b
    	@z=c
	end
	def self.new_2D(a,b)
		new(a,b,0)
	end
	private_class_method :new	# Pasa a ser privado

	# Para inicializer un valor por defecto se iguala directamente
	initialize(a,b=0,c)
	...
end

```

### <u>Consultores y Modificadores</u>

Llamamos **consultores** a los métodos encargados de devolver un atributo (***Diseño:*** Solo deben crearse los consultores que sean necesarios)

- **getAtributo()** en Java.
- **atributo** en Ruby.

Llamaremos **modificadores** a los métodos encargado de modificar el valor de un atributo  (***Diseño:*** Solo deben crearse los modificadores que sean necesarios)

- **setAtributo()** en Java.
- **atributo** en Ruby.

```Java
// Java
public class Persona{
    private static final int MAYOREDAD = 18;	// final significa constante
    private int edad;
    
    Persona(int a){
        edad = a;
    }
    public void setEdad(int a){
        edad = a;
    }
    public int getEdad(){
        return a;
    }
}
```

```ruby
# Ruby
class Persona
    @@MAYOR_EDAD=18
    def initialize(a)
        @edad=a
    end
    attr_reader :edad	# Consultor
    attr_writer :edad	# Modificador
    attr_accessor :edad # Consultor+Modificador
    def self.MAYOR_EDAD(e)
        @@MAYOR_EDAD=e
    end
end
```

### <u>Agrupación de Elementos</u>

En Java tenemos los **paquetes**. Existe una visibilidad de paquete que otros lenguajes no tienen.

- Para decir que un archivo pertenece a un paquete hay que indicarlo al comienzo del mismo.
- Para usar un elemento de un paquete distinto al actual hay que indicarlo.

```java
package ejemplo
import otropaquete.claseejemplo
```

En Ruby tenemos los **módulos**, que permiten agrupar una gran variedad de elementos. (*Recuerda que en Ruby si debes "importar"(añadir) los ficheros que vayas a usar en el fichero actual mediante require_relative*)

### <u>Herencia</u>

La **herencia** permite derivar clases a partir de clases existentes.

La clase de la que se deriva se conoce como **padre** y la clase derivada como **hija o subclase**, la cual, hereda todo el código del padre (Cada lenguaje tiene sus particularidades y esto no implica que la clase hija pueda acceder a todos los ámbitos de la clase padre).

La herencia se usa para aprovechar **la reutilización de código** y a que una clase hija puede verse como una **especialización (caso concreto)** de la clase padre (***Ojo:*** *A nivel de diseño no puede verse la reutilización de código como una excusa para derivar una clase, debe existir una relación a nivel conceptual*)

Se **redefine o sobreescribe** un método de una clase cuando se administra una implementación alternativa a la heredada. En general, basta con definir un método con la misma signatura (cabecera) y añadir la nueva implementación.

En **Java**:

- **No pueden ser redefinidos los métodos declarados como final o privados**.
- Usar **@Override** delante del método, para indicar que se está sobreescribiendo.

En **Ruby:**

- Al crear un método con el mismo nombre que uno de la clase padre, se sobrescribe automáticamente, ya que no existe sobrecarga.

La palabra reservada **super** nos permite acceder a código del padre desde la clase hija. En cada lenguaje hay una serie de particularidades:

- **Java:**
  - Permite acceder a la implementación de cualquier método proporcionado por la clase padre.
  - Permite referenciar al constructor de la clase padre, **pero debe aparecer en la primera línea y es obligatoria**.
- **Ruby:**
  - Solo permite acceder en la clase padre a la implementación del mismo método que está siendo redefinido.
  - Si se utiliza sin argumentos, se pasa automáticamente los mismos que los definidos por el método redefinido.
  - La **llamada a super en el initialize no se produce implícitamente, es responsabilidad nuestra**.

```java
class Persona{
	private String nombre;
    public Persona (String n){
        nombre = n;
    }
    public String andar(){return ("Ando como una persona");}
    public String hablar(){return ("Hablo como una persona";)}
}

class Profesor extends Persona{
    private String asignatura;
    public Profesor(String n, String a){
        super(n);
        asignatura = a;
    }
    @Override
    public String hablar(){("Hablo como un profesor");}
}
```

```ruby
class Persona
    def initialize(n)
        @nombre=n
    end
    def andar
        "Ando como una persona"
    end
    def hablar
        "Hablo como una persona"
    end
end

class Profesor < Persona
    def initialize(n,a)
        super(n)	# No tiene porque ser en la primera línea
        @asignatura=a
    end
    def hablar
        "Hablo como un profesor y " + super # Hablo como un profesor y Hablo como una persona
    end
end
```

### <u>Visibilidad</u>

La **visibilidad** permite restringir el acceso a atributos y métodos. **Ocultan detalles de implementación para que los objetos sean usados a través de una interfaz concreta**.

Los especificadores de acceso habituales son:

- Privado
- Protegido
- Público

Java, además, cuenta con una visibilidad de paquete.

**Especificadores de acceso en Java:**

- Especificador **private**:
  - **Accesible desde código de la propia clase**, ya sea ámbito de instancia o de clase.
  - **Se puede acceder a elementos privados de otra instancia distinta, siempre que sean de la misma clase**.
- **Paquete:**
  - No poner ningún especificador significa visibilidad de paquete.
  - Estos elementos son **públicos dentro del paquete y privados fuera del mismo**.
- **Public:**
  - Utiizables desde cualquier sitio.

- **Protected: **
  - Estos elementos son **públicos dentro del mismo paquete**.
  - También son **accesibles desde subclases de otros paquetes**.
  - Para poder acceder a elementos protegidos de una instancia distinta:
    - Esta instancia tiene que ser de la misma clase que la propietaria del código desde la que se realiza el acceso o una subclase de la misma.
    - El elemento accedido debe estar declarado en la clase propieta del código desde la que se realiza el acceso o una subclase de la misma.
    - **Recordar:** Si las clases involucradas están dentro del mismo paquete, los objetos protegidos son accesibles siempre.

**Especificadores de acceso Ruby:**

- Los **atributos** son siempre **privados** y no se puede cambiar.
- Los **métodos** son por defecto públicos, pero se puede modificar mediante especificadores de acceso.
- El método **initialize** es **privado** y no se puede cambiar.
- **Private:**
  - No se puede acceder a métodos privados de clase desde el ámbito de instancia y viceversa.
  - Si B hereda de A, desde un ámbito de instancia de B se pueden llamar a los métodos privados de instancia de A, y desde un ámbito de clase de B se pueden llamar a los métodos privados de clase de A.
  - Un método privado nunca puede ser utilizado mediante un receptor de mensaje explícito. (A partir de Ruby 2.7 si se permite self como receptor)
- **Protected:**
  - Los métodos protegidos si pueden ser invocados con un receptor de mensaje explícito dentro del mismo contexto.
  
    ```ruby
    class Padre
        @c=0
        def initialize(a,b)
            @a=a
            @b=b
        end
    
        protected
        attr_reader :a, :b, :c
    
        def self.newCopy(p)
            @c+=1
            new(p.a,p.b) # Da error porque p es otra instancia (está en otro contexto)
        end
    
        def salida
            puts @a+1
            puts @b+1
            puts @c+1 unless @c.nil?
        end
    end
    
    class Hija < Padre
        def salida
            super
            puts "fin"
        end
    end
    
    p=Padre.new(1,2)
    p2=Padre.newCopy(p)	
    p.salida
    ```
  
    
  
  - No existen métodos protegidos de clase.

### <u>Clases Abstractas e Interfaces</u>

Las **clases abstractas** representan de manera genérica a otras entidades que sí concretan un funcionamiento desconocido, es decir, modelan entidades que se saben que información y funcionalidad contienen, pero no como se realiza dicha funcionalidad.

- Se declaran como tal y no suelen proporcionar implementación de sus métodos, que se denominan **abstarctos**.
- **No es posible instanciar una clase abstracta**.
- Son una herramienta de diseño que obligan a sus subclases a tener una serie de métodos (a implementar) y atributos comunes.

En Java se utiliza la palabra reservada **abstract**, mientras que en Ruby, al no existir las clases abstractas, se usa como solución hacer **privado el método new en el padre** y volver a **hacerlo público en los hijos**.

```java
abstract class FiguraGeometrica{
    public abstract float area();
}
class Triangulo extends FiguraGeometrica{...}
class Cuadrado extends FiguraGeometrica{...}
```

```ruby
class FiguraGeometrica
    def area
    end
    private_class_method :new
end
class Cuadrado < FiguraGeometrica
    ...
end
```

Una **interfaz** definde un  determinado protocolo de comportamiento y permite la reutilización de dicho protocolo (Contrato que cumplen las clases que realizan dicha interfaz y seráuna clase quien implemente dicho comportamiento).

Una interfaz solo puede tener:

- Constantes
- Signaturas de métodos
- Métodos de tipo **default** (Métodos implementados en la interfaz)
- El equivalente a los métodos de clase **static**
- Solo los métodos default y static pueden tener una implementación asociada.

**No pueden ser instanciadas, solo realizadas por una clase o extendida por otras interfaces**.

- Una clase abstracta puede heredar de una clase y de varias interfaces.
- Una clase abstracta puede indicar una interfaz sin implementar alguno de sus métodos (lo implementan sus descendientes)
- Ruby no soporta interfaces.

```java
interface interfaz1{
    String hazAlgo ();
    default String hazAlgo2() {return "2";}
}
interface interfaz2{
    default String hazAlgo2() {return "22";}
}
class Test implements interfaz{
    @Override
    public String hazAlgo(){return "algo1";}
    // Por colisión debe redefinir
    @Override
    default String hazAlgo2() {
        String a = Interface1.super.hazAlgo2();
        String b = Interface2.super.hazAlgo2();
        return (a+b);
    }
}
```

### <u>Clases parametrizables</u>

Las **clases parametrizables** son clases definidas en función de un tipo de dato. Se generalizan un conjunto de operaciones válidas para diferentes tipos de datos.

```java
class Lista <T>{
	...
}
Lista <Persona> listaPersonas = new ...;
Lista <Mascota> listaMascota = new ...;
```

En Java, este concepto se implementa mediante los **tipos genéricos**, que permiten pasar tipos como parámetros a clases e interfaces.

Se puede forzar que el tipo suministrado a una clase parametizable sea:

- Subclase de otro

  ```java
  class Clase <T extends ClaseBase>
  ```

- Realizar una interfaz

  ```java
  class Clase <T extends Interfaz>
  ```

![Captura de pantalla de 2021-06-24 13-17-18](https://github.com/danieeeld2/DGIIM/blob/master/Segundo/2%20Cuatrimestre/PDOO/.img/Captura%20de%20pantalla%20de%202021-06-24%2013-17-18.png)

La implementación de una clase parametrizable puede requerir que **T** disponga de un determinado método:

```java
class Mazo <T> {
    T getCopiaPrimeraCarta(){
        T primeraCarta = carta.remove(0);
        cartas.add(primeraCarta);
        return primeraCarta.copia(); // Se requiere que T tenga este método
    }
}
```

En este caso:

- El método requerido formará parte de una interfaz.
- Al declarar la clase parametrizable se indicará que el tipo que sustituya debe realizar dicha interfaz.

```java
// Las interfaces se pueden hacer paramétricas, como las clases
interface Copiable <T> {
    public T copia();
}

class Sorpresa implements Copiable<Sorpresa>{
    public Sorpresa copia(){
        return Sorpresa(this);	// Constructor de copia
    }
}

class Mazo <T extends Copiable<T>> {	// Obliga a que T realice Copiable<T>
    T getCopiaPrimeraCarta(){
        T primeraCarta = carta.remove(0);
        cartas.add(primeraCarta);
        return primeraCarta.copia(); // Se requiere que T tenga este método
    }
}
Mazo<Sorpresa> mazoSorpresa = new Mazo<>();
```

### <u>Polimorfismo</u>

El **polimorfismo** es la capacidad de un identificador de **referenciar a objetos de diferentes tipos (clases)**

- Ruby no utiliza mecanismo de declaración de variables, luego, cualquier variable puede referenciar cualquier tipo de objeto.
- En lenguajes con declaración de variables con un tipo específico existen limitaciones al respecto.

El **principio de sustitución de Liskov:** Si B es un subtipo de A, se puede usar instancias de B donde se usan instancias de A (*Por ejemplo, anteriormente vimos la subclase Director de Persona. Luego, se pueden usar instancias de Director donde las instancias de Persona*)

- **Tipo estático:** Tipo (clase) del que se declara la variable.
- **Tipo dinámico:** Clase al que pertenece el objeto referenciado en un momento determinado por una variable.

- **Ligadura estática:** El enlace del código a ejecutar asociado a una llamada a un método se hace en tiempo de compilación.
- **Ligadura dinámica: ** El tipo dinámico determina el código que se ejecutará asociado a la llamada de un método.

```java
class FiguraGeometrica{
    float area(){return 0.0f;}
}
class Circulo extends FiguraGeometrica{
    float area(){return Math.PI*radio*radio;}
}
class Rectangulo extends FiguraGeometrica{
    float area(){return lado1*lado2;}
}
...
ArrayList<FiguraGeometrica> coleccionDeFiguras = new ArrayList<>();
coleccionDeFiguras.add(new Circulo(radio));
coleccionDeFiguras.add(new Rectangulo(lado1,lado2));

float suma = 0.0f;
for(FiguraGeometrica unaFigura : coleccionDeFiguras)
    suma+=unaFigura.area();
```

![Captura de pantalla de 2021-06-24 17-14-54](https://github.com/danieeeld2/DGIIM/blob/master/Segundo/2%20Cuatrimestre/PDOO/.img/Captura%20de%20pantalla%20de%202021-06-24%2017-14-54.png)

El tipo **estático** está limitado por:

- Lo que puede referenciar una variable
- Los métodos que pueden ser invocados  (los disponibles en las instancias de la clase del tipo estático)

```java
class Profesor extends Persona{
    public String impartirClase(){
        // Este método no lo tiene Persona ni ninguna de sus superclases
        return ("Impartiendo clase");
    }
}

Persona p = new Profesor();
p.impartirClase(); // Error de compilación. Las personasno tienen este método
p=new Object(); // Error de compilación. Las personasno tienen este método
```

Un **casts** es cuando se le indica al compilador que considere, temporalmente, que el tipo de la variable es otro:

- Solo para la instrucción en la que aparece y con limitaciones.

Existen los siguientes tipos:

- **Downcasting:**
  - Se indica al compilador que considere, temporalmente, que el tipo de la variable es una subclase del tipo con que se declaró.
  - Permite invocar métodos que sí existen en el tipo del cast pero no están en el tipo estático de la variable.
- **Upcasting:**
  - Se indica que al compilador que considere,  temporalmente, que el tipo de la variable es superclase del tipo con el que se declaró
  - Normalmente es innecesario y redundante

```java
Persona p = new Profesor();	// El objeto es un profesor
p.impartirClase();	// Error de compilación. Las personas no tienen este método
Profesor prof = p; // Error de compilación. Una Persona no es, en general, Profesor

((Profesor)p).impartirClase();
Profesor profe = (Profesor) p;

profe.hablar();	// "Hablo como un profesor"

// Upcast innecesario y sin efectos
((Persona) profe).hablar();
Persona p2 = profe;	// "Hablo como un profesor"
profe.hablar(); // "Hablo como un profesor"

// Errores en tiempo de ejecución

Persona p = new Persona();
Profesor profe = (Profesor) p; // Error
profe = ((Profesor) new Persona()); // Error
((Profesor) p).impartirClase();
((Profesor) ((Object) new Profesor())).impartirClase(); // OK
```

![Captura de pantalla de 2021-06-24 17-07-33](https://github.com/danieeeld2/DGIIM/blob/master/Segundo/2%20Cuatrimestre/PDOO/.img/Captura%20de%20pantalla%20de%202021-06-24%2017-07-33.png)

![Captura de pantalla de 2021-06-24 17-07-38](https://github.com/danieeeld2/DGIIM/blob/master/Segundo/2%20Cuatrimestre/PDOO/.img/Captura%20de%20pantalla%20de%202021-06-24%2017-07-38.png)

Con la ligadura dinámica, **siempre se comienza buscando el código asociado al método invocado en la clase que coincide con el tipo dinámico de la referencia**. Si no se encuentra, se busca en la clase padre y así sucesivamente:

```ruby
class Padre
    def interno
        puts "Interno padre"
    end
    def metodo
        puts "Voy a actuar: "
        interno
    end
end
class Hija < Padre
    def interno
        puts "Interno hijo"
    end
end
Padre.new.metodo # Voy a actuar: Interno padre
Hija.new.metodo  # Voy a actuar: Interno hijo    
```

### <u>Herencia en el Ámbito de Clase</u>

En Java:

- No permite la redefinición de métodos de clase al mismo nivel que de instancia.
- Aunque pueden existir métodos de clase con el mismo nombre en una jerarquía de clases, no se obtienen los mismos resultados que a nivel de instancia.

```java
class Padre{
	public static final int DECLASE = 1;
    public static int getDECLASE(){return DECLASE;}
}

class Hija extends Padre{
    public static final int DECLASE = 2; // Variable shadowing
    /*Shadowing refers to the practice in Java programming of using two variables 
    with the same name within scopes that overlap. When you do that, the variable with 
    the higher-level scope is hidden because the variable with lower-level scope 
    overrides it. The higher-level variable is then “shadowed.”*/
}

class Nieta extends Hija{
    public static int getDECLASE(){ // No es una redefinición
        return DECLASE;
    }
}

System.out.println(Padre.DECLEASE);			// 1
System.out.println(Hija.DECLEASE);			// 2
System.out.println(Nieta.DECLASE);			// 2
System.out.println(Padre.getDECLEASE());	// 1
System.out.println(Hija.getDECLEASE());		// 1
System.out.println(Nieta.getDECLEASE());	// 2
    
```

En Ruby:

- Las clases son **first class citizens** y en el ámbito de clase todo funciona como es de esperar:

```ruby
class Padre
    @atributo_clase1  = 1
    @atributo_clase2  = 2
    @@atributo_clase3 = 5
    
    def self.salida
        puts @atributo_clase1+1
        puts @atributo_clase2+1 unless @atributo_clase2.nil?
        puts @@atributo_clase3+1
    end
    def self.salida2
        salida
    end
end

Padre.salida # 2 3 6

class Hija < Padre
    @atributo_clase1  = 3
    @@atributo_clase3 = 7
    
    def self.salida2
        super
        puts @atributo_clase1+1
    end
end

Padre.salida   # 2 3 8
Hija.salida    # 4 8
Padre.salida2  # 2 3 8
Hija.salida2   # 4 8 4
```

### <u>Herencia Múltiple</u>

La **herencia múltiple** se produce cuando una clase es descendiente de más de una superclase. 

Suele tener problemas como:

- Colisión de nombres de métodos y/o atributos.

- Problema del diamante.

  ![Captura de pantalla de 2021-06-24 18-47-00](https://github.com/danieeeld2/DGIIM/blob/master/Segundo/2%20Cuatrimestre/PDOO/.img/Captura%20de%20pantalla%20de%202021-06-24%2018-47-00.png)

![Captura de pantalla de 2021-06-24 18-48-40](https://github.com/danieeeld2/DGIIM/blob/master/Segundo/2%20Cuatrimestre/PDOO/.img/Captura%20de%20pantalla%20de%202021-06-24%2018-48-40.png)

![Captura de pantalla de 2021-06-24 18-48-47](https://github.com/danieeeld2/DGIIM/blob/master/Segundo/2%20Cuatrimestre/PDOO/.img/Captura%20de%20pantalla%20de%202021-06-24%2018-48-47.png)

![Captura de pantalla de 2021-06-24 18-50-01](https://github.com/danieeeld2/DGIIM/blob/master/Segundo/2%20Cuatrimestre/PDOO/.img/Captura%20de%20pantalla%20de%202021-06-24%2018-50-01.png)

![Captura de pantalla de 2021-06-24 18-50-15](https://github.com/danieeeld2/DGIIM/blob/master/Segundo/2%20Cuatrimestre/PDOO/.img/Captura%20de%20pantalla%20de%202021-06-24%2018-50-15.png)

Soluciones:

- **Composición**: Sustituir una o varias relaciones de herencia por composición.

```java
class Estanteria {...}
class Reloj {...}
class RelojEstanteria extends Estanteria{
    private Reloj reloj;
    RelojEstanteria(){
        super();
        reloj = new Reloj();
    }
    // Los métodos de Estantería se heradan
    void setHora(Hora h){	// Los métodos de Reloj se definen
        reloj.setHora(h);	// se implementan reenviando el mensaje al atributo
    }
}
```

- **Interfaces  Java:** Se pueden realizar varias interfaces Java y heredar de una superclase.

```java
class Estanteria {...}
interface Reloj {public void setHora(Hora h); public Hora getHora();}
class RelojEstanteria extends Estanteria implements Reloj{
    RelojEstanteria(){
        super();
    }
    // Los métodos de Estantería se heredan
    // Se implementan los métodos de la interfaz
    public void setHora(Hora h){...}
    public Hora getHora(){...}
}
```

- **Mixins de Ruby: ** Permiten incluir código proveniente de varios módulos como parte de una clase.

```ruby
module Volador
    def volador
        puts "Volando"
    end
end

module Nadador
    def nadar
        puts "Nadando"
    end
end

class Ejemplo
    def metodo
        puts "Método propio"
    end
    include Volador # Añadimos todo el módulo
    include Nadador # Añadimos todo el módulo
end

e=Ejemplo.new
e.metodo
e.volar
e.nadar
```

### <u>Copia de Objetos</u>

Una operación muy habitual en un programa es esta:

```java
copia=original;
// ¿Qué realiza dicha operación?
// Si modifico original, ¿se ve afectada copia? ¿y  si modifico copia?
```

Aparecen dos coceptos:

- **Profundidad de la copia: ** Hasta que nivel se van a realizr copias de estado en vez de identidad.
- **Inmutabilidad de los objetos: **Un objeto es inmutable si no dispone de métodos que modifiquen su estado (*Hay que tener cuidado con los objetos que referencian a otros si estos no son inmutables*).
- 

