bin/main: obj/main.o include/Pila_max.h include/Pila_max_VD.h include/Pila_max_Cola.h
	g++ obj/main.o -Iinclude/ -o bin/main 

obj/main.o: src/main.cpp
	g++ -g -c -I./include src/main.cpp -o obj/main.o

clean:
	rm obj/* bin/*

rebuild: clean bin/main

documentacion: 
	doxygen doc/doxyfile
