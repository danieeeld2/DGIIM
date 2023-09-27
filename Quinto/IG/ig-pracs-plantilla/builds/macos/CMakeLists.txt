## --------------------------------------------------------------------------------
## Prácticas de Informática Gráfica, curso 22-23
##
## Archivo de configuración para compilar usando CMake en macOS
## última modificación: 26-Abril de 2023
##
## --------------------------------------------------------------------------------

## definir target y nombre del ejecutable (igual que el target)

cmake_minimum_required (VERSION 3.5.1)
project (pracs_ig_macos)

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

set ( flags_compilador  "${version_cpp} ${opcs_warnings} ${opcs_primer_error}")  
set ( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${flags_compilador}")

## definir donde están las unidades de compilación y los headers

file (GLOB fuentes_units      ${fuentes_alumno}/*.cpp)
file (GLOB fuentes_headers    ${fuentes_alumno}/*.h)
file (GLOB materiales_units   ${fuentes_materiales}/*.cpp)
file (GLOB materiales_headers ${fuentes_materiales}/*.h)

## buscar las librerías que queremos enlazar, decir que enlacen

find_package( jpeg    REQUIRED ) ## define variable 'JPEG_LIBRARIES'
find_package( OpenGL  REQUIRED ) ## define librería 'OpenGL::GL'
find_package( glfw3   REQUIRED ) ## define librería 'glfw'
link_libraries( glfw OpenGL::GL ${JPEG_LIBRARIES})

## definir las unidades del ejecutable, los directorios de include y las librerías.

add_executable            ( ${nombre_exe_debug} ${fuentes_units} ${materiales_units} ${fuentes_headers} ${materiales_headers})
target_include_directories( ${nombre_exe_debug} PUBLIC ${fuentes_alumno} ${fuentes_materiales} )
set_target_properties     ( ${nombre_exe_debug} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${carpeta_ejecutables} )
set_target_properties     ( ${nombre_exe_debug} PROPERTIES COMPILE_FLAGS "-g" )

add_executable            ( ${nombre_exe_release} EXCLUDE_FROM_ALL ${fuentes_units} ${materiales_units} ${fuentes_headers} ${materiales_headers})
target_include_directories( ${nombre_exe_release} PUBLIC ${fuentes_alumno} ${fuentes_materiales} )
set_target_properties     ( ${nombre_exe_release} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${carpeta_ejecutables} )
set_target_properties     ( ${nombre_exe_release} PROPERTIES COMPILE_FLAGS "-g" )


##### imprime todas las variables cuando se pone 'cmake ..' (activar/desactivar poniendo true/false)
##### (muy util para depurar este archivo)

if ( false )
   get_cmake_property(_variableNames VARIABLES)
   list (SORT _variableNames)
   foreach (_variableName ${_variableNames})
      message(STATUS "${_variableName}=${${_variableName}}")
   endforeach()
endif()

