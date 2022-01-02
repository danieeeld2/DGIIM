CREATE TABLE proyecto(
	codpj varchar2(3) CONSTRAINT codpj_clave_primaria PRIMARY KEY,
	nompj varchar2(20) CONSTRAINT nompj_no_nulo NOT NULL,
	ciudad varchar2(15));

