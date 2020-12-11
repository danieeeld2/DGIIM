bin/main: obj/main.o obj/guia.o
	g++ obj/main.o obj/guia.o -Iinclude/ -o bin/main 

obj/main.o: src/main.cpp
	g++ -g -c -I./include src/main.cpp -o obj/main.o


obj/guia.o: src/Guiatlf.cpp include/Guiatlf.h
	g++ -g -c -I./include src/Guiatlf.cpp -o obj/guia.o

clean:
	rm obj/* bin/*

rebuild: clean bin/main

documentacion: 
	doxygen doc/doxyfile
