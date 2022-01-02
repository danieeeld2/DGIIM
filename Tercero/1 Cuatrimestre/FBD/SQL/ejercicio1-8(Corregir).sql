CREATE TABLE equipos(
	codE varchar2(3) CONSTRAINT codE_clave_primaria PRIMARY KEY,
	nombreE varchar2(10) NOT NULL CONSTRAINT nombreE_unico UNIQUE,
	localidad varchar2(20) NOT NULL,
	entrenador varchar2(20) NOT NULL,
	fecha_crea date NOT NULL);

CREATE TABLE jugadores(
	codJ varchar2(3) CONSTRAINT codJ_clave_primaria PRIMARY KEY,
	codE REFERENCES equipos(codE) NOT NULL,
	nombreJ varchar2(20) NOT NULL);

CREATE TABLE encuentros(
	ELocal REFERENCES equipos(codE),
	EVisitante REFERENCES equipo(codE),
	fecha date NOT NULL,
	PLocal int NOT NULL default 0,
	PVisitante int NOT NULL default 0,
	CONSTRAINT puntos_mayor_que_0 CHECK (PLocal>=0 and PVisitante>=0),
	CONSTRAINT clave_primaria PRIMARY KEY (ELocal,EVisitante));

CREATE TABLE faltas(
	codJ REFERENCES jugadores(codJ),
	ELocal REFERENCES equipos(ELocal),
	EVisitante REFERENCES equipos(EVisitante),
	num int NOT NULL default 0
		CONSTRAINT num_entre_0_y_5 CHECK (num>=0 and num<=5),
	CONSTRAINT clave_primaria PRIMARY KEY (codJ,ELocal,EVisitante));
	
