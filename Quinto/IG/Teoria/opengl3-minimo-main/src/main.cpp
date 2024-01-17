// Ejemplo mínimo de código OpenGL, usa OpenGL 3.3 + GLSL 3.3 + GLFW



// includes de la librería estándard de C++
#include <cassert>   // 'assert' (enforce preconditions)
#include <cstring>   // 'strlen' (to compile shaders)
#include <iostream>  // 'cout' and such
#include <iomanip>   // set precision and such
#include <vector>    // 'std::vector' types

// incluir cabeceras de OpenGL y GLM
#include "glincludes.h"

// incluir cabeceras auxiliares para shaders, vaos y vbos.
#include "cauce.h"      // clase 'Cauce'
#include "vaos-vbos.h"  // clases 'DescrVAO', 'DescrVBOAtribs' y 'DescrVBOInds' 

// ---------------------------------------------------------------------------------------------
// Constantes y variables globales

// constexpr GLuint
//     ind_atrib_posiciones = 0,      // índice del atributo de vértice con su posiciones (debe ser el índice 0, siempre)
//     ind_atrib_colors    = 1,      // índice del atributo de vértice con su color RGB
//     num_atribs           = 2 ;     // número de atributos que gestionan los shaders
bool
    redibujar_ventana   = true ,   // puesto a true por los gestores de eventos cuando cambia el modelo y hay que regenerar la vista
    terminar_programa   = false ;  // puesto a true en los gestores de eventos cuando hay que terminar el programa
GLFWwindow *
    ventana_glfw        = nullptr; // puntero a la ventana GLFW
int
    ancho_actual        = 1024 ,    // ancho actual del framebuffer, en pixels
    alto_actual         = 1024 ;    // alto actual del framebuffer, en pixels
DescrVAO
    * vao_ind          = nullptr , // identificador de VAO (vertex array object) para secuencia indexada
    * vao_no_ind       = nullptr , // identificador de VAO para secuencia de vértices no indexada
    * vao_glm          = nullptr ; // identificador de VAO para secuencia de vértices guardada en vectors de vec3
Cauce 
    * cauce            = nullptr ; // puntero al objeto de la clase 'Cauce' en uso.


// ---------------------------------------------------------------------------------------------
// función que se encarga de visualizar un triángulo relleno en modo diferido,
// no indexado, usando la clase 'DescrVAO' (declarada en 'vaos-vbos.h')
// el triángulo se dibuja en primer lugar relleno con colores, y luego las aristas en negro


void DibujarTriangulo_NoInd( )
{
    assert( glGetError() == GL_NO_ERROR );

    // la primera vez, crear e inicializar el VAO
    if ( vao_no_ind == nullptr )
    {
        // número de vértices que se van a dibujar
        constexpr unsigned num_verts = 3 ;

        // tablas de posiciones y colores de vértices (posiciones en 2D, con Z=0)
        const GLfloat
            posiciones[ num_verts*2 ] = {  -0.8, -0.8,      +0.8, -0.8,     0.0, 0.8      },
            colores   [ num_verts*3 ] = {  1.0, 0.0, 0.0,   0.0, 1.0, 0.0,  0.0, 0.0, 1.0 };

        // Crear VAO con posiciones, colores e indices
        vao_no_ind = new DescrVAO( cauce->num_atribs, new DescrVBOAtribs( cauce->ind_atrib_posiciones, GL_FLOAT, 2, num_verts, posiciones ));
        vao_no_ind->agregar( new DescrVBOAtribs( cauce->ind_atrib_colores, GL_FLOAT, 3, num_verts, colores ));    
    }
    
    assert( glGetError() == GL_NO_ERROR );

    // duibujar relleno usando los colores del VAO
    glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
    cauce->fijarUsarColorPlano( false );
    vao_no_ind->habilitarAtrib( cauce->ind_atrib_colores, true );
    vao_no_ind->draw( GL_TRIANGLES );

    assert( glGetError() == GL_NO_ERROR );

    // dibujar las líneas usando color negro
    glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
    cauce->fijarUsarColorPlano( true );
    cauce->fijarColor( { 0.0, 0.0, 0.0 });
    vao_no_ind->habilitarAtrib( cauce->ind_atrib_colores, false );
    vao_no_ind->draw( GL_TRIANGLES );

    assert( glGetError() == GL_NO_ERROR );
}

// ---------------------------------------------------------------------------------------------
// función que se encarga de visualizar un triángulo  en modo diferido,
// indexado, usando la clase  'DescrVAO' (declarada en vaos-vbos.h)
// el triángulo se dibuja en primer lugar relleno con colores, y luego las aristas en negro

