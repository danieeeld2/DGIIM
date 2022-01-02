CREATE TABLE proveedor(
	codpro varchar2(3) CONSTRAINT codpro_clave_primaria PRIMARY KEY,
	nompro varchar2(30) CONSTRAINT nompro_no_nulo NOT NULL,
	status NUMBER CONSTRAINT status_entre_1_y_10
		CHECK (status>=1 and status<=10),
	ciudad varchar2(15));
