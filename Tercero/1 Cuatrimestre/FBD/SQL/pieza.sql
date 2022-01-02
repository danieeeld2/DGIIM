CREATE TABLE pieza(
	codpie varchar2(3) CONSTRAINT codpie_clave_primaria PRIMARY KEY,
	nompie varchar2(10) CONSTRAINT nompie_no_nulo NOT NULL,
	color varchar2(10),
	peso number(5,2)
		CONSTRAINT peso_entre_0_y_100 CHECK (peso>0 and peso<=100),
	ciudad varchar2(15));