void DibujarTriangulo_Ind( )
{
    assert( glGetError() == GL_NO_ERROR );

    if ( vao_ind == nullptr )
    {
         // número de vértices e índices que se van a dibujar
        constexpr unsigned num_verts = 3, num_inds  = 3 ;

        // tablas de posiciones y colores de vértices (posiciones en 2D, con Z=0)
        const GLfloat
            posiciones[ num_verts*2 ] = {  -0.4, -0.4,      +0.4, -0.4,     0.0, +0.4      },
            colores   [ num_verts*3 ] = {  1.0, 0.0, 0.0,   0.0, 1.0, 0.0,  0.0, 0.0, 1.0 } ;
        const GLuint
            indices   [ num_inds    ] = { 0, 1, 2 };

        vao_ind = new DescrVAO( cauce->num_atribs, new DescrVBOAtribs( cauce->ind_atrib_posiciones, GL_FLOAT, 2, num_verts, posiciones) );
        vao_ind->agregar( new DescrVBOAtribs( cauce->ind_atrib_colores, GL_FLOAT, 3, num_verts, colores) ) ;
        vao_ind->agregar( new DescrVBOInds( GL_UNSIGNED_INT, num_inds, indices ));
    }
   
    assert( glGetError() == GL_NO_ERROR );
    
    glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
    cauce->fijarUsarColorPlano( false );
    vao_ind->habilitarAtrib( cauce->ind_atrib_colores, true );
    vao_ind->draw( GL_TRIANGLES );

    assert( glGetError() == GL_NO_ERROR );
   
    glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
    cauce->fijarColor( { 0.0, 0.0, 0.0 });
    vao_ind->habilitarAtrib( cauce->ind_atrib_colores, false );
    vao_ind->draw( GL_TRIANGLES );

    assert( glGetError() == GL_NO_ERROR );
}

// ---------------------------------------------------------------------------------------------
// función que se encarga de visualizar un triángulo relleno en modo diferido,
// usando vectores con entradas de tipos GLM (vec2, vec3, uvec3)
// el triángulo se dibuja en primer lugar relleno con colores, y luego las aristas en negro

void DibujarTriangulo_glm( )
{    
    using namespace std ;
    using namespace glm ;

    assert( glGetError() == GL_NO_ERROR );

    if ( vao_glm == nullptr )
    {

        // tablas de posiciones y colores de vértices (posiciones en 2D, con Z=0)
        const vector<vec2>   posiciones = {  {-0.4, -0.4},     {+0.42, -0.47},   {0.1, +0.37}    };
        const vector<vec3>   colores    = {  {1.0, 1.0, 0.0},  {0.0, 1.0, 1.0},  {1.0, 0.0, 1.0} };
        const vector<uvec3>  indices    = {  { 0, 1, 2 }};   // (un único triángulo)      

        vao_glm = new DescrVAO( cauce->num_atribs, new DescrVBOAtribs( cauce->ind_atrib_posiciones, posiciones ));
        vao_glm->agregar( new DescrVBOAtribs( cauce->ind_atrib_colores, colores )) ;
        vao_glm->agregar( new DescrVBOInds( indices ) );

        assert( glGetError() == GL_NO_ERROR );
    }
   
    assert( glGetError() == GL_NO_ERROR );
    
    glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
    cauce->fijarUsarColorPlano( false );
    vao_glm->habilitarAtrib( cauce->ind_atrib_colores, true );
    vao_glm->draw( GL_TRIANGLES );

    assert( glGetError() == GL_NO_ERROR );
   
    glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
    cauce->fijarColor( { 0.0, 0.0, 0.0 });
    vao_glm->habilitarAtrib( cauce->ind_atrib_colores, false );
    vao_glm->draw( GL_TRIANGLES );

    assert( glGetError() == GL_NO_ERROR );
}

// ---------------------------------------------------------------------------------------------

void DibujarFigura1(unsigned int n){
    assert(n>2);
    assert( glGetError() == GL_NO_ERROR );
    std::vector<glm::vec3> vertices;
    std::vector<glm::uvec3> indices;
    vertices.push_back(glm::vec3(0.0,0.0,0.0));
    for(int i = 0; i < n; i++){
        vertices.push_back(glm::vec3(cos(2*M_PI*i/n),sin(2*M_PI*i/n),0.0));
    }
    for(int i = 0; i < n; i++){
        indices.push_back(glm::uvec3(0,i+1,(i+1)%n+1));
    }
    if(vao_glm == nullptr){
        vao_glm = new DescrVAO(cauce->num_atribs, new DescrVBOAtribs(cauce->ind_atrib_posiciones, vertices));
        vao_glm->agregar(new DescrVBOInds(indices));
        assert( glGetError() == GL_NO_ERROR );
    }
    glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
    cauce->fijarUsarColorPlano( true );
    // Esta funcion llama a glVertexAttrib3f
    cauce->fijarColor( { 1.0, 0.0, 1.0 });
    vao_glm->draw( GL_TRIANGLES );
    assert( glGetError() == GL_NO_ERROR );
}

