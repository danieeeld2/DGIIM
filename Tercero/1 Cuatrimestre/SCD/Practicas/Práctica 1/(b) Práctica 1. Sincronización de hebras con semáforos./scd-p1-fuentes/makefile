.SUFFIXES:
.PHONY: pc, fu, pcpla, t 
.PRECIOUS: %_exe

compilador:=g++

pc: prodcons_exe
	./$<

fu: fumadores_exe
	./$< 

## esto solo se usa para probar que la plantilla compila
## (da error al ejecutar)
pcpla: prodcons-plantilla_exe 
	./$< 

## esto solo se usa para probar que la plantilla compila
## (al ejecutarse no hace nada)
fupla: fumadores-plantilla_exe 
	./$< 

## solo para tests
t: test-semaforos_exe
	./$< | more

## regla para compilar (.cpp --> _exe)
%_exe: %.cpp Semaphore.cpp Semaphore.h
		$(compilador) -std=c++11 -pthread -o $@ $< scd.cpp

clean:
	rm -f *_exe
