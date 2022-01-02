CREATE TABLE ventas (
	codpro CONSTRAINT codpro_clave_externa_proveedor
		REFERENCES proveedor(codpro),
	codpie CONSTRAINT codpie_clave_externa_pieza
		REFERENCES pieza(codpie),
	codpj CONSTRAINT codpj_clave_externa_proyecto
		REFERENCES proyecto(codpj),
	cantidad NUMBER(4),
	CONSTRAINT clave_primaria PRIMARY KEY(codpro,codpie,codpj));