// ---------------------------------------------------------------------------------------------

void DibujarFigura2(unsigned int n){
    assert(n>2);
    assert( glGetError() == GL_NO_ERROR );
    std::vector<glm::dvec2> vertices;
    for(int i=0; i<n; i++){
        vertices.push_back(glm::dvec2(cos(2*M_PI*i/n),sin(2*M_PI*i/n)));
    }
    if(vao_glm == nullptr){
        vao_glm = new DescrVAO(cauce->num_atribs, new DescrVBOAtribs(cauce->ind_atrib_posiciones, GL_DOUBLE, 2, vertices.size(), vertices.data()));
        assert( glGetError() == GL_NO_ERROR );
    }
    glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
    vao_glm->draw(GL_LINE_LOOP);
    assert( glGetError() == GL_NO_ERROR );
}

// ---------------------------------------------------------------------------------------------

void DibujarFigura3(unsigned int n){
    assert(n>2);
    assert( glGetError() == GL_NO_ERROR );
    cauce->fijarUsarColorPlano( true );
    cauce->fijarColor( { 1.0, 0.0, 1.0 });
    DibujarFigura1(n);
    cauce->fijarColor( { 0.0, 1.0, 1.0 });
    DibujarFigura2(n);
    assert( glGetError() == GL_NO_ERROR );
}

// ---------------------------------------------------------------------------------------------

void DibujarFigura4(unsigned int n){
    assert(n>2);
    assert( glGetError() == GL_NO_ERROR );
    std::vector<glm::vec3> vertices;
    std::vector<glm::uvec3> indices;
    vertices.push_back(glm::vec3(0.0,0.0,0.0));
    for(int i = 0; i < n; i++){
        vertices.push_back(glm::vec3(cos(2*M_PI*i/n),sin(2*M_PI*i/n),0.0));
    }
    for(int i = 0; i < n; i++){
        indices.push_back(glm::uvec3(0,i+1,(i+1)%n+1));
    }
    if(vao_glm == nullptr){
        vao_glm = new DescrVAO(cauce->num_atribs, new DescrVBOAtribs(cauce->ind_atrib_posiciones, vertices));
        vao_glm->agregar(new DescrVBOInds(indices));
        assert( glGetError() == GL_NO_ERROR );
    }
    glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
    cauce->fijarUsarColorPlano( true );
    cauce->fijarColor( { 1.0, 0.0, 1.0 });
    vao_glm->draw( GL_TRIANGLES );
    assert( glGetError() == GL_NO_ERROR );
    cauce->fijarColor( { 0.0, 1.0, 1.0 });
    vao_glm->draw(GL_LINE_LOOP);
    assert( glGetError() == GL_NO_ERROR );
}

// ---------------------------------------------------------------------------------------------

void DibujarFigura5(unsigned int n){
    assert(n>2);
    assert( glGetError() == GL_NO_ERROR );
    std::vector<glm::vec3> vertices;
    std::vector<glm::vec3> colores;
    std::vector<glm::uvec3> indices;
    vertices.push_back(glm::vec3(0.0,0.0,0.0));
    for(int i = 0; i < n; i++){
        vertices.push_back(glm::vec3(cos(2*M_PI*i/n),sin(2*M_PI*i/n),0.0));
    }
    for(int i = 0; i < n; i++){
        indices.push_back(glm::uvec3(0,i+1,(i+1)%n+1));
    }
    srand(time(NULL));
    for(int i = 0; i < n+1; i++){
        colores.push_back(glm::vec3((float)rand()/RAND_MAX,(float)rand()/RAND_MAX,(float)rand()/RAND_MAX));
    }
    if(vao_glm == nullptr){
        vao_glm = new DescrVAO(cauce->num_atribs, new DescrVBOAtribs(cauce->ind_atrib_posiciones, vertices));
        vao_glm->agregar(new DescrVBOAtribs(cauce->ind_atrib_colores, colores));
        vao_glm->agregar(new DescrVBOInds(indices));
        assert( glGetError() == GL_NO_ERROR );
    }
    glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
    // Llama a glUniform1i
    cauce->fijarUsarColorPlano( false );
    vao_glm->habilitarAtrib( cauce->ind_atrib_colores, true );
    vao_glm->draw( GL_TRIANGLES );
    assert( glGetError() == GL_NO_ERROR );
    vao_glm->habilitarAtrib( cauce->ind_atrib_colores, false );
    cauce->fijarUsarColorPlano( true );
    cauce->fijarColor( { 1.0, 0.0, 1.0 });
    vao_glm->draw(GL_LINE_LOOP);
    assert( glGetError() == GL_NO_ERROR );
}

