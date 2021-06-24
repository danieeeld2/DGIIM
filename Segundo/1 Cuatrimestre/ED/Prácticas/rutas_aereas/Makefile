SRC = src
INC = include
OBJ = obj
BIN = bin
CXX = g++
CPPFLAGS = -Wall -g  -I$(INC) -c
TST = test


# ************** Binario **********
$(BIN)/rutas_aereas : $(OBJ)/Punto.o $(OBJ)/Pais.o $(OBJ)/Paises.o $(OBJ)/Ruta.o $(OBJ)/almacen_rutas.o $(OBJ)/imagen.o $(OBJ)/imagenES.o $(OBJ)/rutas_aereas.o
	$(CXX) -I$(INC) $^ -o $@

# ************ Objetos ***************
$(OBJ)/Punto.o : $(SRC)/Punto.cpp $(INC)/Punto.h
	$(CXX) $(CPPFLAGS) $< -o $@


$(OBJ)/Pais.o : $(SRC)/Pais.cpp $(INC)/Pais.h
	$(CXX) $(CPPFLAGS) $< -o $@

$(OBJ)/Paises.o : $(SRC)/Paises.cpp $(INC)/Paises.h
	$(CXX) $(CPPFLAGS) $< -o $@

$(OBJ)/Ruta.o : $(SRC)/Ruta.cpp $(INC)/Ruta.h
	$(CXX) $(CPPFLAGS) $< -o $@

$(OBJ)/almacen_rutas.o : $(SRC)/almacen_rutas.cpp $(INC)/almacen_rutas.h
	$(CXX) $(CPPFLAGS) $< -o $@

$(OBJ)/imagen.o : $(SRC)/imagen.cpp $(INC)/imagen.h
	$(CXX) $(CPPFLAGS) $< -o $@

$(OBJ)/imagenES.o : $(SRC)/imagenES.cpp $(INC)/imagenES.h
	$(CXX) $(CPPFLAGS) $< -o $@

$(OBJ)/rutas_aereas.o : $(SRC)/rutas_aereas.cpp
	$(CXX) $(CPPFLAGS) $< -o $@

# ************* Objetos test ******************

$(OBJ)/pruebaimagen.o : $(TST)/pruebaimagen.cpp
	$(CXX) $(CPPFLAGS) $< -o $@

$(OBJ)/pruebapais.o : $(TST)/pruebapais.cpp
	$(CXX) $(CPPFLAGS) $< -o $@

$(OBJ)/pruebapaises.o : $(TST)/pruebapaises.cpp
	$(CXX) $(CPPFLAGS) $< -o $@

$(OBJ)/pruebapegado.o : $(TST)/pruebapaises.cpp
	$(CXX) $(CPPFLAGS) $< -o $@

$(OBJ)/pruebapunto.o : $(TST)/pruebapunto.cpp
	$(CXX) $(CPPFLAGS) $< -o $@

$(OBJ)/pruebarotacion.o : $(TST)/pruebarotacion.cpp
	$(CXX) $(CPPFLAGS) $< -o $@

$(OBJ)/pruebaruta.o : $(TST)/pruebaruta.cpp
	$(CXX) $(CPPFLAGS) $< -o $@

$(OBJ)/pruebarutas.o : $(TST)/pruebarutas.cpp
	$(CXX) $(CPPFLAGS) $< -o $@

# ************ Generación de documentación ******************
documentacion :
	doxygen doc/doxys/Doxyfile


