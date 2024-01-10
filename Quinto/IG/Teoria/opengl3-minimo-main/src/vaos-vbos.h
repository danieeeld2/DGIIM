#ifndef VBOS_VAOS_H
#define VBOS_VAOS_H

#include <vector>
#include "glincludes.h"

#define CError()  assert( glGetError() == GL_NO_ERROR );
// --------------------------------------------------------------------------------------------

// Guarda los datos y metadatos de un VBO con una tabla de atributos de vértice
//
class DescrVBOAtribs
{
   private: 

   // metadatos y datos del buffer

   GLuint       buffer   = 0 ; // nombre o id del buffer en la GPU (0 antes de crearlo, >0 después)
   GLuint       index    = 0 ; // índice de atributo (<num_attrs)
   GLenum       type     = 0 ; // tipo de los valores (GL_FLOAT o GL_DOUBLE)
   GLint        size     = 0 ; // numero de valores por tupla (usualmente 2,3, o 4)
   GLsizei      count    = 0 ; // número de tuplas en la tabla (>0)
   GLsizeiptr   tot_size = 0 ; // tamaño completo de la tabla en bytes (=count*size*sizeof(c-type))
   
   const void * data     = nullptr ; // datos originales en la CPU (null antes de saberlos, no null después)
   void *       own_data = nullptr ; // si no nulo, tiene copia de los datos (propiedad de este objeto).
   
   // Hace una copia de los datos de la tabla en una zona de memoria propiedad de esta 
   // instancia (copia los datos originales en 'data' en 'own_data', solo una vez).
   // 
   void copiarDatos() ; 

   friend class DescrVAO ;

   public:

   // constructores, asumen offset y stride a 0 (AOS con una tabla por VBO)

   // impide usar constructor por defecto (sin parámetros)
   DescrVBOAtribs() = delete ; 

   // Crea un descriptor de VBO de atributos, a partir de sus metadatos (type, size, count) y un 
   // puntero a los datos (p_data)
   // 
   // @param p_index (unsigned) índice del atributo 
   // @param p_type  (GLenum)   tipo de los datos (GL_FLOAT o GL_DOUBLE)
   // @param p_size  (unsigned) tamaño de las tuplas o vectores (2, 3 o 4)
   // @param p_count (unsigned) número de tuplas (>0)
   // @param p_data  (void *)   puntero al array de tuplas (no nulo)   
   // 
   DescrVBOAtribs( const unsigned p_index, const GLenum p_type, const unsigned p_size, 
               const unsigned long p_count, const void *p_data ); 

   // Crea un descriptor de VBO de atributos, a partir de una tabla de coordenadas,
   // almacenada como un vector (std::vector) de 'vec3'.
   // 
   // @param p_index (unsigned)     índice del atributo 
   // @param p_type  (vector<vec3>) vector con los datos (solo se lee)
   // 
   DescrVBOAtribs( const unsigned p_index, const std::vector<glm::vec3> & src_vec );

   // Crea un descriptor de VBO de atributos, a partir de una tabla de coordenadas,
   // almacenada como un vector (std::vector) de 'vec2'.
   // 
   // @param p_index  (unsigned)     índice del atributo 
   // @param p_type   (vector<vec2>) vector con los datos (solo se lee)
   //
   DescrVBOAtribs( const unsigned p_index, const std::vector<glm::vec2> & src_vec );

   // Comprueba que los descriptores de la tabla de datos son correctos, aborta si no
   //
   void comprobar() const;



   // Crea el VBO en la GPU (solo se puede llamar una vez), deja el VBO habilitado en el 
   // índice de atributo, requiere que 'buffer' esté a cero (evita llamarlo 2 veces)
   // deja en buffer el identificador de VBO
   //
   void crearVBO() ; 

   // Devuelve true solo si el VBO ya ha sido creado en la GPU
   inline bool creado() const { return buffer != 0; } 

   // Devuelve el valor de 'count' para este descriptor
   inline GLsizei leerCount() { return count ; }

   // Devuelve el índice de este VBO
   inline GLuint leerIndex() const { return index; }

   // Devuelve el número de vértices
   inline GLuint getCount() const { return count; }

   // Libera la memoria ocupada por el VBO, tanto en la memoria de la aplicación, como 
   // en la memoria del buffer en la GPU (si ya se ha creado)
   //
   ~DescrVBOAtribs();  
} ;

// --------------------------------------------------------------------------------------------

// Guarda los datos y metadatos de un VBO de índices
//
class DescrVBOInds
{
   private:

   // metadatos y datos del buffer
   GLuint       buffer   = 0 ; // nombre o id del buffer en la GPU (0 antes de crearlo, >0 después)
   GLenum       type     = 0 ; // tipo de los valores (GL_UNSIGNED_BYTE, GL_UNSIGNED_SHORT, GL_UNSIGNED_INT)
   GLsizei      count    = 0 ; // número de índices en la tabla (>0)
   GLsizeiptr   tot_size = 0 ; // tamaño completo de la tabla en bytes (=count*sizeof(c-type))
   
   const void * indices     = nullptr ; // datos originales en la CPU (null antes de saberlos, no null después)
   void *       own_indices = nullptr ; // si no nulo, tiene copia de los datos (propiedad de este objeto).
   
