bin/main: obj/main.o include/Diccionario.h
	g++ obj/main.o -Iinclude/ -o bin/main 

obj/main.o: src/main.cpp
	g++ -g -c -I./include src/main.cpp -o obj/main.o

clean:
	rm obj/* bin/*

rebuild: clean bin/main

documentacion: 
	doxygen doc/doxyfile