// ---------------------------------------------------------------------------------------------

void fijarRegionVisible(const float x0, const float x1, 
                        const float y0, const float y1,
                        const float z0, const float z1)
{
    assert( glGetError() == GL_NO_ERROR );
    float sx = 2.0/(x1-x0), sy = 2.0/(y1-y0), sz = 2.0/(z1-z0);
    float cx = (x0+x1)/2, cy = (y0+y1)/2, cz = (z0+z1)/2;
    glm::mat4 mat = glm::mat4(sx, 0.0, 0.0, -1*cx*sx,
                              0.0, sy, 0.0, -1*cy*sy,
                              0.0, 0.0, sz, -1*cz*sz,
                              0.0, 0.0, 0.0, 1.0);
    // Llama a glUniformMatrix4fv
    cauce->fijarMatrizProyeccion(mat);
}

// ---------------------------------------------------------------------------------------------

struct AtributosVertices{
    glm::vec3 posicion;
    glm::vec3 color;
};

void DibujarFigura6(unsigned int n){
    assert(n>2);
    assert( glGetError() == GL_NO_ERROR );
    static GLuint array = 0;
    std::vector<AtributosVertices> vertices;
    std::vector<glm::uvec3> indices;
    vertices.push_back({glm::vec3(0.0,0.0,0.0),glm::vec3(0.0,0.0,0.0)});
    for(int i = 0; i < n; i++){
        vertices.push_back({glm::vec3(cos(2*M_PI*i/n),sin(2*M_PI*i/n),0.0),glm::vec3(0.0,0.0,0.0)});
    }
    for(int i = 0; i < n; i++){
        indices.push_back(glm::uvec3(0,i+1,(i+1)%n+1));
    }
    srand(time(NULL));
    for(int i = 0; i < n+1; i++){
        vertices[i].color = glm::vec3((float)rand()/RAND_MAX,(float)rand()/RAND_MAX,(float)rand()/RAND_MAX);
    }
    if(array == 0){
        // Creamos VAO
        glGenVertexArrays(1, &array);
        glBindVertexArray(array);
        // Creamos VBO
        GLuint buffer;
        glGenBuffers(1, &buffer);
        glBindBuffer(GL_ARRAY_BUFFER, buffer);
        glBufferData(GL_ARRAY_BUFFER, vertices.size()*sizeof(AtributosVertices), vertices.data(), GL_STATIC_DRAW);
        // Especificar formato de las posiciones
        glVertexAttribPointer(cauce->ind_atrib_posiciones, 3, GL_FLOAT, GL_FALSE, sizeof(AtributosVertices), (void*)0);
        glEnableVertexAttribArray(cauce->ind_atrib_posiciones);
        // Especificar formato de los colores
        glVertexAttribPointer(cauce->ind_atrib_colores, 3, GL_FLOAT, GL_FALSE, sizeof(AtributosVertices), (void*)(3*sizeof(float)));
        // Hacemos VBO indice
        DescrVBOInds *vbo_ind = new DescrVBOInds(indices);
        vbo_ind->crearVBO();
        assert( glGetError() == GL_NO_ERROR );
    }
    // Dibujamos relleno
    glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
    cauce->fijarUsarColorPlano( false );
    glEnableVertexAttribArray(cauce->ind_atrib_colores);
    glDrawElements(GL_TRIANGLES, indices.size()*3, GL_UNSIGNED_INT, 0);
    // Dibujamos aristas
    glDisableVertexAttribArray(cauce->ind_atrib_colores);
    cauce->fijarUsarColorPlano( true );
    cauce->fijarColor( { 0.0, 0.0, 0.0 });
    glDrawArrays(GL_LINE_LOOP, 1, n);
}

// ---------------------------------------------------------------------------------------------

void gancho(){
    std::vector<glm::vec3> vertices = {glm::vec3(0.0,0.0,0.0), glm::vec3(0.1,0.0,0.0),
                                        glm::vec3(0.1,0.1,0.0), glm::vec3(0.0,0.1,0.0), glm::vec3(0.0,0.2,0.0)};
    if(vao_glm == nullptr){
        vao_glm = new DescrVAO(cauce->num_atribs, new DescrVBOAtribs(cauce->ind_atrib_posiciones, vertices));
        assert( glGetError() == GL_NO_ERROR );
    }
    glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
    cauce->fijarUsarColorPlano( true );
    vao_glm->draw(GL_LINE_STRIP);
    assert( glGetError() == GL_NO_ERROR );
}

// ---------------------------------------------------------------------------------------------

