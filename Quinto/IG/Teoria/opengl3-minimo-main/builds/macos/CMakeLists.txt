
## --------------------------------------------------------------------------------
## Ejemplo OpenGL mínimo, versión OpenGL+GLSL 3.3
##
## Archivo de configuración para compilar usando CMake en macOS
## creado: 26-Abril de 2023
## actualizaciones:
##    2023 Jun 20 : separo carpetas 'cmake' y 'bin' añado targets debug y release
##
## --------------------------------------------------------------------------------

cmake_minimum_required (VERSION 3.5.1)
project (opengl3_minimo_macos)

## diversos aspectos configurables

set ( carpeta_fuentes     "../../src")
set( carpeta_ejecutables  "../bin" )
set ( flags_compilador    "-std=c++20 -Wall -Wfatal-errors -Wno-deprecated-declarations" ) 
set ( nombre_exe_debug    "debug_exe" )
set ( nombre_exe_release  "release_exe" )

## definir directorios donde están los fuentes

file ( GLOB unidades  ${carpeta_fuentes}/*.cpp )
file ( GLOB cabeceras ${carpeta_fuentes}/*.h   )

## fijar las opciones que se van a usar para compilar y enlazar

set (CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} ${flags_compilador}")

## buscar las librerías que se van a usar 

find_package( OpenGL REQUIRED )
find_package( glfw3 3.3 REQUIRED )
link_libraries(  glfw OpenGL::GL)

## definir el ejecutable de 'debug' (se usa la opción adicional: -g)
## se compila con 'make' 

add_executable       ( ${nombre_exe_debug} ${unidades} ${cabeceras} )
set_target_properties( ${nombre_exe_debug} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${carpeta_ejecutables} )
set_target_properties( ${nombre_exe_debug} PROPERTIES COMPILE_FLAGS "-g" )


## definir el ejecutable de 'release' (se usa la opción adicional: -O3)
## se compila con 'make release_exe'

add_executable       ( ${nombre_exe_release} EXCLUDE_FROM_ALL ${unidades} ${cabeceras} )
set_target_properties( ${nombre_exe_release} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${carpeta_ejecutables} )
set_target_properties( ${nombre_exe_release} PROPERTIES COMPILE_FLAGS "-O3" )