   // Inicializa 'own_indices' con una copia de los datos en 'indices', y apunta 
   // 'indices' a 'own_indices'
   //
   void copyIndices() ; 

   public:

   // impide usar constructor por defecto (sin parámetros)
   DescrVBOInds() = delete ; 

   // Crea un descriptor de VBO de índices, a partir de sus metadatos (type, count) y un 
   // puntero a los datos (p_indices)
   // 
   // @param p_type  (GLEnum)   tipo de los datos (GL_UNSIGNED_BYTE, GL_UNSIGNED_SHORT o GL_UNSIGNED_INT)
   // @param p_count (unsigned) número de índices (>0)
   // @param p_data  (void *)   puntero al array de índices (no nulo, solo se lee)   
   //
   DescrVBOInds( const GLenum p_type, const GLsizei p_count, const void * p_data ); 

   // Crea un descriptor de VBO de índices, a partir de una tabla de tuplas con 3 enteros
   // (se puede usar típicamente para tablas de triángulos)
   // 
   // @param src_vec  (vector<uvec3> &)  tabla de tuplas de 3 enteros (triángulos)
   //
   DescrVBOInds( const std::vector<unsigned> & src_vec );
   
   
   // Crea un descriptor de VBO de índices, a partir de una tabla de tuplas con 3 enteros
   // (se puede usará típicamente para tablas de triángulos)
   // 
   // @param src_vec  (vector<uvec3> &)  tabla de tuplas de 3 enteros (triángulos)
   // 
   DescrVBOInds( const std::vector<glm::uvec3> & src_vec );


   // Comprueba que los metadatos son correctos, aborta si no
   void comprobar() const ;

   // Devuelve true solo si el VBO ya ha sido creado en la GPU
   inline bool creado() const { return buffer != 0; }

   // Devuelve el valor de 'count' para este descriptor
   inline GLsizei leerCount() { return count ; }

   // Devuelve el valor de 'type' para este descriptor
   inline GLenum leerType() { return type ; }

   // Crear y activar el VBO de índices, es decir:
   //   1. Crea el VBO y envía la tabla de índices a la GPU (únicamente la primera vez)
   //   2. Hace 'bind' de la tabla en el 'target' GL_ELEMENT_ARRAY_BUFFER
   //
   void crearVBO( );

   // destruye un VAO (libera memoria dinámica de la aplic. y elimina VAO en la GPU)
   ~DescrVBOInds();

} ;

// -----------------------------------------------------------------------------------------------------

// Guarda los datos y metadatos de los VBOs que forman un VAO
//
class DescrVAO
{
   private:

   // nombre o identificador del VAO en la GPU (0 si no creado en GPU)
   GLuint array = 0 ; 

   // número de tablas de atributos que tiene el VAO (incluyendo las posicione)
   GLuint num_atribs = 0;

   // número de vértices en la tabla de posiciones de vértices 
   GLsizei count = 0 ;

   // número de índices en la tabla de índices (si hay índices, en otro caso 0)
   GLsizei idxs_count = 0 ;

   // si hay índices, tiene el tipo de los índices 
   GLenum idxs_type ;

   // si la secuencia es indexada, VBO de attrs, en otro caso
   DescrVBOInds * dvbo_indices   = nullptr ; 
   
   // vector de punteros a los descriptores de VBOs de atributos
   std::vector<DescrVBOAtribs *> dvbo_atributo ;

   // array que indica si cada tabla de atributos está habilitada o deshabilitada
   std::vector<bool> atrib_habilitado ;

   void check( const unsigned index ); // comprueba precondiciones antes de añadir tabla de atribs

   public:    

   // impide usar constructor por defecto (sin parámetros)
   DescrVAO() = delete ; 

   // Crea un descriptor de VAO, dando un descriptor del VBO de posiciones de vértices
   //
   // @param p_num_atribs     (unsigned)        número de atributos que puede tener este VAO 
   // @param dvbo_posiciones  (DescrVBOAttrib *) puntero al descriptor del VBO de atributos (no nulo)
   //
   DescrVAO( const unsigned p_num_atribs, DescrVBOAtribs * vbo_posiciones ) ;
  
   // Crea el identificador del VAO (array), crea los identificadores de los VBOs asociados, 
   // transfiere los datos de todas las tablas a la GPU.
   //
   void crearVAO();

   // Añade un descriptor de VBO de atributos 
   //
   // @param index (unsigned) índice del atributo (no puede ser 0, la tabla de posiciones se da en el constructor)
   // @param vbo_atributo (DescrVBOAtribs *) puntero al descriptor (no puede ser nulo)
   //
   void agregar( DescrVBOAtribs * vbo_atributo );

   // Añade el descriptor de índices, por tanto el VAO pasa a ser indexado.
   // @param vbo_indices (DescrVBOInds *) puntero al descriptor del VBO de índices (no puede ser nulo)
   //
   void agregar( DescrVBOInds * vbo_indices );

   // habilita/deshabilita una tabla de atributos (index no puede ser 0)
   void habilitarAtrib( const unsigned index, const bool habilitar );

   // ....
   void draw( const GLenum mode ) ;

   // ....
   ~DescrVAO();
} ;




#endif

