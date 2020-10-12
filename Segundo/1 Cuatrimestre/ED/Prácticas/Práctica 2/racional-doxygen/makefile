INCLUDE = .
LIB     = .
OBJ     = .

usoRacional : $(OBJ)/usoRacional.o $(LIB)/libracional.a
	g++ -o usoRacional $(OBJ)/usoRacional.o -I$(INCLUDE) -L$(LIB) -lracional

$(LIB)/libracional.a : $(OBJ)/Racional.o
	ar rvs $(LIB)/libracional.a $(OBJ)/Racional.o

$(OBJ)/Racional.o : Racional.cpp
	g++ -c -o $(OBJ)/Racional.o Racional.cpp -I$(INCLUDE)

$(OBJ)/usoRacional.o : usoRacional.cpp
	g++ -c -o $(OBJ)/usoRacional.o usoRacional.cpp -I$(INCLUDE)
