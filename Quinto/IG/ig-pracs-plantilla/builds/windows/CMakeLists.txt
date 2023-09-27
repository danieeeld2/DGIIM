## --------------------------------------------------------------------------------
## Prácticas de Informática Gráfica, curso 23-24
##
## Archivo de configuración para compilar usando CMake en windows,
## Asume que las librerías necesarias se han instalado con 'vcpkg'
## última modificación: 19 de Abril del 2023
##                      17 de Julio de 2023.
##
## --------------------------------------------------------------------------------

cmake_minimum_required (VERSION 3.5.1)
set( CMAKE_TOOLCHAIN_FILE ~/vcpkg/scripts/buildsystems/vcpkg.cmake) ## permite a 'find_package' encontrar librerías instaladas con VCPKG
project (pracs_ig_windows)

## ----------------------------------------------------------------------------------------------------
## Aspectos configurables

set (raiz         "../..")
set (dir_src_mat  ${raiz}/materiales/src-cpp)
set (dir_src_alu  ${raiz}/src)

set( carpeta_ejecutable    "../bin" )
set( nombre_ejecutable     "ejecutable" )
set( opcs_warnings         "/wd4244 /wd4305 /wd4267" ) ## deshabilitar warnings de conversión implicita double --> float, size_t --> int (este ultimo es dudoso..)
set( opcs_primer_error     "" ) ## "-Wfatal-errors"  --> no hay nada equivalente a esto en el compilador de microsoft, no se puede parar con el 1er error
set( flags_compilador      "/std:c++20 /utf-8 /MT /O2 ${opcs_warnings} ${opcs_primer_error}" ) 

## ----------------------------------------------------------------------------------------------------
## Definir flags para compilador y carpeta(s) de includes en todos los targets

set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${flags_compilador}")
include_directories( ${dir_src_mat} ${dir_src_alu} )

## ----------------------------------------------------------------------------------------------------
## Buscar librerías en el sistema y añadirlas a todos los targets
## (no se busca GLM ya que es una librería 'header only')

find_package( GLEW  REQUIRED )
find_package( glfw3 CONFIG REQUIRED )
find_package( JPEG  REQUIRED)
link_libraries( GLEW::GLEW glfw  ${JPEG_LIBRARIES})

## ----------------------------------------------------------------------------------------------------
## Definir ejecutable (unidades y cabeceras a compilar), indicar carpeta donde debe alojarse el .exe

file (GLOB unidades_alu   ${dir_src_alu}/*.cpp  )
file (GLOB cabeceras_alu  ${dir_src_alu}/*.h    )
file (GLOB unidades_mat   ${dir_src_mat}/*.cpp )
file (GLOB cabeceras_mat  ${dir_src_mat}/*.h   )

add_executable       ( ${nombre_ejecutable} ${unidades_alu} ${unidades_mat} ${cabeceras_alu} ${cabeceras_mat})
set_target_properties( ${nombre_ejecutable} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${carpeta_ejecutable} )

#######################################
## para depurar, imprime algunas (o todas) las variables
## imprime todas las variables cuando se pone 'cmake .' (activar/desactivar poniendo true/false)

if ( false )
   get_cmake_property(_variableNames VARIABLES)
   list (SORT _variableNames)
   foreach (_variableName ${_variableNames})
      message(STATUS "${_variableName}=${${_variableName}}")
   endforeach()
endif()