void gancho_x4(){
    cauce->resetMM();
    gancho();
    cauce->compMM(glm::translate(glm::vec3(0.0,0.2,0.0)));
    cauce->compMM(glm::rotate(glm::radians(90.0f),glm::vec3(0.0,0.0,1.0)));
    gancho();
    cauce->resetMM();
    cauce->compMM(glm::translate(glm::vec3(-0.2,0.2,0.0)));
    cauce->compMM(glm::rotate(glm::radians(180.0f),glm::vec3(0.0,0.0,1.0)));
    gancho();
    cauce->resetMM();
    cauce->compMM(glm::translate(glm::vec3(-0.2,0.0,0.0)));
    cauce->compMM(glm::rotate(glm::radians(270.0f),glm::vec3(0.0,0.0,1.0)));
    gancho();
    cauce->resetMM();    
}

// ---------------------------------------------------------------------------------------------

void gancho_2p(glm::vec3 p0, glm::vec3 p1){
    glm::vec3 v = p1-p0;
    float l = glm::length(v);
    float angunlo = std::acos(v.y/l);
    if(v.y < 0.0){
        angunlo = -1*angunlo;
    }
    float escala = l/2.0f;
    cauce->resetMM();
    cauce->compMM(glm::translate(p0));
    angunlo = angunlo*180.0f/M_PI;
    cauce->compMM(glm::rotate(angunlo,glm::vec3(0.0,0.0,1.0)));
    cauce->compMM(glm::scale(glm::vec3(escala,escala,0.0)));
    gancho();
    cauce->resetMM();    
}

// ---------------------------------------------------------------------------------------------

void gancho_2p_b(glm::vec3 p0, glm::vec3 p1){  
    glm::vec3 y_prima = (p1-p0)/glm::vec3(2.0,2.0,2.0);
    glm::vec3 x_prima = glm::vec3(y_prima.y,-y_prima.x,y_prima.z);
    x_prima = glm::normalize(x_prima);
    glm::mat4 mat_trans = glm::mat4(1.0);
    mat_trans[0][0] = x_prima.x;
    mat_trans[0][1] = y_prima.x;
    mat_trans[1][0] = x_prima.y;
    mat_trans[1][1] = y_prima.y;
    mat_trans = glm::translate(p0)*mat_trans;
    cauce->resetMM();
    cauce->compMM(mat_trans);
    gancho();
    cauce->resetMM();
}

// ---------------------------------------------------------------------------------------------

#include <cmath>

void generarGanchos(const unsigned int n){
    const double radio = 0.3f; // Radio del círculo
    const double angulo_base = 2*M_PI/n; // Ángulo entre ganchos

    for(int i=0; i<n; i++){
        double angulo = (angulo_base*i)+(180.0/M_PI);
        double angulo_sig = angulo_base*(i+1)+(180.0/M_PI);
        glm::vec3 p0 = glm::vec3(radio*cos(angulo),radio*sin(angulo),0.0);
        glm::vec3 p1 = glm::vec3(radio*cos(angulo_sig),radio*sin(angulo_sig),0.0);
        gancho_2p(p0,p1);
    }
}

// ---------------------------------------------------------------------------------------------

void FiguraSimple(){
    assert( glGetError() == GL_NO_ERROR );
    std::vector<glm::vec3> vertices_cuadrado = {glm::vec3(-0.5,-0.5,0.0), glm::vec3(0.5,-0.5,0.0),
                                                glm::vec3(0.5,0.5,0.0), glm::vec3(-0.5,0.5,0.0)};
    std::vector<glm::vec3> vertices_triangulo = {glm::vec3(-0.4,-0.4,0.0), glm::vec3(-0.2,-0.4,0.0),
                                                glm::vec3(-0.3,0.1,0.0)};
    std::vector<glm::uvec3> indices_cuadrado = {glm::uvec3(0,1,2), glm::uvec3(0,2,3)};
    std::vector<glm::uvec3> indices_triangulo = {glm::uvec3(0,1,2)};
    DescrVAO *vao_cuadrados = nullptr;
    DescrVAO *vao_triangulos = nullptr;
    if(vao_cuadrados == nullptr){
        vao_cuadrados = new DescrVAO(cauce->num_atribs, new DescrVBOAtribs(cauce->ind_atrib_posiciones, vertices_cuadrado));
        vao_cuadrados->agregar(new DescrVBOInds(indices_cuadrado));
        assert( glGetError() == GL_NO_ERROR );
    }
    if(vao_triangulos == nullptr){
        vao_triangulos = new DescrVAO(cauce->num_atribs, new DescrVBOAtribs(cauce->ind_atrib_posiciones, vertices_triangulo));
        vao_triangulos->agregar(new DescrVBOInds(indices_triangulo));
        assert( glGetError() == GL_NO_ERROR );
    }
    glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
    cauce->fijarUsarColorPlano( true );
    cauce->fijarColor( { 0.3, 0.7, 0.9});
    vao_cuadrados->draw(GL_TRIANGLES);
    assert( glGetError() == GL_NO_ERROR );
    cauce->fijarColor( { 1.0, 1.0, 1.0});
    vao_triangulos->draw(GL_TRIANGLES);
    assert( glGetError() == GL_NO_ERROR );
}

