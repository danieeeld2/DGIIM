## --------------------------------------------------------------------------------
## Prácticas de Informática Gráfica, curso 22-23
##
## Archivo de configuración para compilar usando CMake en Linux
## última modificación: 14-Julio de 2022
##
## --------------------------------------------------------------------------------

cmake_minimum_required (VERSION 3.5.1)
project (pracs_ig_linux_exe)


## ----------------------------------------------------------------------
## Definir parámetros configurables

set ( raiz                "../..")
set ( fuentes_materiales  ${raiz}/materiales/src-cpp)
set ( fuentes_alumno      ${raiz}/src)
set ( carpeta_ejecutables "../bin" )
set ( nombre_exe_debug    "debug_exe" )
set ( nombre_exe_release  "release_exe" )
set ( opcs_warnings       "-Wall -Wextra -Wno-unused-parameter -Wno-unused-private-field" )
set ( opcs_primer_error   "-Wfatal-errors")
set ( version_cpp         "-std=c++20")

## ----------------------------------------------------------------------
## definir los flags del compilador

set ( flags_compilador  "${version_cpp} ${opcs_warnings} ${opcs_primer_error}")  
set ( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${flags_compilador}")

## ----------------------------------------------------------------------
## definir las listas de archivos *.cpp y *.h que se deben compilar

file (GLOB fuentes_units      ${fuentes_alumno}/*.cpp)
file (GLOB fuentes_headers    ${fuentes_alumno}/*.h)
file (GLOB materiales_units   ${fuentes_materiales}/*.cpp)
file (GLOB materiales_headers ${fuentes_materiales}/*.h)

## ----------------------------------------------------------------------
## buscar las librerías que queremos enlazar, decir que enlacen

set( OpenGL_GL_PREFERENCE "GLVND" ) ## usado en 'find_package( OpenGL )',  sirve para seleccionar Nvidia en ordenadores con GPU discreta nvidia e integrada INTEL 

find_package( GLEW      REQUIRED )
find_package( OpenGL    REQUIRED )
find_package( glfw3 3.3 REQUIRED )
link_libraries( glfw GLEW OpenGL::GL jpeg )

## ----------------------------------------------------------------------
## definir las unidades del ejecutable de debug y de release, dar flags específicos

add_executable            ( ${nombre_exe_debug} ${fuentes_units} ${materiales_units} ${fuentes_headers} ${materiales_headers})
target_include_directories( ${nombre_exe_debug} PUBLIC ${fuentes_alumno} ${fuentes_materiales} )
set_target_properties     ( ${nombre_exe_debug} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${carpeta_ejecutables} )
set_target_properties     ( ${nombre_exe_debug} PROPERTIES COMPILE_FLAGS "-g" )

add_executable            ( ${nombre_exe_release} EXCLUDE_FROM_ALL ${fuentes_units} ${materiales_units} ${fuentes_headers} ${materiales_headers})
target_include_directories( ${nombre_exe_release} PUBLIC ${fuentes_alumno} ${fuentes_materiales} )
set_target_properties     ( ${nombre_exe_release} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${carpeta_ejecutables} )
set_target_properties     ( ${nombre_exe_release} PROPERTIES COMPILE_FLAGS "-O2" )

## -------------------------------------------------------------------------------------------------
## imprime todas las variables cuando se pone 'cmake ..' 
## (activar/desactivar poniendo true/false)

if ( false )
   get_cmake_property(_variableNames VARIABLES)
   list (SORT _variableNames)
   foreach (_variableName ${_variableNames})
      message(STATUS "${_variableName}=${${_variableName}}")
   endforeach()
endif()