# ************ Limpieza ************
clean :
	-rm $(OBJ)/* $(SRC)/*~ $(INC)/*~ ./*~

mrproper : clean
	-rm $(BIN)/* doc/html/*


# ************** Build test ******************8
test: $(BIN)/pruebaimagen $(BIN)/pruebapais $(BIN)/pruebapaises $(BIN)/pruebarutas $(BIN)/pruebapegado $(BIN)/pruebapunto $(BIN)/pruebarotacion $(BIN)/pruebaruta
	$(BIN)/pruebaimagen datos/imagenes/mapas/mapa1.ppm
	$(BIN)/pruebapais 
	$(BIN)/pruebapaises datos/paises.txt
	$(BIN)/pruebarutas datos/almacen_rutas.txt
	$(BIN)/pruebapegado datos/imagenes/mapas/mapa1.ppm datos/imagenes/aviones/avion1.ppm datos/imagenes/aviones/mascara_avion1.ppm pegado.ppm 400 400 1
	$(BIN)/pruebapunto
	$(BIN)/pruebarotacion datos/imagenes/mapas/mapa1.ppm 90 rotacion.ppm
	$(BIN)/pruebaruta

$(BIN)/pruebaimagen : $(OBJ)/pruebaimagen.o $(OBJ)/Punto.o $(OBJ)/Pais.o $(OBJ)/Paises.o $(OBJ)/Ruta.o $(OBJ)/almacen_rutas.o $(OBJ)/imagen.o $(OBJ)/imagenES.o
	$(CXX) -I$(INC) $^ -o $@

$(BIN)/pruebapais : $(OBJ)/pruebapais.o $(OBJ)/Punto.o $(OBJ)/Pais.o $(OBJ)/Paises.o $(OBJ)/Ruta.o $(OBJ)/almacen_rutas.o $(OBJ)/imagen.o $(OBJ)/imagenES.o
	$(CXX) -I$(INC) $^ -o $@

$(BIN)/pruebapaises : $(OBJ)/pruebapaises.o $(OBJ)/Punto.o $(OBJ)/Pais.o $(OBJ)/Paises.o $(OBJ)/Ruta.o $(OBJ)/almacen_rutas.o $(OBJ)/imagen.o $(OBJ)/imagenES.o
	$(CXX) -I$(INC) $^ -o $@

$(BIN)/pruebarutas : $(OBJ)/pruebarutas.o $(OBJ)/Punto.o $(OBJ)/Pais.o $(OBJ)/Paises.o $(OBJ)/Ruta.o $(OBJ)/almacen_rutas.o $(OBJ)/imagen.o $(OBJ)/imagenES.o
	$(CXX) -I$(INC) $^ -o $@

$(BIN)/pruebapegado : $(OBJ)/pruebapegado.o $(OBJ)/Punto.o $(OBJ)/Pais.o $(OBJ)/Paises.o $(OBJ)/Ruta.o $(OBJ)/almacen_rutas.o $(OBJ)/imagen.o $(OBJ)/imagenES.o
	$(CXX) -I$(INC) $^ -o $@

$(BIN)/pruebapunto : $(OBJ)/pruebapunto.o $(OBJ)/Punto.o $(OBJ)/Pais.o $(OBJ)/Paises.o $(OBJ)/Ruta.o $(OBJ)/almacen_rutas.o $(OBJ)/imagen.o $(OBJ)/imagenES.o
	$(CXX) -I$(INC) $^ -o $@

$(BIN)/pruebarotacion : $(OBJ)/pruebarotacion.o $(OBJ)/Punto.o $(OBJ)/Pais.o $(OBJ)/Paises.o $(OBJ)/Ruta.o $(OBJ)/almacen_rutas.o $(OBJ)/imagen.o $(OBJ)/imagenES.o
	$(CXX) -I$(INC) $^ -o $@

$(BIN)/pruebaruta : $(OBJ)/pruebaruta.o $(OBJ)/Punto.o $(OBJ)/Pais.o $(OBJ)/Paises.o $(OBJ)/Ruta.o $(OBJ)/almacen_rutas.o $(OBJ)/imagen.o $(OBJ)/imagenES.o
	$(CXX) -I$(INC) $^ -o $@
# ************* Otros ***************
run: $(BIN)/rutas_aereas
	./bin/rutas_aereas datos/paises.txt datos/imagenes/mapas/mapa1.ppm datos/imagenes/banderas/ datos/almacen_rutas.txt datos/imagenes/aviones/avion1.ppm datos/imagenes/aviones/mascara_avion1.pgm