// ---------------------------------------------------------------------------------------------

void figuraCompleja(){
    assert( glGetError() == GL_NO_ERROR );
    FiguraSimple();
    cauce->pushMM();
        cauce->compMM(glm::translate(glm::vec3(1.5,0.5,0.0)));
        cauce->compMM(glm::scale(glm::vec3(sqrt(2.0),sqrt(2.0),0.0)));
        float angulo = 3*M_PI/4.0f;
        cauce->compMM(glm::rotate(angulo,glm::vec3(0.0,0.0,1.0)));
        FiguraSimple();
    cauce->popMM();
    cauce->pushMM();
        cauce->compMM(glm::translate(glm::vec3(3.5,0.0,0.0)));
        cauce->compMM(glm::scale(glm::vec3(2.0,-1.0,0.0)));
        FiguraSimple();
    cauce->popMM();
}

// ---------------------------------------------------------------------------------------------

void Tronco(){
    assert( glGetError() == GL_NO_ERROR );
    std::vector<glm::vec3> vertices = {glm::vec3(0.0,0.0,0.0), glm::vec3(1.0,0.0,0.0), glm::vec3(1.0,1.0,0.0),
                                        glm::vec3(2.0,2.0,0.0), glm::vec3(1.5,2.5,0.0), glm::vec3(0.5,1.5,0.0),
                                        glm::vec3(0.0,3.0,0.0), glm::vec3(-0.5,3.0,0.0), glm::vec3(0.0,1.5,0.0)};
    std::vector<glm::uvec3> indices_relleno = {glm::uvec3(0,1,2),glm::uvec3(0,2,8),glm::uvec3(2,5,8),
                                                glm::uvec3(2,3,4),glm::uvec3(2,4,5),glm::uvec3(5,6,8),glm::uvec3(6,7,8)};
    std::vector<glm::uvec2> indices_aristas = {glm::uvec2(0,8),glm::uvec2(8,7),glm::uvec2(6,5),
                                                glm::uvec2(5,4),glm::uvec2(3,2),glm::uvec2(2,1)};
    DescrVAO *vao_relleno = nullptr;
    DescrVAO *vao_aristas = nullptr;
    if(vao_relleno == nullptr){
        vao_relleno = new DescrVAO(cauce->num_atribs, new DescrVBOAtribs(cauce->ind_atrib_posiciones, vertices));
        vao_relleno->agregar(new DescrVBOInds(indices_relleno));
        assert( glGetError() == GL_NO_ERROR );
    }
    if(vao_aristas == nullptr){
        vao_aristas = new DescrVAO(cauce->num_atribs, new DescrVBOAtribs(cauce->ind_atrib_posiciones, vertices));
        vao_aristas->agregar(new DescrVBOInds(GL_UNSIGNED_INT, indices_aristas.size()*2, indices_aristas.data()));
        assert( glGetError() == GL_NO_ERROR );
    }

    glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
    cauce->fijarUsarColorPlano( true );
    cauce->fijarColor( { 0.5, 0.8, 1.0});
    vao_relleno->draw(GL_TRIANGLES);
    assert( glGetError() == GL_NO_ERROR );
    cauce->fijarColor( { 0.0, 0.0, 1.0});
    vao_aristas->draw(GL_LINES);
    assert( glGetError() == GL_NO_ERROR );
}

// ---------------------------------------------------------------------------------------------

void Arbol(const unsigned int n){
    assert( glGetError() == GL_NO_ERROR );
    assert(n>0);
    Tronco();
    if(n>1){
        cauce->pushMM();
            cauce->compMM(glm::translate(glm::vec3(-0.5,3.0,0.0)));
            cauce->compMM(glm::scale(glm::vec3(0.5,0.5,1.0)));
            Arbol(n-1);
        cauce->popMM();
        cauce->pushMM();
            cauce->compMM(glm::translate(glm::vec3(1.5,2.5,0.0)));
            cauce->compMM(glm::rotate(-45.0f,glm::vec3(0.0,0.0,1.0)));
            cauce->compMM(glm::scale(glm::vec3(0.707,0.707,0.0)));
            Arbol(n-1);
        cauce->popMM();
    }
}

// ---------------------------------------------------------------------------------------------
// función que se encarga de visualizar el contenido en la ventana

void VisualizarFrame( )
{
    using namespace std ;
    using namespace glm ;

    // comprobar y limpiar variable interna de error
    assert( glGetError() == GL_NO_ERROR );

    // usar (acrivar) el objeto programa (no es necesario hacerlo en 
    // cada frame si solo hay uno de estos objetos, pero se incluye 
    // para hacer explícito que el objeto programa debe estar activado)
    cauce->activar();

    // establece la zona visible (toda la ventana)
    glViewport( 0, 0, ancho_actual, alto_actual );

    // fija la matriz de transformación de posiciones de los shaders 
    // (la hace igual a la matriz identidad)
    cauce->resetMM();

    // fija la matriz de proyeccion (la hace igual a la matriz identidad)
    cauce->fijarMatrizProyeccion( glm::mat4(1.0) );

    float r = (float)(ancho_actual)/alto_actual;
    float x0, x1, y0, y1, z0, z1;
    z0 = -1.0;
    z1 = 1.0;
    if(r > 1.0){
        x0 = -1.0*r;
        x1 = 1.0*r;
        y0 = -1.0;
        y1 = 1.0;
    }else{
        x0 = -1.0;
        x1 = 1.0;
        y0 = -1.0/r;
        y1 = 1.0/r;
    }
    fijarRegionVisible(x0,x1,y0,y1,z0,z1);

    // limpiar la ventana
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

    // habilitar EPO por Z-buffer (test de profundidad)
    glDisable( GL_DEPTH_TEST );

    //cauce->compMM(glm::scale(glm::vec3(0.15,0.15,0.0)));
    gancho_2p_b(glm::vec3(0.0,0.0,0.0),glm::vec3(1.0,1.0,0.0));

    // comprobar y limpiar variable interna de error
    assert( glGetError() == GL_NO_ERROR );

    // esperar a que termine 'glDrawArrays' y entonces presentar el framebuffer actualizado
    glfwSwapBuffers( ventana_glfw );

}

// ---------------------------------------------------------------------------------------------
// función que se invoca cada vez que cambia el número de pixels del framebuffer
// (cada vez que se redimensiona la ventana)

void FGE_CambioTamano( GLFWwindow* ventana, int nuevo_ancho, int nuevo_alto )
{
    using namespace std ;
    //cout << "FGE cambio tamaño, nuevas dimensiones: " << nuevo_ancho << " x " << nuevo_alto << "." << endl ;
    ancho_actual      = nuevo_ancho ;
    alto_actual       = nuevo_alto ;
    redibujar_ventana = true ; // fuerza a redibujar la ventana
}
// ---------------------------------------------------------------------------------------------
// función que se invocará cada vez que se pulse o levante una tecla.

void FGE_PulsarLevantarTecla( GLFWwindow* ventana, int key, int scancode, int action, int mods )
{
    using namespace std ;
    //cout << "FGE pulsar levantar tecla, número de tecla == " << key << "." << endl ;
    // si se pulsa la tecla 'ESC', acabar el programa
    if ( key == GLFW_KEY_ESCAPE )
        terminar_programa = true ;
}
// ---------------------------------------------------------------------------------------------
// función que se invocará cada vez que se pulse o levante un botón del ratón

void FGE_PulsarLevantarBotonRaton( GLFWwindow* ventana, int button, int action, int mods )
{
    // nada, por ahora

}
// ---------------------------------------------------------------------------------------------
// función que se invocará cada vez que cambie la posición del puntero

void FGE_MovimientoRaton( GLFWwindow* ventana, double xpos, double ypos )
{
    // nada, por ahora
}
// ---------------------------------------------------------------------------------------------
// función que se invocará cada vez que mueva la rueda del ratón.

void FGE_Scroll( GLFWwindow* ventana, double xoffset, double yoffset )
{
    // nada, por ahora
}
// ---------------------------------------------------------------------------------------------
// función que se invocará cuando se produzca un error de GLFW

void ErrorGLFW ( int error, const char * description )
{
    using namespace std ;
    cerr
        << "Error en GLFW. Programa terminado" << endl
        << "Código de error : " << error << endl
        << "Descripción     : " << description << endl ;
    exit(1);
}
// ---------------------------------------------------------------------------------------------
// código de inicialización de GLFW

void InicializaGLFW( int argc, char * argv[] )
{
    using namespace std ;

    // intentar inicializar, terminar si no se puede
    glfwSetErrorCallback( ErrorGLFW );
    if ( ! glfwInit() )
    {
        cout << "Imposible inicializar GLFW. Termino." << endl ;
        exit(1) ;
    }

    // especificar versión de OpenGL y parámetros de compatibilidad que se querrán
   // (pedimos opengl 330, tipo "core" (sin compatibilidad con versiones anteriores)
   glfwWindowHint( GLFW_CONTEXT_VERSION_MAJOR, 3 );
   glfwWindowHint( GLFW_CONTEXT_VERSION_MINOR, 3 ); 
   glfwWindowHint( GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE ); // indica que tambien debe funcionar si se usa con un driver con version superior a la 3.3
   glfwWindowHint( GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE ); // indica que no es compatible hacia atrás con versiones previas a la 3.3

    // especificar que función se llamará ante un error de GLFW
    glfwSetErrorCallback( ErrorGLFW );

    // crear la ventana (var. global ventana_glfw), activar el rendering context
    ventana_glfw = glfwCreateWindow( 512, 512, "IG ejemplo mínimo (OpenGL 3+)", nullptr, nullptr );
    glfwMakeContextCurrent( ventana_glfw ); // necesario para OpenGL

    // leer y guardar las dimensiones del framebuffer en pixels
    glfwGetFramebufferSize( ventana_glfw, &ancho_actual, &alto_actual );

    // definir cuales son las funciones gestoras de eventos (con nombres 'FGE_....')
    glfwSetFramebufferSizeCallback( ventana_glfw, FGE_CambioTamano );
    glfwSetKeyCallback            ( ventana_glfw, FGE_PulsarLevantarTecla );
    glfwSetMouseButtonCallback    ( ventana_glfw, FGE_PulsarLevantarBotonRaton);
    glfwSetCursorPosCallback      ( ventana_glfw, FGE_MovimientoRaton );
    glfwSetScrollCallback         ( ventana_glfw, FGE_Scroll );
}

// ---------------------------------------------------------------------------------------------
// función para inicializar GLEW (necesario para las funciones de OpenGL ver 2.0 y posteriores)
// en macOS no es necesario (está vacía)

void InicializaGLEW()
{
#ifndef __APPLE__
    using namespace std ;
    GLenum codigoError = glewInit();
    if ( codigoError != GLEW_OK ) // comprobar posibles errores
    {
        cout << "Imposible inicializar ’GLEW’, mensaje recibido: " << endl
             << (const char *)glewGetErrorString( codigoError ) << endl ;
        exit(1);
    }
    else
        cout << "Librería GLEW inicializada correctamente." << endl << flush ;

#endif
}

// ---------------------------------------------------------------------------------------------

void InicializaOpenGL()
{
    using namespace std ;
    
    assert( glGetError() == GL_NO_ERROR );

    cout  << "Datos de versión e implementación de OpenGL" << endl
         << "    Implementación de : " << glGetString(GL_VENDOR)  << endl
         << "    Hardware          : " << glGetString(GL_RENDERER) << endl
         << "    Versión de OpenGL : " << glGetString(GL_VERSION) << endl
         << "    Versión de GLSL   : " << glGetString(GL_SHADING_LANGUAGE_VERSION) << endl ;

    
    InicializaGLEW(); // En linux y windows, fija punteros a funciones de OpenGL version 2.0 o superiores
    
    
    assert( glGetError() == GL_NO_ERROR );
    
    glClearColor( 1.0, 1.0, 1.0, 0.0 ); // color para 'glClear' (blanco, 100% opaco)
    glDisable( GL_CULL_FACE );          // dibujar todos los triángulos independientemente de su orientación
    cauce = new Cauce() ;            // crear el objeto programa (variable global 'cauce')
    
    assert( cauce != nullptr );
    assert( glGetError() == GL_NO_ERROR );
}
// ---------------------------------------------------------------------------------------------

void BucleEventosGLFW()
{
    while ( ! terminar_programa )
    {   
        if ( redibujar_ventana )
        {   
            VisualizarFrame();
            redibujar_ventana = false; // (evita que se redibuje continuamente)
        }
        glfwWaitEvents(); // esperar evento y llamar FGE (si hay alguna)
        terminar_programa = terminar_programa || glfwWindowShouldClose( ventana_glfw );
    }
}
// ---------------------------------------------------------------------------------------------

int main( int argc, char *argv[] )
{
    using namespace std ;
    cout << "Programa mínimo de OpenGL 3.3 o superior" << endl ;

    InicializaGLFW( argc, argv ); // Crea una ventana, fija funciones gestoras de eventos
    InicializaOpenGL() ;          // Compila vertex y fragment shaders. Enlaza y activa programa. Inicializa GLEW.
    BucleEventosGLFW() ;          // Esperar eventos y procesarlos hasta que 'terminar_programa == true'
    glfwTerminate();              // Terminar GLFW (cierra la ventana)

    cout << "Programa terminado normalmente." << endl ;
}
